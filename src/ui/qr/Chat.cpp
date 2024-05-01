#include <QTimer>
#include <QScrollBar>
#include <QDateTime>
#include "ui/qr/Chat.h"
#include "ui/MessageLabel.h"
#include "ui/UsernameLabel.h"
#include "ui/ImageLabel.h"

Qr::Chat::Chat(QWidget *parent) : QScrollArea(parent) {
    auto *content = new QWidget(this);
    content->setStyleSheet("QWidget {background-color:#fff;}");
    content->setLayout(&layout);
    layout.addStretch();
    setWidgetResizable(true);
    setWidget(content);
}

void Qr::Chat::addText(const QString &username, const QString &text) {
    QString dateTime = QDateTime::currentDateTime().toString("M/d/yyyy, hh:mm AP");

    auto *label = new UsernameLabel(this);
    label->setText(username + "    " + dateTime);
    layout.insertWidget(layout.count() - 1, label);

    auto *messageLabel = new MessageLabel(this);
    messageLabel->setText(text);
    layout.insertWidget(layout.count() - 1, messageLabel);

    scrollToBottom();
}

void Qr::Chat::addText(const QString &username) {
    QString dateTime = QDateTime::currentDateTime().toString("M/d/yyyy, hh:mm AP");

    auto *label = new UsernameLabel(this);
    label->setText(username + "    " + dateTime);
    layout.insertWidget(layout.count() - 1, label);

    scrollToBottom();
}

void Qr::Chat::addImage(const QImage &img) {
    auto *label = new ImageLabel(img, 400, this);
    layout.insertWidget(layout.count() - 1, label);

    scrollToBottom();
}

void Qr::Chat::scrollToBottom() {
    QTimer::singleShot(10, this, [scrollBar = verticalScrollBar()] {
        scrollBar->setValue(scrollBar->maximum());
    });
}
