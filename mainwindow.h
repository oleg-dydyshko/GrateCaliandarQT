#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtNetwork/QNetworkReply>
#include "createcalindar.h"
#include "downloadsite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getSize(int *, QString *);
    void update(int *);
    void finish();
    void finishAll();
    void downloadSiteStart(int *);
    void downloadSiteUpdate(int *);
    void downloadSiteFinish();
    void on_exit_clicked();
    void on_create_clicked();
    void replyFinished(QNetworkReply *);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void dialogAccepted(QString *);
    void downloadSiteFilesList(QNetworkReply *);
    void downloadSiteFilesListAll(QNetworkReply *);

private:
    Ui::MainWindow *ui;
    QThread *pMyThread;
    QThread *pSiteThread;
    CreateCalindar *pCreateCalindar;
    downloadSite *pdownloadSite;
    int run = 0;
    int develSite = 0;
    int reliseSite = 0;
    QString carkvaPatch;
    QString malitounikPatch;
    QStringList download;
    QStringList downloadFiles;
};
#endif // MAINWINDOW_H
