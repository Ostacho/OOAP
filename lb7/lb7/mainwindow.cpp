#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ButtonHandler.h"
#include "KeyHandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto* buttonHandler = new ButtonHandler();
    auto* keyHandler = new KeyHandler();

    buttonHandler->setNext(keyHandler);
    handler = buttonHandler;

    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
        handler->handleEvent("button_click");
    });

    connect(ui->actionSimulate_Key_Event, &QAction::triggered, this, [=]() {
        handler->handleEvent("key_press");
    });

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keyText = event->text();
    if (!keyText.isEmpty()) {
        qDebug() << "Натиснута клавіша:" << keyText;
        handler->handleEvent("key_press");
    }
}
