#ifndef ASSISTANT_UI_SD_SETTINGS_H
#define ASSISTANT_UI_SD_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include <QCheckBox>
#include "ui/SelectBox.h"
#include "ui/Slider.h"
#include "core/structures.h"

namespace Sd {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        SelectBox model;
        Slider steps;
        QCheckBox autosave;

        QString style = R"(
            QGroupBox {
                border: 1px solid #ccc;
                border-radius: 4px;
            }
            QCheckBox {
                font-size: 12px;
            }
        )";

        const QList<QString> models = {
            "Stable Diffusion v1.5",
            "Stable Diffusion 3.5 Medium",
            "Stable Diffusion 3.5 Large",
        };
    };
}

#endif //ASSISTANT_UI_SD_SETTINGS_H
