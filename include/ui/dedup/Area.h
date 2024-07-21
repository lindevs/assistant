#ifndef ASSISTANT_UI_DEDUP_AREA_H
#define ASSISTANT_UI_DEDUP_AREA_H

#include <QThread>
#include "ui/UploadBar.h"
#include "ui/dedup/Settings.h"
#include "ui/Chat.h"
#include "dedup/QImageDeduplication.h"

namespace Dedup {
    class Area : public QWidget {
    Q_OBJECT

    public:
        explicit Area(QWidget *parent = nullptr);

        ~Area() override;

    private:
        Chat *chat;
        Settings *settings;
        UploadBar *uploadBar;
        QImageDeduplication deduplication;
        QThread thread;
        Params currentParams;
        bool started = false;
        const size_t showLimit = 100;

        void findDuplicates(const QString &path);
    };
}

#endif //ASSISTANT_UI_DEDUP_AREA_H
