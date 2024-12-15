#ifndef ASSISTANT_UI_SELECT_BOX_H
#define ASSISTANT_UI_SELECT_BOX_H

#include <QComboBox>
#include <QLabel>

class SelectBox : public QWidget {
Q_OBJECT

public:
    explicit SelectBox(QWidget *parent = nullptr);

    void setText(const QString &text);

    void setCurrenctIndex(int index);

    int getCurrentIndex();

    void addItems(const QList<QString> &items);

signals:

    int currentIndexChanged(int index);

private:
    QLabel label;
    QComboBox input;

    QString style = R"(
        QLabel {
            color: #000;
            font-size: 12px;
        }
        QComboBox {
            font-size: 12px;
        }
    )";
};

#endif //ASSISTANT_UI_SELECT_BOX_H
