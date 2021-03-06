#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include <QWidget>

namespace Ui {
class GroupWidget;
}

class GroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupWidget(QWidget *parent = 0);
    ~GroupWidget();
    void setlabeltext(const QString &text);
    QString getlabeltext();
private:
    Ui::GroupWidget *ui;


};

#endif // GROUPWIDGET_H
