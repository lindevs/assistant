#include "ui/hash/Area.h"
#include "utils/ImgProc.h"

Hash::Area::Area(QWidget *parent) : QWidget(parent) {
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

    hashCalculation.moveToThread(&thread);
    connect(&thread, &QThread::started, [=] {
        currentParams = settings->getParams();
        hashCalculation.start(currentParams);
    });
    connect(&thread, &QThread::finished, &hashCalculation, &QHashCalculation::stop);
    connect(&hashCalculation, &QHashCalculation::calculated, this, [=](const QString &hash) {
        chat->removeProgressBar();
        chat->addText(hash);
    });

    connect(uploadBar, &UploadBar::imageSelected, this, [=](const cv::Mat &img) {
        Params params = settings->getParams();

        if (currentParams != params) {
            thread.quit();
            thread.wait();
            started = false;
        }
        if (!started) {
            thread.start();
            started = true;
        }

        calculate(img);
    });
}

Hash::Area::~Area() {
    if (started) {
        thread.quit();
        thread.wait();
    }
}

void Hash::Area::calculate(const cv::Mat &img) {
    chat->addUsername("User");
    chat->addImage(img);
    chat->addUsername("Assistant");
    chat->addProgressBar();
    QMetaObject::invokeMethod(&hashCalculation, [=] {
        hashCalculation.calculate(img);
    });
}
