#include "aspectratiopixmaplabel.h"
//#include <QDebug>

AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget *parent) :
    QLabel(parent),_isHidden(false)
{
    this->setMinimumSize(1,1);
    setScaledContents(false);
}

void AspectRatioPixmapLabel::setPixmap ( const QPixmap & p)
{
    pix = p;
    QLabel::setPixmap(scaledPixmap());
}

int AspectRatioPixmapLabel::heightForWidth( int width ) const
{
    return pix.isNull() ? this->height() : ((qreal)pix.height()*width)/pix.width();
}

QSize AspectRatioPixmapLabel::sizeHint() const
{
    int w = this->width();
    return QSize( w, heightForWidth(w) );
}

QPixmap AspectRatioPixmapLabel::scaledPixmap() const
{
    return pix.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void AspectRatioPixmapLabel::hideImage(){
    _isHidden=true;
    QLabel::setPixmap(QPixmap());
}

void AspectRatioPixmapLabel::showImage()
{
    _isHidden=false;
    QLabel::setPixmap(pix);
}

bool AspectRatioPixmapLabel::isHidden()
{
    return _isHidden;
}

void AspectRatioPixmapLabel::resizeEvent(QResizeEvent * e)
{
    if(!pix.isNull() && !_isHidden)
        QLabel::setPixmap(scaledPixmap());
}
