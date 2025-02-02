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
            "Stable Diffusion v2.1",
            "Stable Diffusion XL",
            "Stable Diffusion 3 Medium",
            "Stable Diffusion 3.5 Medium",
            "Stable Diffusion 3.5 Large",
            "FLUX.1 [schnell]",
            "FLUX.1 [dev]",
        };
    };
}

#endif //ASSISTANT_UI_SD_SETTINGS_H
