#include "ui/MessageEdit.h"

MessageEdit::MessageEdit(QWidget *parent) : QTextEdit(parent) {
    setAcceptRichText(false);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    setFixedHeight(38);
    connect(this, &QTextEdit::textChanged, this, &MessageEdit::adjustHeight);
}

void MessageEdit::adjustHeight() {
    int currentHeight = document()->size().toSize().height();
    if (currentHeight != 0 && currentHeight <= MAX_HEIGHT) {
        setFixedHeight(currentHeight + 10);
    } else if (currentHeight > MAX_HEIGHT) {
        setFixedHeight(MAX_HEIGHT);
    }
}
