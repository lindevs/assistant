#ifndef ASSISTANT_UI_UPLOAD_BAR_H
#define ASSISTANT_UI_UPLOAD_BAR_H

#include <QWidget>
#include <QSettings>
#include <opencv2/core/mat.hpp>

class UploadBar : public QWidget {
Q_OBJECT

public:
    explicit UploadBar(QWidget *parent = nullptr, int type = TYPE_IMAGE);

    static const int TYPE_DIRECTORY = 0;
    static const int TYPE_IMAGE = 1;

signals:

    void imageSelected(const cv::Mat &img);

    void directorySelected(const QString &path);

private:
    QSettings settings;

    QString style = R"(
        QPushButton {
            border-radius: 3px;
            padding: 10px 30px;
            font-size: 14px;
            color: #fff;
            font-weight: bold;
        }
        QPushButton {
            background-color: #007bff;
            border: 1px solid #007bff;
        }
        QPushButton:hover {
            background-color: #0056b3;
            border-color: #0056b3;
        }
        QPushButton:pressed {
            background-color: #004080;
            border-color: #00264d;
        }
        QPushButton:disabled {
            background-color: rgba(13, 110, 253, 0.65);
            border-color: #0d6efd;
        }
        QFileDialog QWidget {
            font-size: 12px;
        }
    )";

    const QList<QString> text = {
        "Select Directory...",
        "Select Image...",
    };
};

#endif //ASSISTANT_UI_UPLOAD_BAR_H
