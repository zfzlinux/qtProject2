#include "ascan.h"
#include <QPainter>
Ascan::Ascan(QWidget *parent) : QWidget(parent)
{

}

void Ascan::show()
{
    this->update();
}

void Ascan::setRang(int rang)
{
    m_rang = rang;
}

void Ascan::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::red);


    //painter.drawLine(0,0,100,200);
    QByteArray wave(512,0);
    double posx[512];
    double posy[512];

    double startPosX,stopPosX,stepX;
    double startposY,stopPosY,stepY;
    int m_width = width();
    int m_height = height();

//    painter.drawLine(0,0,m_width,m_height);

//    painter.setPen(Qt::blue);

//    painter.drawLine(m_width/4,m_height/2,m_width,m_height);

    /*画随机数*/
    stepX = m_width/512.0;
    stepY = m_height/256/1.0;
    for(int i=0;i<512;i++)
    {
       posx[i]=i*stepX;
       posy[i]=qrand()%256*stepY;
//       if(i<=255)
//       {
//           posy[i]=i;
//       }else
//       {
//           posy[i] = 512-i;
//       }
    }
    for(int i=0;i<512-1;i++)
    {
        painter.drawLine(posx[i],posy[i],posx[i+1],posy[i+1]);
    }



}

