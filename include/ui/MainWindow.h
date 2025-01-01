#ifndef ASSISTANT_MAINWINDOW_H
#define ASSISTANT_MAINWINDOW_H

#include <QMainWindow>
#include "ui/Menu.h"
#include "ui/qr/Area.h"
#include "ui/ocr/Area.h"
#include "ui/face/Area.h"
#include "ui/hash/Area.h"
#include "ui/dedup/Area.h"
#include "ui/sd/Area.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Menu *menu;
    Qr::Area *qrArea = nullptr;
    Ocr::Area *ocrArea = nullptr;
    Face::Area *faceArea = nullptr;
    Hash::Area *hashArea = nullptr;
    Dedup::Area *dedupArea = nullptr;
    Sd::Area *sdArea = nullptr;
    Ui::MainWindow *ui;

    void menuItemClicked(int item);

    void removeMenuItem(QWidget *item);
};

#endif //ASSISTANT_MAINWINDOW_H
