#ifndef ASSISTANT_UI_OCR_AREA_H
#define ASSISTANT_UI_OCR_AREA_H

#include <QThread>
#include "ui/UploadBar.h"
#include "ui/ocr/Settings.h"
#include "ui/Chat.h"
#include "ui/MessageDialog.h"
#include "ocr/QTesseract.h"

namespace Ocr {
    class Area : public QWidget {
    Q_OBJECT

    public:
        explicit Area(QWidget *parent = nullptr);

        ~Area() override;

    private:
        Chat *chat;
        Settings *settings;
        UploadBar *uploadBar;
        MessageDialog *dialog;
        QTesseract tesseract;
        QThread thread;
        Params currentParams;
        bool started = false;

        void process(const cv::Mat &img);

        void recognize(const cv::Mat &img);

        const QString tesseractUrl = "https://github.com/tesseract-ocr/tessdata";
    };
}

#endif //ASSISTANT_UI_OCR_AREA_H
