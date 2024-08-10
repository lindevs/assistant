#ifndef ASSISTANT_UI_FACE_SETTINGS_H
#define ASSISTANT_UI_FACE_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include <QCheckBox>
#include "ui/SelectBox.h"
#include "core/structures.h"

namespace Face {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        SelectBox model;
        QCheckBox blur;
        QCheckBox autosave;

        const QList<QString> models = {
            "libfacedetection",
            "YOLOv8n-Face-Lindevs",
            "YOLOv8s-Face-Lindevs",
            "YOLOv8m-Face-Lindevs",
            "YOLOv8l-Face-Lindevs",
            "YOLOv8x-Face-Lindevs",
            "UltraFace-slim-320",
            "UltraFace-RFB-320",
            "UltraFace-slim-640",
            "UltraFace-RFB-640",
        };
    };
}

#endif //ASSISTANT_UI_FACE_SETTINGS_H
