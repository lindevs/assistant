#ifndef ASSISTANT_UI_SELECT_BOX_H
#define ASSISTANT_UI_SELECT_BOX_H

#include <QComboBox>
#include <QLabel>

class SelectBox : public QWidget {
Q_OBJECT

public:
    explicit SelectBox(QWidget *parent = nullptr);

    void setText(const QString &text);

    int getValueIndex();

    void addItems(const QList<QString> &items);

private:
    QLabel label;
    QComboBox input;

    QString style = R"(
        QLabel {
            color: #000;
        }
    )";
};

#endif //ASSISTANT_UI_SELECT_BOX_H
