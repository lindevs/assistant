#ifndef ASSISTANT_UI_HASH_AREA_H
#define ASSISTANT_UI_HASH_AREA_H

#include <QThread>
#include "ui/UploadBar.h"
#include "ui/hash/Settings.h"
#include "ui/Chat.h"
#include "hash/QHashCalculation.h"

namespace Hash {
    class Area : public QWidget {
    Q_OBJECT

    public:
        explicit Area(QWidget *parent = nullptr);

        ~Area() override;

    private:
        Chat *chat;
        Settings *settings;
        UploadBar *uploadBar;
        QHashCalculation hashCalculation;
        QThread thread;
        Params currentParams;
        bool started = false;

        void process(const cv::Mat &img);

        void calculate(const cv::Mat &img);
    };
}

#endif //ASSISTANT_UI_HASH_AREA_H
