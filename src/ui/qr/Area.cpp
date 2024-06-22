#include "ui/qr/Area.h"
#include "utils/ImgIo.h"
#include "utils/DateTime.h"

Qr::Area::Area(QWidget *parent) : QWidget(parent) {
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
    textBar = new TextBar(mainContent);
    contentLayout->addWidget(textBar);

    connect(textBar, &TextBar::generateButtonClicked, this, [=]() {
        if (textBar->getText().length() == 0) {
            return;
        }

        generate();
    });
}

void Qr::Area::generate() {
    QString text = textBar->getText();
    Params params = settings->getParams();
    chat->addUsername("User");
    chat->addText(text);
    chat->addUsername("Assistant");
    textBar->clearText();

    cv::Mat img = ZxingCpp::generate(text.toStdString(), params);
    chat->addImage(img);

    if (params.autosave) {
        ImgIo::write(params.path, DateTime::current() + ".jpg", img);
    }
}
