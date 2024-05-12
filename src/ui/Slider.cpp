#include <QLayout>
#include "ui/Slider.h"

Slider::Slider(QWidget *parent) : QWidget(parent) {
    setStyleSheet(style);

    auto *mainLayout = new QVBoxLayout(this);
    auto *sliderLayout = new QVBoxLayout();
    auto *valueLayout = new QHBoxLayout();
    auto *inputsLayout = new QHBoxLayout();

    mainLayout->setContentsMargins(0, 0, 0, 0);
    sliderLayout->setContentsMargins(0, 0, 0, 0);
    valueLayout->setContentsMargins(0, 0, 0, 0);
    inputsLayout->setContentsMargins(0, 0, 0, 0);

    input.setFixedWidth(60);
    input.setButtonSymbols(QAbstractSpinBox::NoButtons);
    slider.setOrientation(Qt::Orientation::Horizontal);

    valueLayout->addWidget(&minValue);
    valueLayout->addWidget(&maxValue);
    maxValue.setAlignment(Qt::AlignRight);

    sliderLayout->addWidget(&slider);
    sliderLayout->addLayout(valueLayout);

    inputsLayout->addLayout(sliderLayout);
    inputsLayout->addWidget(&input);

    mainLayout->addWidget(&label);
    mainLayout->addLayout(inputsLayout);

    connect(&slider, &QSlider::valueChanged, &input, &QSpinBox::setValue);
    connect(&slider, &QSlider::valueChanged, this, &Slider::valueChanged);
    connect(&input, &QSpinBox::valueChanged, &slider, &QSlider::setValue);
}

void Slider::setText(const QString &text) {
    label.setText(text);
}

void Slider::setValue(const int value) {
    input.setValue(value);
}

int Slider::getValue() {
    return input.value();
}

void Slider::setMinMaxValue(const int min, const int max) {
    slider.setRange(min, max);
    input.setRange(min, max);
    minValue.setText(QString::number(min));
    maxValue.setText(QString::number(max));
}
