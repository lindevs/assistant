#include "ui/MainWindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QFontDatabase::addApplicationFont(":/font/OpenSans-Regular.ttf");
    QApplication::setFont(QFont("Open Sans"));

    move(screen()->geometry().center() - frameGeometry().center());

    menu = new Menu();
    ui->horizontalLayout->addWidget(menu);
    menuItemClicked(menu->getItemIdx());
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);

    connect(menu, &Menu::clicked, this, &MainWindow::menuItemClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::menuItemClicked(int itemIdx) {
    removeMenuItem(qrArea);
    removeMenuItem(ocrArea);
    removeMenuItem(faceArea);
    removeMenuItem(hashArea);
    removeMenuItem(dedupArea);
    qrArea = nullptr;
    ocrArea = nullptr;
    faceArea = nullptr;
    hashArea = nullptr;
    dedupArea = nullptr;

    switch (itemIdx) {
        case 0:
            qrArea = new Qr::Area(this);
            ui->horizontalLayout->addWidget(qrArea);
            break;
        case 1:
            ocrArea = new Ocr::Area(this);
            ui->horizontalLayout->addWidget(ocrArea);
            break;
        case 2:
            faceArea = new Face::Area(this);
            ui->horizontalLayout->addWidget(faceArea);
            break;
        case 3:
            hashArea = new Hash::Area(this);
            ui->horizontalLayout->addWidget(hashArea);
            break;
        case 4:
            dedupArea = new Dedup::Area(this);
            ui->horizontalLayout->addWidget(dedupArea);
            break;
        default:
            break;
    }
}

void MainWindow::removeMenuItem(QWidget *item) {
    if (item != nullptr) {
        ui->horizontalLayout->removeWidget(item);
        delete item;
    }
}
