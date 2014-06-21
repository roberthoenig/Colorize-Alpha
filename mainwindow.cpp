#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <iostream>
#include <QDebug>
#include <vector>
#include <math.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(farbeEinlesen()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(bildEinlesen()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bildEinlesen() {
    std::string path = ui->lineEdit->text().toStdString();

    image = new QImage(path.c_str());

    if(image->isNull()==false) {

        //alpha in bild kolorieren
        QSize sizeImage;
        int percent = 0;
        int height, width;
        sizeImage = image->size();
        width = sizeImage.width();
        height = sizeImage.height();

        bool useAlpha = false;
        const uchar* pixelData = image->bits();
        int bytes = image->byteCount();


        std::vector<position> pixels(0);

        for (const QRgb* pixel = reinterpret_cast<const QRgb*>(pixelData); bytes > 0; pixel++, bytes -= sizeof(QRgb)) {
            if (qAlpha(*pixel) != UCHAR_MAX) {
                int pos = (image->byteCount()-bytes)/sizeof(QRgb);
                position posC;
                posC.x = pos%width;
                posC.y = (pos-(pos%width))/width;
                posC.alpha = qAlpha(*pixel);
                pixels.push_back(posC);
                useAlpha = true;
            }
        }

        for(uint i=0; i<pixels.size(); ++i) {
                    position p = pixels.at(i);

                    double influence = (double)(255-std::abs(p.alpha)) / (double)255;
                    QColor oldColor = image->pixel(p.x, p.y);
                    QColor newColor;
                    newColor.setAlpha(0);
                    newColor.setRed((influence*(double)color.red()) + ((1-influence)*(double)oldColor.red()));
                    newColor.setGreen((influence*(double)color.green()) + ((1-influence)*(double)oldColor.green()));
                    newColor.setBlue((influence*(double)color.blue()) + ((1-influence)*(double)oldColor.blue()));

                    image->setPixel(p.x, p.y, newColor.rgb());

                    int interval = pixels.size() / 100;
                    if(percent*interval < i) {
                        ui->label_4->setText("progress: "+QString::number(percent++));
                    }
        }

        image->save(ui->lineEdit_2->text());
        ui->label_4->setText("Finished");
    } else {
        ui->label_4->setText("Don't trick me\nwith wrong \nfile names!");
    }
}

void MainWindow::farbeEinlesen() {
    color = QColorDialog::getColor();
}
