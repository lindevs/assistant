#ifndef ASSISTANT_UI_MESSAGE_LABEL_H
#define ASSISTANT_UI_MESSAGE_LABEL_H

#include <QTextEdit>

class MessageLabel : public QTextEdit {
Q_OBJECT

public:
    explicit MessageLabel(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QTextBlockFormat format;
    int currentHeight = 0;

    QString style = R"(
        QTextEdit {
            background-color:#f5f5f4;
            padding:8px;
            border-radius:8px;
            font-size:14px;
        }
    )";

    void adjustHeight();

    void adjustLineSpacing();
};

#endif //ASSISTANT_UI_MESSAGE_LABEL_H
