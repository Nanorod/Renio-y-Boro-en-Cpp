#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Elige"), "", tr(""));
    if (QString::compare(filename, QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if (valid)
        {
            image = image.scaledToWidth(ui->imagen->width(), Qt::SmoothTransformation);
            ui->imagen->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            //Error cargando
        }
    }

}

