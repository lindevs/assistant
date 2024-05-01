#ifndef ASSISTANT_UI_QR_CHAT_H
#define ASSISTANT_UI_QR_CHAT_H

#include <QScrollArea>
#include <QLayout>

namespace Qr {
    class Chat : public QScrollArea {
    Q_OBJECT

    public:
        explicit Chat(QWidget *parent = nullptr);

        void addText(const QString &username, const QString &text);

        void addText(const QString &username);

        void addImage(const QImage &img);

    private:
        QVBoxLayout layout;

        void scrollToBottom();
    };
}

#endif //ASSISTANT_UI_QR_CHAT_H
