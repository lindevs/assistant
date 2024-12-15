#ifndef ASSISTANT_UI_DEDUP_SETTINGS_H
#define ASSISTANT_UI_DEDUP_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include <QCheckBox>
#include "ui/SelectBox.h"
#include "core/structures.h"

namespace Dedup {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        SelectBox model;

        QString style = R"(
            QGroupBox {
                border: 1px solid #ccc;
                border-radius: 4px;
            }
        )";

        const QList<QString> models = {
            "MobileNetV3-Small-Dedup",
        };
    };
}

#endif //ASSISTANT_UI_DEDUP_SETTINGS_H
