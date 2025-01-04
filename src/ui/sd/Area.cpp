#include <QFile>
#include "ui/sd/Area.h"
#include "ui/MessageDialog.h"
#include "utils/ImgIo.h"
#include "utils/DateTime.h"

Sd::Area::Area(QWidget *parent) : QWidget(parent) {
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

    auto *dialog = new MessageDialog("Error", parent);

    diffusion.moveToThread(&thread);
    connect(&thread, &QThread::started, [=] {
        currentParams = settings->getParams();
        diffusion.start(currentParams);
    });
    connect(&thread, &QThread::finished, &diffusion, &QStableDiffusion::stop);
    connect(textBar, &TextBar::generateButtonClicked, this, [=]() {
        if (textBar->getText().length() == 0) {
            return;
        }

        Params params = settings->getParams();
        for (size_t i = 0; i < params.model.files.size(); ++i) {
            QString modelPath = QString(params.path) + "/" + params.model.files[i];

            if (!QFile::exists(modelPath)) {
                dialog->setText(
                    QString("Unable to find model '%1'.<br>Download it from <a href=\"%2\">%3</a>")
                        .arg(modelPath, params.model.urls[i], params.model.urls[i])
                );
                dialog->show();

                return;
            }
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

        generate();
    });
    connect(&diffusion, &QStableDiffusion::generated, this, &Area::onGenerated);
    connect(&diffusion, &QStableDiffusion::stepChanged, this, [=](const int &step) {
        chat->setProgressBarStep(step);
    });
}

Sd::Area::~Area() {
    if (started) {
        thread.quit();
        thread.wait();
    }
}

void Sd::Area::generate() {
    Params params = settings->getParams();
    QString text = textBar->getText();
    chat->addUsername("User");
    chat->addText(text);
    chat->addUsername("Assistant");
    chat->addProgressBar(params.steps);
    textBar->clearText();
    QMetaObject::invokeMethod(&diffusion, [=] {
        diffusion.generate(text, params.steps);
    });
}

void Sd::Area::onGenerated(const cv::Mat &img) {
    Params params = settings->getParams();

    chat->removeProgressBar();
    chat->addImage(img);

    if (params.autosave) {
        ImgIo::write(params.outputPath, DateTime::current() + ".png", img);
    }
}
