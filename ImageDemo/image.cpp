#include "image.h"
#include <QPainter>
Image::Image(QWidget *parent) : QWidget(parent)
{
    p_image =NULL;
}

void Image::paintEvent(QPaintEvent *e)
{
    p_image->fill(Qt::black);
    uchar* p_imagebits = p_image->bits();
    int bytesPerLine = p_image->bytesPerLine();
    int _nWdith = this->width();
    int _nHeight = this->height();
    int _nCurrentPos;
    int _nColorindex;
    _nCurrentPos =0;
    for(int y =0;y<_nHeight;y++)
    {
        for(int x =0;x<_nWdith;x++)
        {
           _nCurrentPos = y*_nWdith +x;
           //画图。。。
           _nColorindex = _nCurrentPos % 255;
           *(ushort *)(p_imagebits+y*bytesPerLine+x*2) = m_colorbar->getPixColor(_nColorindex) ;
        }
    }
    QPainter painter(this);
    painter.drawImage(0,0,*p_image);
}

void Image::resizeEvent(QResizeEvent *e)
{
    if(p_image)
    {
        delete p_image;
        p_image = NULL;
    }
    p_image = new QImage(this->size(),QImage::Format_RGB16);
}

