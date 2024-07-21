#include <QFile>
#include "ui/dedup/Area.h"
#include "ui/MessageDialog.h"
#include "utils/Formatting.h"

Dedup::Area::Area(QWidget *parent) : QWidget(parent) {
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
    uploadBar = new UploadBar(mainContent, UploadBar::TYPE_DIRECTORY);
    contentLayout->addWidget(uploadBar);

    auto *dialog = new MessageDialog("Error", parent);

    deduplication.moveToThread(&thread);
    connect(&thread, &QThread::started, [=] {
        currentParams = settings->getParams();
        deduplication.start(currentParams);
    });
    connect(&thread, &QThread::finished, &deduplication, &QImageDeduplication::stop);
    connect(&deduplication, &QImageDeduplication::found, this, [=](const Dedup::Findings &findings) {
        chat->removeProgressBar();

        size_t total = findings.duplications.size();
        for (size_t i = 0; i < total; ++i) {
            if (findings.duplications[i].empty()) {
                continue;
            }
            if (i == showLimit) {
                chat->addText("Too many duplicates...");
                break;
            }
            chat->addText(QString::fromStdString(Formatting::formatDuplications(findings, i)));
        }
    });

    connect(uploadBar, &UploadBar::directorySelected, this, [=](const QString &path) {
        Params params = settings->getParams();
        QString modelPath = QString(params.path) + "/" + params.model.file;

        if (params.model.url && !QFile::exists(modelPath)) {
            dialog->setText(
                QString("Unable to find model '%1'.<br>Download it from <a href=\"%2\">%3</a>")
                    .arg(modelPath, params.model.url, params.model.url)
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

        findDuplicates(path);
    });
}

Dedup::Area::~Area() {
    if (started) {
        thread.quit();
        thread.wait();
    }
}

void Dedup::Area::findDuplicates(const QString &path) {
    chat->addUsername("User");
    chat->addText(path);
    chat->addUsername("Assistant");
    chat->addProgressBar();
    QMetaObject::invokeMethod(&deduplication, [=] {
        deduplication.findDuplicates(path);
    });
}
