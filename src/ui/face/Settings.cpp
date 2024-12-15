#include <QLayout>
#include "ui/Line.h"
#include "ui/face/Settings.h"
#include "core/app.h"

Face::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet(style);

    settings.beginGroup("face");

    auto *layout = new QVBoxLayout(this);

    detectionModel.setText("Face detection model");
    detectionModel.addItems(detectionModels);
    detectionModel.setCurrenctIndex(settings.value("detection_model", 0).toInt());
    connect(&detectionModel, &SelectBox::currentIndexChanged, [=] (int index) {
        settings.setValue("detection_model", index);
    });
    layout->addWidget(&detectionModel);

    blur.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    blur.setText("Blur faces");
    blur.setChecked(settings.value("blur", false).toBool());
    connect(&blur, &QCheckBox::clicked, [=] (bool checked) {
        settings.setValue("blur", checked);
    });
    layout->addWidget(&blur);

    autosave.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    autosave.setText("Save output automatically");
    autosave.setChecked(settings.value("autosave", false).toBool());
    connect(&autosave, &QCheckBox::clicked, [=] (bool checked) {
        settings.setValue("autosave", checked);
    });
    layout->addWidget(&autosave);

    layout->addWidget(new Line());

    idPhoto.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    idPhoto.setText("Make ID photo");
    idPhoto.setChecked(settings.value("id_photo", false).toBool());
    connect(&idPhoto, &QCheckBox::clicked, [=] (bool checked) {
        settings.setValue("id_photo", checked);
    });
    layout->addWidget(&idPhoto);

    mattingModel.setText("Background matting model");
    mattingModel.addItems(mattingModels);
    mattingModel.setCurrenctIndex(settings.value("matting_model", 0).toInt());
    connect(&mattingModel, &SelectBox::currentIndexChanged, [=] (int index) {
        settings.setValue("matting_model", index);
    });
    layout->addWidget(&mattingModel);

    layout->setAlignment(Qt::AlignTop);
}

Face::Params Face::Settings::getParams() {
    Params params;
    params.detectionModel.id = detectionModel.getCurrentIndex();
    params.detectionModel.file = MODEL_FILES[detectionModel.getCurrentIndex()];
    params.detectionModel.url = MODEL_URLS[detectionModel.getCurrentIndex()];
    params.mattingModel.id = mattingModel.getCurrentIndex();
    params.mattingModel.file = Matting::MODEL_FILES[mattingModel.getCurrentIndex()];
    params.mattingModel.url = Matting::MODEL_URLS[mattingModel.getCurrentIndex()];
    params.blur = blur.isChecked();
    params.idPhoto = idPhoto.isChecked();
    params.autosave = autosave.isChecked();

    return params;
}
