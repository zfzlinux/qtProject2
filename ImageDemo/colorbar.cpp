#include "colorbar.h"
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QPainter>
#include <QPen>
colorbar::colorbar(QWidget *parent) : QWidget(parent)
{
    m_Image = NULL;

    loadColorFile(":/ONDT_Amplitude.pal");

}

void colorbar::paintEvent(QPaintEvent *e)
{
    m_Image->fill(Qt::white);
    uchar *p_imageBits = m_Image->bits();
    int _nbytePerLine =m_Image->bytesPerLine();
    QPainter _painter(m_Image);
    int _nWidth = this->width();
    int _nHeight = this->height();
    int _nColorIndex;
    QPen _pen;
    for(int i =1; i<_nHeight;i++)
    {
        _nColorIndex =255-(i * 255 / _nHeight);
        _pen.setColor(m_colorPreview.at(_nColorIndex));
        _painter.setPen(_pen);
        _painter.drawLine(QPointF(0,i),QPointF(_nWidth,i));
        //取出颜色值
         m_pixColor[_nColorIndex] = *(ushort *)(p_imageBits + i*(_nbytePerLine)+1*2);

    }
    QPainter pa(this);
    pa.drawImage(0,0,*m_Image);

}

void colorbar::resizeEvent(QResizeEvent *e)
{
    if(m_Image)
    {
        delete m_Image;
        m_Image = NULL;
    }
    m_Image = new QImage(this->size(),QImage::Format_RGB16);
}

void colorbar::loadColorFile(QString path)
{
    if(path.isEmpty()){return ;};
    int i;
    i =0;
    int red,green,blue,fire;
    m_colorPreview.clear();
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xmlReader(&file);

        while(!xmlReader.atEnd())
        {
            //读取下一个节点
            xmlReader.readNext();
//           if(xmlReader.isStartElement() && xmlReader.name()=="SpecialColors")
//           {
//               while(!(xmlReader.isEndElement() && xmlReader.name()=="SpecialColors"))
//               {
//                    xmlReader.readNext();
//                    if(xmlReader.isStartElement() && xmlReader.name()== "Color")
//                    {
//                        red = xmlReader.attributes().value("R").toInt();
//                        green =xmlReader.attributes().value("G").toInt();
//                        blue = xmlReader.attributes().value("B").toInt();
//                        m_colorPreview.append(QColor(red,green,blue));
//                    }
//               }

//           }
           if(xmlReader.isStartElement() && xmlReader.name() == "MainColors")
           {
               while(!(xmlReader.isEndElement() && xmlReader.name() == "MainColors"))
               {
                   xmlReader.readNext();
                   if(xmlReader.isStartElement() && xmlReader.name()== "Color")
                   {
                       red = xmlReader.attributes().value("R").toInt();
                       green =xmlReader.attributes().value("G").toInt();
                       blue = xmlReader.attributes().value("B").toInt();
                       m_colorPreview.append(QColor(red,green,blue));
                   }
               }
           }
        }

    }
    file.close();
}

QVector<QColor> colorbar::getColor()
{
    return m_colorPreview;
}

ushort colorbar::getPixColor(int pixel)
{
    return m_pixColor[pixel];
}



