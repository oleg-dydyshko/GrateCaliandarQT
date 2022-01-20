#include "downloadsite.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <QtNetwork/QNetworkReply>
#include <QJsonArray>
#include <QFile>
#include <QDir>

downloadSite::downloadSite()
{
}

QJsonArray downloadFiles;

void downloadSite::download() {
    networkManager = new QNetworkAccessManager(this);
    QUrl url("https://carkva-gazeta.by/admin/backup.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrlQuery params;
    params.addQueryItem("saveProgram", "1");
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(dowloadSiteArray(QNetworkReply *)));
    networkManager->post(request, params.query().toUtf8());
}

void downloadSite::dowloadSiteArray(QNetworkReply *reply) {
    if(!reply->error()){
        while(downloadFiles.count()) {
             downloadFiles.pop_back();
        }
        QByteArray array = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonArray result = document.array();
        disconnect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(dowloadSiteArray(QNetworkReply *)));
        connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(dowloadSiteFile(QNetworkReply *)));
        for (int i = 0; i < result.size(); i++) {
            QString getFile = result.at(i).toString();
            QString path = getFile.replace("https://carkva-gazeta.by/", "/home/oleg/www/carkva/");
            QFile file(path);
            if (!file.exists() || path.contains(".sql") || path.contains(".xml")) {
                downloadFiles.append(result.at(i).toString());
            }
        }
        int size = downloadFiles.size() - 1;
        emit downloadSiteStart(&size);
        networkManager->get(QNetworkRequest(QUrl(downloadFiles.at(downloadSite::position).toString())));
    }
    reply->deleteLater();
}

void downloadSite::dowloadSiteFile(QNetworkReply *reply) {
    if(!reply->error()){
        QByteArray array = reply->readAll();
        QString getFile = downloadFiles.at(downloadSite::position).toString();
        QString path = getFile.replace("https://carkva-gazeta.by/", "/home/oleg/www/carkva/");
        int t1 = path.lastIndexOf("/");
        QString dirPath = path.mid(0, t1);
        QDir dirs(dirPath);
        if (!dirs.exists()) {
            dirs.mkpath(dirPath);
        }
        QFile file(path);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(array);
        }
        file.close();
        downloadSite::position++;
        if (downloadSite::position < downloadFiles.size()) {
            int update = downloadSite::position;
            emit downloadSiteUpdate(&update);
            getFile = downloadFiles.at(downloadSite::position).toString();
            networkManager->get(QNetworkRequest(QUrl(getFile)));
        } else {
            emit downloadSiteFinish();
        }
    }
    reply->deleteLater();
}
