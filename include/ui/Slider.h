#ifndef ASSISTANT_UI_SLIDER_H
#define ASSISTANT_UI_SLIDER_H

#include <QSlider>
#include <QSpinBox>
#include <QLabel>

class Slider : public QWidget {
Q_OBJECT

public:
    explicit Slider(QWidget *parent = nullptr);

    void setText(const QString &text);

    void setValue(int value);

    int getValue();

    void setMinMaxValue(int min, int max);

signals:

    void valueChanged(int value);

private:
    QLabel label;
    QSlider slider;
    QSpinBox input;
    QLabel minValue;
    QLabel maxValue;

    QString style = R"(
        QSpinBox {
            padding: 6px;
            border: 1px solid #ccc;
            border-radius: 4px;
            color: #333;
            font-size: 14px;
        }
        QSpinBox:focus {
            border-color: #66afe9;
        }
        QSpinBox:disabled {
            background-color: #e9ecef;
            border-color: #ced4da;
            color: #212529;
        }
        QLabel {
            color: #000;
            font-size: 12px;
        }
    )";
};

#endif //ASSISTANT_UI_SLIDER_H
