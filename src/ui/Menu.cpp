#include <QLayout>
#include "ui/Menu.h"

Menu::Menu(QWidget *parent) : QGroupBox(parent) {
    setStyleSheet(style);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    for (int i = 0; i < (int) icons.size(); ++i) {
        auto *item = new MenuItem(icons[i]);
        layout->addWidget(item);
        items.emplace_back(item);
        if (itemIdx == i) {
            item->setActive(true);
        }

        connect(item, &MenuItem::clicked, [=] {
            if (itemIdx == i) {
                return;
            }
            for (auto &element: items) {
                element->setActive(false);
            }
            item->setActive(true);
            itemIdx = i;
            emit clicked(i);
        });
    }

    layout->setAlignment(Qt::AlignTop);
}
