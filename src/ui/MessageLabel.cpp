#include <QTimer>
#include <QTextBlock>
#include "ui/MessageLabel.h"

MessageLabel::MessageLabel(QWidget *parent) : QTextEdit(parent) {
    setStyleSheet(style);
    setReadOnly(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto policy = sizePolicy();
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    setSizePolicy(policy);

    format.setLineHeight(140, QTextBlockFormat::ProportionalHeight);

    connect(this, &QTextEdit::textChanged, [=] {
        QTimer::singleShot(5, this, [=] {
            adjustLineSpacing();
            adjustHeight();
        });
    });
}

void MessageLabel::resizeEvent(QResizeEvent *event) {
    QTextEdit::resizeEvent(event);
    adjustHeight();
}

void MessageLabel::adjustHeight() {
    int height = document()->size().toSize().height();
    if (height != currentHeight) {
        currentHeight = height;
        setFixedHeight(height + contentsMargins().top() + contentsMargins().bottom());
    }
}

void MessageLabel::adjustLineSpacing() {
    blockSignals(true);

    for (QTextBlock it = document()->begin(); it != document()->end(); it = it.next()) {
        if (!it.text().isEmpty()) {
            QTextCursor cursor(it);
            cursor.setBlockFormat(format);
        }
    }

    blockSignals(false);
}
