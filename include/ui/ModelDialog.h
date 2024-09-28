#ifndef ASSISTANT_UI_MODEL_DIALOG_H
#define ASSISTANT_UI_MODEL_DIALOG_H

#include "core/models.h"
#include "ui/MessageDialog.h"

class ModelDialog : public MessageDialog {
Q_OBJECT

public:
    explicit ModelDialog(const QString &title, QWidget *parent);

    void setModel(const Model &model, const QString &path);
};

#endif //ASSISTANT_UI_MODEL_DIALOG_H
