#include "ui/MenuItem.h"

MenuItem::MenuItem(const QString &icon, QWidget *parent) : QLabel(parent) {
    setCursor(Qt::PointingHandCursor);
    QPixmap pixmap(icon);
    setPixmap(pixmap);
}

void MenuItem::setActive(const bool active) {
    activeItem = active;
    if (active) {
        setStyleSheet("QLabel {background-color: #fff;}");
    } else {
        setStyleSheet("QLabel {background-color: transparent;}");
    }
}

bool MenuItem::isActive() const {
    return activeItem;
}

void MenuItem::mousePressEvent(QMouseEvent *) {
    emit clicked();
}
