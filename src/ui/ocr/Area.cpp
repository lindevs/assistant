#include <QFile>
#include "ui/ocr/Area.h"
#include "utils/ImgIo.h"

Ocr::Area::Area(QWidget *parent) : QWidget(parent) {
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

    dialog = new MessageDialog("Error", parent);

    tesseract.moveToThread(&thread);
    connect(&thread, &QThread::started, [=] {
        currentParams = settings->getParams();
        tesseract.start(currentParams);
    });
    connect(&thread, &QThread::finished, &tesseract, &QTesseract::stop);
    connect(&tesseract, &QTesseract::recognized, this, [=](const QString &text) {
        chat->removeProgressBar();
        chat->addText(text.trimmed());
    });

    connect(uploadBar, &UploadBar::imageSelected, this, &Area::process);
    connect(chat, &Chat::dropped, this, [=](const QString &path) {
        cv::Mat img = ImgIo::read(path.toStdString());
        if (!img.empty()) {
            process(img);
        }
    });
}

Ocr::Area::~Area() {
    if (started) {
        thread.quit();
        thread.wait();
    }
}

void Ocr::Area::process(const cv::Mat &img) {
    Params params = settings->getParams();
    QString path = QString(params.path) + "/" + params.language + ".traineddata";

    if (!QFile::exists(path)) {
        dialog->setText(
            QString("Unable to find training data '%1'.<br>Download it from <a href=\"%2\">%3</a>")
            .arg(path, tesseractUrl, tesseractUrl)
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

    recognize(img);
}

void Ocr::Area::recognize(const cv::Mat &img) {
    chat->addUsername("User");
    chat->addImage(img);
    chat->addUsername("Assistant");
    chat->addProgressBar();
    QMetaObject::invokeMethod(&tesseract, [=] {
        tesseract.recognize(img);
    });
}
