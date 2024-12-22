#ifndef ASSISTANT_UI_FACE_SETTINGS_H
#define ASSISTANT_UI_FACE_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include <QCheckBox>
#include "ui/BackendSelectBox.h"
#include "core/structures.h"

namespace Face {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        BackendSelectBox backend;
        SelectBox detectionModel;
        SelectBox mattingModel;
        QCheckBox blur;
        QCheckBox idPhoto;
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

        const QList<QString> detectionModels = {
            "libfacedetection",
            "YOLOv5-BlazeFace",
            "YOLOv5n-0.5-Face",
            "YOLOv5n-Face",
            "YOLOv5s-Face",
            "YOLOv5m-Face",
            "YOLOv5l-Face",
            "YOLOv7-Lite-t-Face",
            "YOLOv7-Lite-s-Face",
            "YOLOv7-Tiny-Face",
            "YOLOv7s-Face",
            "YOLOv7-Face",
            "YOLOv7-W6-Face",
            "YOLOv8n-Face-Lindevs",
            "YOLOv8s-Face-Lindevs",
            "YOLOv8m-Face-Lindevs",
            "YOLOv8l-Face-Lindevs",
            "YOLOv8x-Face-Lindevs",
            "YOLOv9t-Face-Lindevs",
            "YOLOv9s-Face-Lindevs",
            "YOLOv9m-Face-Lindevs",
            "YOLOv9c-Face-Lindevs",
            "YOLOv9e-Face-Lindevs",
            "UltraFace-slim-320",
            "UltraFace-RFB-320",
            "UltraFace-slim-640",
            "UltraFace-RFB-640",
            "YOLO-FaceV2",
            "RetinaFace ResNet-50",
            "RetinaFace MobileNet-0.25",
        };

        const QList<QString> mattingModels = {
            "MODNet (Photographic)",
        };
    };
}

#endif //ASSISTANT_UI_FACE_SETTINGS_H
