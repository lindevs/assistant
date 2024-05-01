#ifndef ASSISTANT_MAINWINDOW_H
#define ASSISTANT_MAINWINDOW_H

#include <QMainWindow>
#include "ui/Menu.h"
#include "ui/qr/Area.h"

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
    Ui::MainWindow *ui;

    void menuItemClicked(int item);
};

#endif //ASSISTANT_MAINWINDOW_H
