#ifndef ASSISTANT_UI_HASH_SETTINGS_H
#define ASSISTANT_UI_HASH_SETTINGS_H

#include <QGroupBox>
#include <QSettings>
#include "ui/SelectBox.h"
#include "core/structures.h"

namespace Hash {
    class Settings : public QGroupBox {
    Q_OBJECT

    public:
        explicit Settings(QWidget *parent = nullptr);

        Params getParams();

    private:
        QSettings settings;
        SelectBox algorithm;

        const QList<QString> algorithms = {
            "Average hash (AHash)",
            "Difference hash (DHash)",
            "Perceptual hash (PHash)",
        };
    };
}

#endif //ASSISTANT_UI_HASH_SETTINGS_H
