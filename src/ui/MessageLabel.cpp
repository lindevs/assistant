#include "ui/MessageLabel.h"

MessageLabel::MessageLabel(QWidget *parent) : QTextEdit(parent) {
    setStyleSheet("QTextEdit {background-color:#f5f5f4;padding:8px;border-radius:8px;font-size:14px;}");
    setReadOnly(true);

    format.setLineHeight(140, QTextBlockFormat::ProportionalHeight);

    connect(this, &QTextEdit::cursorPositionChanged, this, &MessageLabel::adjustLineSpacing);
}

void MessageLabel::resizeEvent(QResizeEvent *event) {
    QTextEdit::resizeEvent(event);
    adjustHeight();
}

void MessageLabel::adjustHeight() {
    int currentHeight = document()->size().toSize().height();
    if (currentHeight != 0) {
        setFixedHeight(currentHeight + 16);
    }
}

void MessageLabel::adjustLineSpacing() {
    if (document()->size().toSize().height() > 25) {
        QTextCursor cursor = textCursor();
        cursor.select(QTextCursor::Document);
        cursor.setBlockFormat(format);
    }
}
