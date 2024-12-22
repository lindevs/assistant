#include "ui/BackendSelectBox.h"
#include "utils/OrtInfo.h"

BackendSelectBox::BackendSelectBox(QWidget *parent) : SelectBox(parent) {
    setText("Backend");

    std::vector<Core::Backend> supportedBackends = OrtInfo::getBackends();
    for (Core::Backend &backend: supportedBackends) {
        addItem(backends[backend]);
    }
}

Core::Backend BackendSelectBox::getCurrentBackend() {
    return (Core::Backend) getCurrentIndex();
}
