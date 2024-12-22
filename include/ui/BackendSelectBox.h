#ifndef ASSISTANT_UI_BACKEND_SELECT_BOX_H
#define ASSISTANT_UI_BACKEND_SELECT_BOX_H

#include "ui/SelectBox.h"
#include "core/app.h"

class BackendSelectBox : public SelectBox {
    Q_OBJECT

public:
    explicit BackendSelectBox(QWidget *parent = nullptr);

    Core::Backend getCurrentBackend();

private:

    std::map<Core::Backend, QString> backends = {
        {Core::Backend::CPU, "CPU"},
        {Core::Backend::CUDA, "CUDA"},
    };
};

#endif //ASSISTANT_UI_BACKEND_SELECT_BOX_H
