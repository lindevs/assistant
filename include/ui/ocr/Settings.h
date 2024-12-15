#ifndef ASSISTANT_UI_OCR_SETTINGS_H
#define ASSISTANT_UI_OCR_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include "ui/SelectBox.h"
#include "core/structures.h"

namespace Ocr {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        SelectBox language;

        QString style = R"(
            QGroupBox {
                border: 1px solid #ccc;
                border-radius: 4px;
            }
        )";

        const QList<QString> languages = {
            "English",
            "Danish",
            "German",
            "French",
        };
        const char *codes[4] = {
            "eng",
            "dan",
            "deu",
            "fra",
        };
    };
}

#endif //ASSISTANT_UI_OCR_SETTINGS_H
