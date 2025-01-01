#ifndef ASSISTANT_MODELS_PROGRESS_INTERFACE_H
#define ASSISTANT_MODELS_PROGRESS_INTERFACE_H

class ProgressInterface {
public:
    virtual ~ProgressInterface() = default;

    virtual void changeStep(const int &step) = 0;
};

#endif //ASSISTANT_MODELS_PROGRESS_INTERFACE_H
