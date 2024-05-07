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

    void adjustHeight();

    void adjustLineSpacing();
};

#endif //ASSISTANT_UI_MESSAGE_LABEL_H
