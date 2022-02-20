#ifndef DOWNLOADLIST_H
#define DOWNLOADLIST_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class DownloadList;
}

class DownloadList : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadList(QWidget *parent = nullptr);
    ~DownloadList();
    void setDownloadList(QStringList array);

private:
    Ui::DownloadList *ui;
};

#endif // DOWNLOADLIST_H
