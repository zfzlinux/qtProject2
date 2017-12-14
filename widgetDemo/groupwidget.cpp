#include "groupwidget.h"
#include "ui_groupwidget.h"

GroupWidget::GroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupWidget)
{
    ui->setupUi(this);

}

GroupWidget::~GroupWidget()
{
    delete ui;
}

void GroupWidget::setlabeltext(const QString &text)
{
    ui->GroupLabel->setText(text);
}

QString GroupWidget::getlabeltext()
{
    return ui->GroupLabel->text();
}
