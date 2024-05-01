#include <QLayout>
#include <QPushButton>
#include "ui/TextBar.h"

TextBar::TextBar(QWidget *parent) : QWidget(parent) {
    setStyleSheet(style);

    auto *layout = new QHBoxLayout(this);

    textEdit.setPlaceholderText("Enter your text...");

    auto *generateButton = new QPushButton(this);
    generateButton->setText("Generate");
    generateButton->setCursor(Qt::PointingHandCursor);

    layout->addWidget(&textEdit);
    layout->addWidget(generateButton);
    layout->setAlignment(generateButton, Qt::AlignBottom);
    layout->setContentsMargins(0, 9, 0, 0);

    connect(generateButton, &QPushButton::clicked, this, &TextBar::generateButtonClicked);
}

QString TextBar::getText() {
    return textEdit.toPlainText();
}

void TextBar::clearText() {
    textEdit.clear();
}
