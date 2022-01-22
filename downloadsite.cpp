#include "downloadsite.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkReply>
#include <QJsonArray>
#include <QFile>
#include <QDir>

downloadSite::downloadSite()
{
}

QJsonArray downloadFiles;

void downloadSite::download() {
    QString dirName = QDir::homePath() + "/.malitounik-bgkc";
    QDir dirs(dirName);
    if (!dirs.exists()) {
        carkvaPatch = "/home/oleg/www/carkva";
        malitounikPatch = "/home/oleg/AndroidStudioProjects/Malitounik";
    } else {
        QByteArray array;
        QString fileName = dirName + "/settings.json";
        QFileInfo fileInfo(fileName);
        QDir::setCurrent(fileInfo.path());
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly))
        {
            array = file.readAll();
            file.close();
        }
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonObject result = document.object();
        QJsonValue carkva = result.value("carkva");
        QJsonValue malitounik = result.value("malitounik");
        carkvaPatch = carkva.toString();
        malitounikPatch = malitounik.toString();
    }
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
            QString path = getFile.replace("https://carkva-gazeta.by", carkvaPatch);
            int t1 = path.lastIndexOf("/");
            QString dir = carkvaPatch + getFile.mid(0, t1);
            QDir qdir(dir);
            if (!qdir.exists()) {
                qdir.mkpath(dir);
            }
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
        QString path = getFile.replace("https://carkva-gazeta.by", carkvaPatch);
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
