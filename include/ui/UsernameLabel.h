#ifndef ASSISTANT_UI_USERNAME_LABEL_H
#define ASSISTANT_UI_USERNAME_LABEL_H

#include <QLabel>

class UsernameLabel : public QLabel {
Q_OBJECT

public:
    explicit UsernameLabel(QWidget *parent = nullptr);

private:
    QString style = R"(
        QLabel {
            font-weight:bold;
            font-size:14px;
        }
    )";
};

#endif //ASSISTANT_UI_USERNAME_LABEL_H
