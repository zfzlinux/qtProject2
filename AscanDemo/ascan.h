#ifndef ASCAN_H
#define ASCAN_H

#include <QWidget>

class Ascan : public QWidget
{
    Q_OBJECT
public:
    explicit Ascan(QWidget *parent = 0);
    void show();
    void setRang(int rang =10);
protected:
    void paintEvent(QPaintEvent *);

public:
    int  m_rang;

};

#endif // ASCAN_H
