#ifndef ASSISTANT_UI_SD_PROMPT_BAR_H
#define ASSISTANT_UI_SD_PROMPT_BAR_H

#include "ui/MessageEdit.h"

class TextBar : public QWidget {
Q_OBJECT

public:
    explicit TextBar(QWidget *parent = nullptr);

    QString getText();

    void clearText();

signals:

    void generateButtonClicked();

private:
    MessageEdit textEdit;

    QString style = R"(
        QTextEdit {
            padding: 4px;
            border: 1px solid #ccc;
            border-radius: 4px;
            color: #333;
            font-size: 14px;
            background-color: #fff;
        }
        QTextEdit:focus {
            border-color: #66afe9;
        }
        QTextEdit:disabled {
            background-color: #e9ecef;
            border-color: #ced4da;
            color: #212529;
        }
        QPushButton {
            border-radius: 3px;
            padding: 10px 30px;
            font-size: 14px;
            color: #fff;
            font-weight: bold;
        }
        QPushButton {
            background-color: #007bff;
            border: 1px solid #007bff;
        }
        QPushButton:hover {
            background-color: #0056b3;
            border-color: #0056b3;
        }
        QPushButton:pressed {
            background-color: #004080;
            border-color: #00264d;
        }
        QPushButton:disabled {
            background-color: rgba(13, 110, 253, 0.65);
            border-color: #0d6efd;
        }
    )";
};

#endif //ASSISTANT_UI_SD_PROMPT_BAR_H
