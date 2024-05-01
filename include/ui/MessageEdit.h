#ifndef ASSISTANT_UI_MESSAGE_EDIT_H
#define ASSISTANT_UI_MESSAGE_EDIT_H

#include <QTextEdit>

class MessageEdit : public QTextEdit {
Q_OBJECT

public:
    explicit MessageEdit(QWidget *parent = nullptr);

private:
    const int MAX_HEIGHT = 331;

    void adjustHeight();
};

#endif //ASSISTANT_UI_MESSAGE_EDIT_H
