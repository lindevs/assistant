#ifndef ASSISTANT_SD_QSTABLE_DIFFUSION_H
#define ASSISTANT_SD_QSTABLE_DIFFUSION_H

#include <QObject>
#include "models/StableDiffusionModel.h"
#include "models/ProgressInterface.h"

class QStableDiffusion : public QObject, public ProgressInterface {
    Q_OBJECT

public:
    void start(const Sd::Params &params);

    void stop();

    void generate(const QString &text, const int &steps);

signals:
    void generated(const cv::Mat &img);

    void stepChanged(const int &step);

private:
    StableDiffusionModel *model = nullptr;

    void changeStep(const int &step) override;
};

#endif //ASSISTANT_SD_QSTABLE_DIFFUSION_H
