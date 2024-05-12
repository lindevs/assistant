#ifndef ASSISTANT_UI_CHAT_H
#define ASSISTANT_UI_CHAT_H

#include <QScrollArea>
#include <QProgressBar>
#include <QLayout>
#include <opencv2/core/mat.hpp>

class Chat : public QScrollArea {
Q_OBJECT

public:
    explicit Chat(QWidget *parent = nullptr);

    void addText(const QString &text);

    void addUsername(const QString &username);

    void addImage(const cv::Mat &img);

    void addProgressBar();

    void removeProgressBar();

private:
    QVBoxLayout layout;
    QProgressBar progressBar;

    void scrollToBottom();
};

#endif //ASSISTANT_UI_CHAT_H
