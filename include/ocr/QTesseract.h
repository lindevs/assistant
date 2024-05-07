#ifndef ASSISTANT_OCR_QTESSERACT_H
#define ASSISTANT_OCR_QTESSERACT_H

#include <QObject>
#include <QImage>
#include "ocr/Tesseract.h"

class QTesseract : public QObject {
Q_OBJECT

public:
    void start(const Ocr::Params &params);

    void stop();

    void recognize(const QImage &img);

signals:

    void recognized(const QString &text);

private:
    Tesseract tesseract;
};

#endif //ASSISTANT_OCR_QTESSERACT_H
