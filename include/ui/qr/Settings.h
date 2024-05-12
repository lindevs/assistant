#ifndef ASSISTANT_UI_QR_SETTINGS_H
#define ASSISTANT_UI_QR_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include <QCheckBox>
#include "ui/Slider.h"
#include "core/structures.h"

namespace Qr {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        Slider width;
        Slider height;
        QCheckBox autosave;
    };
}

#endif //ASSISTANT_UI_QR_SETTINGS_H
