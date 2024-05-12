#ifndef ASSISTANT_UI_QR_SETTINGS_H
#define ASSISTANT_UI_QR_SETTINGS_H

#include <QGroupBox>
#include "ui/Slider.h"
#include "ui/CheckBox.h"
#include "core/structures.h"

namespace Qr {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        Slider width;
        Slider height;
        CheckBox autosave;
    };
}

#endif //ASSISTANT_UI_QR_SETTINGS_H
