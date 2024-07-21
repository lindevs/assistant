#ifndef ASSISTANT_UI_MENU_H
#define ASSISTANT_UI_MENU_H

#include <QGroupBox>
#include <QSettings>
#include "ui/MenuItem.h"

class Menu : public QGroupBox {
Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

    int getItemIdx();

signals:

    void clicked(int itemIdx);

private:
    QSettings settings;

    std::vector<QString> icons = {
        ":/img/qr.png",
        ":/img/ocr.png",
        ":/img/face.png",
        ":/img/hash.png",
        ":/img/dedup.png",
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
