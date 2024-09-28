#include <QFile>
#include "ui/face/Area.h"
#include "utils/ImgIo.h"
#include "utils/DateTime.h"
#include "utils/Visualize.h"

Face::Area::Area(QWidget *parent) : QWidget(parent) {
    auto *horizontalLayout = new QHBoxLayout(this);

    auto *mainContent = new QWidget(this);
    horizontalLayout->addWidget(mainContent);
    auto *contentLayout = new QVBoxLayout(mainContent);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    auto *sidebarContent = new QWidget();
    sidebarContent->setMaximumWidth(250);
    auto *sidebarLayout = new QHBoxLayout(sidebarContent);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->addWidget(sidebarContent);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    settings = new Settings();
    sidebarLayout->addWidget(settings);

    chat = new Chat(mainContent);
    contentLayout->addWidget(chat);
    uploadBar = new UploadBar(mainContent);
    contentLayout->addWidget(uploadBar);

    dialog = new ModelDialog("Error", parent);

    faceDetection.moveToThread(&thread);
    backgroundMatting.moveToThread(&thread);
    connect(&thread, &QThread::started, [=] {
        currentParams = settings->getParams();
        faceDetection.start(currentParams);
        if (currentParams.idPhoto) {
            backgroundMatting.start(currentParams);
        }
    });
    connect(&thread, &QThread::finished, [=] {
        faceDetection.stop();
        backgroundMatting.stop();
    });

    connect(uploadBar, &UploadBar::imageSelected, this, &Area::process);
    connect(&faceDetection, &QFaceDetection::detected, this, &Area::onDetected);
    connect(&backgroundMatting, &QBackgroundMatting::generated, this, &Area::onMatteGenerated);
}

Face::Area::~Area() {
    if (started) {
        thread.quit();
        thread.wait();
    }
}

void Face::Area::process(const cv::Mat &img) {
    currentImg = img;
    Params params = settings->getParams();

    QString modelPath = QString(params.path) + "/" + params.detectionModel.file;
    if (params.detectionModel.url && !QFile::exists(modelPath)) {
        dialog->setModel(params.detectionModel, params.path);
        dialog->show();

        return;
    }

    modelPath = QString(params.path) + "/" + params.mattingModel.file;
    if (params.idPhoto && params.mattingModel.url && !QFile::exists(modelPath)) {
        dialog->setModel(params.mattingModel, params.path);
        dialog->show();

        return;
    }
    if (currentParams != params) {
        thread.quit();
        thread.wait();
        started = false;
    }
    if (!started) {
        thread.start();
        started = true;
    }

    detect();
}

void Face::Area::detect() {
    chat->addUsername("User");
    chat->addImage(currentImg);
    chat->addUsername("Assistant");
    chat->addProgressBar();
    QMetaObject::invokeMethod(&faceDetection, [=] {
        faceDetection.detect(currentImg);
    });
}

void Face::Area::onDetected(const std::vector<Detection> &detections) {
    currentDetections = detections;
    if (detections.empty()) {
        chat->addText("No faces detected.");
        chat->removeProgressBar();

        return;
    }

    Params params = settings->getParams();
    if (params.idPhoto) {
        if (detections.size() > 1) {
            chat->addText("Multiple faces detected.");
            chat->removeProgressBar();

            return;
        }

        QMetaObject::invokeMethod(&backgroundMatting, [=] {
            backgroundMatting.generate(currentImg);
        });

        return;
    }

    cv::Mat result;
    currentImg.copyTo(result);
    if (params.blur) {
        Visualize::blurFaces(result, detections);
    } else {
        Visualize::drawFaceDetections(result, detections);
    }

    chat->removeProgressBar();
    chat->addImage(result);

    if (params.autosave) {
        ImgIo::write(params.outputPath, DateTime::current() + ".jpg", result);
    }
}

void Face::Area::onMatteGenerated(const cv::Mat &matte) {
    Params params = settings->getParams();

    cv::Mat alpha = matte * 255;
    alpha.convertTo(alpha, CV_8U);
    cv::Mat result = idPhotoCreator.create(currentImg, alpha, currentDetections[0].box);

    chat->removeProgressBar();
    chat->addImage(result);

    if (params.autosave) {
        ImgIo::write(params.outputPath, DateTime::current() + ".png", result);
    }
}
