#include <QTimer>
#include <QScrollBar>
#include <QDateTime>
#include <QDragEnterEvent>
#include <QMimeData>
#include "ui/Chat.h"
#include "ui/MessageLabel.h"
#include "ui/UsernameLabel.h"
#include "ui/ImageLabel.h"

Chat::Chat(QWidget *parent) : QScrollArea(parent) {
    auto *content = new QWidget(this);
    content->setStyleSheet("QWidget {background-color:#fff;}");
    content->setLayout(&layout);
    layout.addStretch();
    setWidgetResizable(true);
    setAcceptDrops(true);
    setWidget(content);
}

void Chat::addText(const QString &text) {
    auto *messageLabel = new MessageLabel(this);
    messageLabel->setText(text);
    layout.insertWidget(layout.count() - 1, messageLabel);

    scrollToBottom();
}

void Chat::addUsername(const QString &username) {
    QString dateTime = QDateTime::currentDateTime().toString("M/d/yyyy, hh:mm AP");

    auto *label = new UsernameLabel(this);
    label->setText(username + "    " + dateTime);
    layout.insertWidget(layout.count() - 1, label);

    scrollToBottom();
}

void Chat::addImage(const cv::Mat &img) {
    auto *label = new ImageLabel(img, 400, this);
    layout.insertWidget(layout.count() - 1, label);

    scrollToBottom();
}

void Chat::addProgressBar() {
    progressBar.setRange(0, 0);
    layout.insertWidget(layout.count() - 1, &progressBar);

    scrollToBottom();
}

void Chat::addProgressBar(const int &steps) {
    progressBarSteps = steps;
    progressBar.setRange(0, 0);
    progressBar.setValue(0);
    layout.insertWidget(layout.count() - 1, &progressBar);

    scrollToBottom();
}

void Chat::setProgressBarStep(const int &step) {
    progressBar.setRange(0, progressBarSteps);
    progressBar.setValue(step);
}

void Chat::removeProgressBar() {
    progressBar.setParent(nullptr);
}

void Chat::scrollToBottom() {
    QTimer::singleShot(40, this, [scrollBar = verticalScrollBar()] {
        scrollBar->setValue(scrollBar->maximum());
    });
}

void Chat::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void Chat::dropEvent(QDropEvent *event) {
    for (const QUrl &url: event->mimeData()->urls()) {
        emit dropped(url.toLocalFile());
        break;
    }
}
