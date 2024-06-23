#ifndef ASSISTANT_UI_MENU_ITEM_H
#define ASSISTANT_UI_MENU_ITEM_H

#include <QLabel>

class MenuItem : public QLabel {
Q_OBJECT

public:
    explicit MenuItem(const QString &icon, QWidget *parent = nullptr);

    void setActive(bool active);

    [[nodiscard]] bool isActive() const;

signals:

    void clicked();

protected:
    void mousePressEvent(QMouseEvent *) override;

private:
    bool activeItem = false;
};

#endif //ASSISTANT_UI_MENU_ITEM_H
