#ifndef ASSISTANT_UI_MESSAGE_DIALOG_H
#define ASSISTANT_UI_MESSAGE_DIALOG_H

#include <QDialog>
#include <QLabel>

class MessageDialog : public QDialog {
Q_OBJECT

public:
    explicit MessageDialog(const QString &title, QWidget *parent);

    void setText(const QString &text);

private:
    QLabel label;

    QString style = R"(
        QLabel {
            color: #000;
            font-size: 14px;
        }
    )";
};

#endif //ASSISTANT_UI_MESSAGE_DIALOG_H
