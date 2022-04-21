#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

class ImageLabel : public QLabel
{
private:
    QString filePath;
public:
    ImageLabel(QWidget *parent = nullptr) : QLabel(parent){}
    QImage BlurImage(QImage source, int blurRadius);
    void SetPathToFile(QString path){if(!path.isEmpty()) filePath = path;}
    QString GetPathToFile(){return filePath;}
    void SetImage(QString path);
public slots:
    void setBlurEffect(int blurRadius);
};

QImage ImageLabel::BlurImage(QImage source, int blurRadius)
{
    if(source.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));

    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0, 0, source.width(), source.height()));
    return result;
}

void ImageLabel::SetImage(QString path)
{
    this->SetPathToFile(path);
    this->setPixmap(QPixmap::fromImage(QImage(path).scaled(this->width(), this->height(), Qt::KeepAspectRatio)));

}

void ImageLabel::setBlurEffect(int blurRadius)
{
    if(!filePath.isEmpty())
    {
        QImage newImage = BlurImage(QImage(filePath), blurRadius);
        this->setPixmap(QPixmap::fromImage(newImage.scaled(this->width(), this->height(), Qt::KeepAspectRatio)));
    }
}
#endif // IMAGELABEL_H
