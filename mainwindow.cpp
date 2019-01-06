#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, ui->openGLWidget, &GLWidget::animate);
    timer->start(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (timer->isActive()) {
        timer->stop();
        ui->pushButton->setText("Play");
    } else {
        timer->start(16);
        ui->pushButton->setText("Pause");
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    int fps = ui->horizontalSlider->value();
    timer->setInterval(fps);
}
