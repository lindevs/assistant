#ifndef ASSISTANT_UI_SD_AREA_H
#define ASSISTANT_UI_SD_AREA_H

#include <QThread>
#include "ui/TextBar.h"
#include "ui/sd/Settings.h"
#include "ui/Chat.h"
#include "sd/QStableDiffusion.h"

namespace Sd {
    class Area : public QWidget {
    Q_OBJECT

    public:
        explicit Area(QWidget *parent = nullptr);

        ~Area() override;

    private:
        Chat *chat;
        Settings *settings;
        TextBar *textBar;
        QStableDiffusion diffusion;
        QThread thread;
        Params currentParams;
        bool started = false;

        void generate();

        void onGenerated(const cv::Mat &img);
    };
}

#endif //ASSISTANT_UI_SD_AREA_H
