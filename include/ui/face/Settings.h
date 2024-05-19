#ifndef ASSISTANT_UI_FACE_SETTINGS_H
#define ASSISTANT_UI_FACE_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include <QCheckBox>
#include "core/structures.h"

namespace Face {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        QCheckBox blur;
        QCheckBox autosave;
    };
}

#endif //ASSISTANT_UI_FACE_SETTINGS_H
