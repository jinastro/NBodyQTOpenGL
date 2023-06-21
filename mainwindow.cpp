#include <mainwindow.h>
#include <./ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,800);
//    setCentralWidget(ui->openGLWidget);

    connect(ui->actStart, &QAction::triggered,this,[=](){
        ui->openGLWidget->startSimulation();
    });

    connect(ui->actStop, &QAction::triggered,this,[=](){
        ui->openGLWidget->stopSimulation();
    });

    connect(ui->actReset, &QAction::triggered,this,[=](){
        ui->openGLWidget->resetSimulation();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

