#include "ui/MainWindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());

    menu = new Menu();
    ui->horizontalLayout->addWidget(menu);
    menuItemClicked(0);
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);

    connect(menu, &Menu::clicked, this, &MainWindow::menuItemClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::menuItemClicked(int itemIdx) {
    switch (itemIdx) {
        case 0:
            qrArea = new Qr::Area(this);
            ui->horizontalLayout->addWidget(qrArea);
            break;
        default:
            break;
    }
}
