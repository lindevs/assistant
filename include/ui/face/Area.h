#ifndef ASSISTANT_UI_FACE_AREA_H
#define ASSISTANT_UI_FACE_AREA_H

#include <QThread>
#include "ui/UploadBar.h"
#include "ui/face/Settings.h"
#include "ui/Chat.h"
#include "face/QFaceDetection.h"

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
        QFaceDetection faceDetection;
        QThread thread;
        Params currentParams;
        bool started = false;

        void detect(const cv::Mat &img);
    };
}

#endif //ASSISTANT_UI_FACE_AREA_H
