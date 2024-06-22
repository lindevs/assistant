#include <QFile>
#include "ui/face/Area.h"
#include "utils/ImgIo.h"
#include "utils/DateTime.h"
#include "utils/Visualize.h"
#include "ui/MessageDialog.h"
#include "face/QFaceDetection.h"

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

    auto *dialog = new MessageDialog("Error", parent);

    faceDetection.moveToThread(&thread);
    connect(&thread, &QThread::started, [=] {
        currentParams = settings->getParams();
        faceDetection.start(currentParams);
    });
    connect(&thread, &QThread::finished, &faceDetection, &QFaceDetection::stop);
    connect(&faceDetection, &QFaceDetection::detected, this, [=](
        const std::vector<Face::Detection> &detections, const cv::Mat &img
    ) {
        chat->removeProgressBar();
        Params params = settings->getParams();

        cv::Mat result;
        img.copyTo(result);
        if (params.blur) {
            Visualize::blurFaces(result, detections);
        } else {
            Visualize::drawFaceDetections(result, detections);
        }
        chat->addImage(result);

        if (params.autosave) {
            ImgIo::write(params.outputPath, DateTime::current() + ".jpg", result);
        }
    });

    connect(uploadBar, &UploadBar::imageSelected, this, [=](const cv::Mat &img) {
        Params params = settings->getParams();
        QString path = QString(params.path) + "/" + params.model.file;

        if (params.model.url && !QFile::exists(path)) {
            dialog->setText(
                QString("Unable to find model '%1'.<br>Download it from <a href=\"%2\">%3</a>")
                    .arg(path, params.model.url, params.model.url)
            );
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

        detect(img);
    });
}

Face::Area::~Area() {
    if (started) {
        thread.quit();
        thread.wait();
    }
}


void Face::Area::detect(const cv::Mat &img) {
    chat->addUsername("User");
    chat->addImage(img);
    chat->addUsername("Assistant");
    chat->addProgressBar();
    QMetaObject::invokeMethod(&faceDetection, [=] {
        faceDetection.detect(img);
    });
}
