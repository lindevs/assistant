#ifndef ASSISTANT_UI_FACE_AREA_H
#define ASSISTANT_UI_FACE_AREA_H

#include <QThread>
#include "ui/UploadBar.h"
#include "ui/face/Settings.h"
#include "ui/Chat.h"
#include "ui/ModelDialog.h"
#include "face/QFaceDetection.h"
#include "face/QBackgroundMatting.h"
#include "face/IdPhotoCreator.h"

namespace Face {
    class Area : public QWidget {
    Q_OBJECT

    public:
        explicit Area(QWidget *parent = nullptr);

        ~Area() override;

    private:
        Chat *chat;
        Settings *settings;
        UploadBar *uploadBar;
        ModelDialog *dialog;
        QFaceDetection faceDetection;
        QBackgroundMatting backgroundMatting;
        IdPhotoCreator idPhotoCreator;
        QThread thread;
        bool started = false;

        Params currentParams;
        cv::Mat currentImg;
        std::vector<Detection> currentDetections;
        cv::Mat currentMatte;

        void process(const cv::Mat &img);

        void detect();

        void onDetected(const std::vector<Detection> &detections);

        void onMatteGenerated(const cv::Mat &matte);
    };
}

#endif //ASSISTANT_UI_FACE_AREA_H
