#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <colorbar.h>

class Image : public QWidget
{
    Q_OBJECT
public:
    explicit Image(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
public:
    void setColor(colorbar* color){m_colorbar = color;}

public:
    QImage* p_image;
    colorbar* m_colorbar;

};

#endif // IMAGE_H
