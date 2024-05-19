#include "ui/face/Area.h"
#include "utils/ImageIo.h"
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

    libfacedetection.moveToThread(&thread);
    connect(&libfacedetection, &QLibfacedetection::detected, this, [=](
        const std::vector<Face::Detection> &detections, const cv::Mat &img
    ) {
        chat->removeProgressBar();

        cv::Mat result;
        img.copyTo(result);
        Visualize::drawFaceDetections(result, detections);
        chat->addImage(result);

        Params params = settings->getParams();
        if (params.autosave) {
            ImageIo::write(params.path, DateTime::current() + ".jpg", img);
        }
    });

    connect(uploadBar, &UploadBar::imageSelected, this, [=](const cv::Mat &img) {
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
    QMetaObject::invokeMethod(&libfacedetection, [=] {
        libfacedetection.detect(img);
    });
}
