#ifndef ASSISTANT_UI_QR_AREA_H
#define ASSISTANT_UI_QR_AREA_H

#include "ui/TextBar.h"
#include "ui/qr/Settings.h"
#include "ui/Chat.h"
#include "qr/ZxingCpp.h"

namespace Qr {
    class Area : public QWidget {
    Q_OBJECT

    public:
        explicit Area(QWidget *parent = nullptr);

    private:
        Chat *chat;
        Settings *settings;
        TextBar *textBar;

        void generate();
    };
}

#endif //ASSISTANT_UI_QR_AREA_H
