#ifndef COLORBAR_H
#define COLORBAR_H

#include <QWidget>
#include <QImage>
class colorbar : public QWidget
{
    Q_OBJECT
public:
    explicit colorbar(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
signals:

public slots:
private:
    void loadColorFile(QString path);
public:
    QVector<QColor> getColor();
    ushort getPixColor(int pixel);

private:

    QVector<QColor> m_colorPreview;
    QImage* m_Image;
    ushort m_pixColor[256];
};

#endif // COLORBAR_H
