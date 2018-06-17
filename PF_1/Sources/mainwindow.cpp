#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <analisispgm.h>

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

void MainWindow::on_btn_carimag_clicked()
{
    int w = ui->ulbl_imagori->width();
    int h = ui->ulbl_imagori->height();
    QPixmap imagen1("img1.pgm");
    QPixmap imagen2("img2.pgm");
    QPixmap imagen3("img3.pgm");
    QPixmap imagen4("img4.pgm");


    if(ui->rb_imag1->isChecked())
    {
        ui->ulbl_imagori->setPixmap(imagen1.scaled(w,h,Qt::KeepAspectRatio));
    }

    else if(ui->rb_imag2->isChecked())
    {
        ui->ulbl_imagori->setPixmap(imagen2.scaled(w,h,Qt::KeepAspectRatio));
    }

    else if(ui->rb_imag3->isChecked())
    {
        ui->ulbl_imagori->setPixmap(imagen3.scaled(w,h,Qt::KeepAspectRatio));
    }

    else if(ui->rb_imag4->isChecked())
    {
        ui->ulbl_imagori->setPixmap(imagen4.scaled(w,h,Qt::KeepAspectRatio));
    }

    else
    {
        QMessageBox::information(this,"Error","Selecciona una imagen");
    }
}

void MainWindow::on_btn_iniana_clicked()
{
    IMAGEN imagenori;
    IMAGEN imagenana;
    char nombre[100];
    int tipo;

    if(ui->rb_imag1->isChecked())
    {
        strncpy(nombre, "img1.pgm", sizeof(nombre));
    }

    else if(ui->rb_imag2->isChecked())
    {
        strncpy(nombre, "img2.pgm", sizeof(nombre));
    }

    else if(ui->rb_imag3->isChecked())
    {
        strncpy(nombre, "img3.pgm", sizeof(nombre));
    }

    else if(ui->rb_imag4->isChecked())
    {
        strncpy(nombre, "img4.pgm", sizeof(nombre));
    }

    else
    {
        QMessageBox::information(this,"Error","Carga una imagen");
    }


    tipo = tipo_imagen(nombre);

    if(tipo == 1)
    {
        imagenori = leer_imagen(nombre);
        mostrar_datos_imagen(&imagenori);
        imagenana = duplicar_imagen(&imagenori);
        mostrar_datos_imagen(&imagenana);
        negativo_imagen(&imagenana);
        recubrimiento_imagen(&imagenana);
        guardar_imagen(&imagenana);
    }
}


void MainWindow::on_btn_mostrar_clicked()
{
    QPixmap imagana1("Dup_img1.pgm");
    QPixmap imagana2("Dup_img2.pgm");
    QPixmap imagana3("Dup_img3.pgm");
    QPixmap imagana4("Dup_img4.pgm");


    int w = ui->ulbl_imagori->width();
    int h = ui->ulbl_imagori->height();

    if(ui->rb_imag1->isChecked())
    {
        ui->ulbl_imagpro->setPixmap(imagana1.scaled(w,h,Qt::KeepAspectRatio));
    }

    else if(ui->rb_imag2->isChecked())
    {
        ui->ulbl_imagpro->setPixmap(imagana2.scaled(w,h,Qt::KeepAspectRatio));
    }

    else if(ui->rb_imag3->isChecked())
    {
        ui->ulbl_imagpro->setPixmap(imagana3.scaled(w,h,Qt::KeepAspectRatio));
    }

    else if(ui->rb_imag4->isChecked())
    {
        ui->ulbl_imagpro->setPixmap(imagana4.scaled(w,h,Qt::KeepAspectRatio));
    }

    else
    {
        QMessageBox::information(this,"Error","Análisis Incompleto");
    }
}

