#include "ui/ModelDialog.h"

ModelDialog::ModelDialog(const QString &title, QWidget *parent) : MessageDialog(title, parent) {
}

void ModelDialog::setModel(const Model &model, const QString &path) {
    setText(
        QString("Unable to find model '%1'.<br>Download it from <a href=\"%2\">%3</a>").arg(
            QString(path) + "/" + model.file,
            model.url,
            model.url
        )
    );
}
