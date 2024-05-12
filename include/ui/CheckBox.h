#ifndef ASSISTANT_UI_CHECK_BOX_H
#define ASSISTANT_UI_CHECK_BOX_H

#include <QCheckBox>

class CheckBox : public QCheckBox {
Q_OBJECT

public:
    explicit CheckBox(QWidget *parent = nullptr);

    void setText(const QString &text);

    bool isChecked();

private:
    QString style = R"(
        QCheckBox {
            color: #000;
        }
    )";
};

#endif //ASSISTANT_UI_CHECK_BOX_H
