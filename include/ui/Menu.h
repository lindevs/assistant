#ifndef ASSISTANT_UI_MENU_H
#define ASSISTANT_UI_MENU_H

#include <QGroupBox>
#include "ui/MenuItem.h"

class Menu : public QGroupBox {
Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

signals:

    void clicked(int itemIdx);

private:
    std::vector<QString> icons = {
        ":/img/qr.png",
        ":/img/ocr.png",
    };
    std::vector<MenuItem *> items;

    int itemIdx = 0;

    QString style = R"(
        QGroupBox {
            border: 1px solid #ccc;
            border-radius: 4px;
        }
        QLabel {
            padding: 9px;
            border-bottom: 1px solid #ccc;
            border-radius: 4px;
        }
    )";
};

#endif //ASSISTANT_UI_MENU_H
