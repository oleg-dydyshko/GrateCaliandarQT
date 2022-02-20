#include "downloadlist.h"
#include "ui_downloadlist.h"

DownloadList::DownloadList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadList)
{
    ui->setupUi(this);

}

void DownloadList::setDownloadList(QStringList array) {
    ui->listWidget->addItems(array);
}

DownloadList::~DownloadList()
{
    delete ui;
}
