#include "widget.h"

#include <QApplication>

#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

#include <QFileDialog>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include <imagelabel.h>


int main(int argc, char *argv[])
{
    QString filePath;
    QApplication a(argc, argv);
    Widget w;
    auto vbox = new QVBoxLayout(&w);
    auto label = new ImageLabel(&w);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    label->setFixedSize(640, 480);
    auto slider = new QSlider(&w);
    slider->setOrientation(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(10);
    auto openButton = new QPushButton("Open file", &w);
    vbox->addWidget(label);
    vbox->addWidget(slider);
    vbox->addWidget(openButton);
    w.setWindowTitle("Blur effect");

    QObject::connect(openButton, &QPushButton::pressed, [&filePath, label](){
        filePath = QFileDialog::getOpenFileName(nullptr, "Open file", "C:\\Qt\\Projects\\HomeWork38_5_3", "image files(*.jpg)");
        label->SetImage(filePath);
    });
    QObject::connect(slider, &QSlider::valueChanged, label, &ImageLabel::setBlurEffect);
    w.show();
    return a.exec();
}
