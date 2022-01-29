#ifndef DOWNLOADSITE_H
#define DOWNLOADSITE_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class downloadSite: public QObject
{
    Q_OBJECT
public:
    downloadSite();
private:
    QNetworkAccessManager *networkManager;
    int position = 0;
    QString carkvaPatch;
    QString malitounikPatch;
    int downloadFilesSize;
private slots:
    void dowloadSiteArray(QNetworkReply *reply);
    void dowloadSiteFile(QNetworkReply *reply);
public slots:
    void download();
signals:
    void downloadSiteStart(int *);
    void downloadSiteUpdate(int *);
    void downloadSiteFinish();
};

#endif // DOWNLOADSITE_H
