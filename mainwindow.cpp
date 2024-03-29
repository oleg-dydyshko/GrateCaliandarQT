#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "settings.h"
#include "downloadlist.h"
#include <QDir>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    manager->get(QNetworkRequest(QUrl("https://carkva-gazeta.by/updateMalitounikBGKC.json")));

    QString dirName = QDir::homePath() + "/.malitounik-bgkc";
    QDir dirs(dirName);
    QString yearIn;
    QString yearOut;
    if (!dirs.exists()) {
        Settings window;
        window.setModal(true);
        connect(&window, SIGNAL(myaccepted(QString *)), this, SLOT(dialogAccepted(QString *)));
        window.exec();
        QDate date = QDate::currentDate();
        carkvaPatch = "/home/oleg/www/carkva";
        malitounikPatch = "/home/oleg/AndroidStudioProjects/Malitounik";
        yearIn = QString::number(date.addYears(-2).year());
        yearOut = QString::number(date.addYears(1).year());
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
        QJsonValue jsonYear = result.value("year");
        carkvaPatch = carkva.toString();
        malitounikPatch = malitounik.toString();
        yearIn = jsonYear.toString();
        int preYear = yearIn.toInt();
        preYear += 3;
        yearOut = QString::number(preYear);
    }
    ui->yearEdit_1->setText(yearIn);
    ui->yearEdit_2->setText(yearOut);
    ui->exit->setVisible(false);
    QNetworkAccessManager * network = new QNetworkAccessManager(this);
    connect(network, &QNetworkAccessManager::finished, this, &MainWindow::downloadSiteFilesList);
    network->get(QNetworkRequest(QUrl("https://carkva-gazeta.by/admin/getFiles.php?yearIn=" + yearIn + "&yearOut=" + yearOut)));
    QNetworkAccessManager * networkManager = new QNetworkAccessManager(this);
    QUrl url("https://carkva-gazeta.by/admin/backup.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrlQuery params;
    params.addQueryItem("saveProgram", "1");
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(downloadSiteFilesListAll(QNetworkReply *)));
    networkManager->post(request, params.query().toUtf8());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::downloadSiteFilesListAll(QNetworkReply *reply) {
    if(!reply->error()){
        QByteArray array = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonArray result = document.array();
        for (int i = 0; i < result.size(); i++) {
            QJsonValue val = result.at(i);
            QJsonArray arr = val.toArray();
            QString getFile = arr.at(0).toString();
            QString path = arr.at(0).toString().replace("https://carkva-gazeta.by", carkvaPatch);
            int t1 = path.lastIndexOf("/");
            QString dir = carkvaPatch + path.mid(0, t1);
            QDir qdir(dir);
            if (!qdir.exists()) {
                qdir.mkpath(dir);
            }
            QFileInfo info(path);
            int mFileModifi = info.lastModified().toSecsSinceEpoch();
            int mFileModifiSite = arr[1].toInt();
            if (mFileModifi < mFileModifiSite) {
                MainWindow::downloadFiles.append(val[0].toString().replace("https://carkva-gazeta.by", ""));
            }
        }
        QString sizeDownload = QString::number(MainWindow::downloadFiles.size());
        ui->label_8->setText("Будзе запампована: " + sizeDownload.toUtf8());
    }
    reply->deleteLater();
}

void MainWindow::downloadSiteFilesList(QNetworkReply *reply) {
    if(!reply->error()) {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonArray ja = document.array();
        for (int i = 0; i < ja.size();i++) {
            QJsonValue val = ja.at(i);
            QJsonArray arr = val.toArray();
            QString filePath = arr[0].toString();
            QString path = arr[0].toString().replace("https://carkva-gazeta.by", carkvaPatch);
            if (path.contains("admin/getFilesCaliandar.php?year=")) {
                int t1 = path.lastIndexOf("=");
                QString year = path.mid(t1 + 1);
                path = carkvaPatch + "/calendar-cytanne_" + year + ".php";
            }
            QFileInfo info(path);
            int mFileModifi = info.lastModified().toSecsSinceEpoch();
            int mFileModifiSite = arr[1].toInt();
            if (mFileModifi < mFileModifiSite) {
                MainWindow::download.append(val[0].toString().replace("https://carkva-gazeta.by", ""));
            }
        }
        QString sizeDownload = QString::number(MainWindow::download.size());
        ui->label_7->setText("Будзе запампована: " + sizeDownload);
    }
    reply->deleteLater();
}

void MainWindow::replyFinished(QNetworkReply *reply) {
    if(!reply->error()){
        QByteArray array = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonObject result = document.object();
        QJsonValue release = result.value("release");
        QJsonValue devel = result.value("devel");
        develSite = devel.toString().toInt();
        reliseSite = release.toString().toInt();
        ui->lineEditBeta->setValue(devel.toString().toInt());
        ui->lineEditRelise->setValue(release.toString().toInt());
    }
    reply->deleteLater();
}

void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}

void MainWindow::getSize(int *size, QString *label)
{
    QString utflabel = *label;
    ui->progressBar->setMaximum(*size);
    ui->progressBar->setValue(0);
    ui->label_4->setText(utflabel.toUtf8());
}

void MainWindow::finish() {
    run++;
    MainWindow::finishAll();
}

void MainWindow::finishAll() {
    if (run == 4) {
        ui->label_4->setText("Гатова!");
        run = 0;
        ui->create->setVisible(true);
        ui->exit->setVisible(true);
        ui->label_7->setText("Будзе запампована: 0");
        ui->label_8->setText("Будзе запампована: 3");
    }
}

void MainWindow::downloadSiteStart(int *sizeD) {
    ui->progressBar_2->setMaximum(*sizeD);
    ui->progressBar_2->setValue(0);
}

void MainWindow::downloadSiteUpdate(int *update) {
    ui->progressBar_2->setValue(*update);
}

void MainWindow::downloadSiteFinish() {
    run++;
    MainWindow::finishAll();
}

void MainWindow::update(int *update) {
    ui->progressBar->setValue(*update);
}

void MainWindow::on_pushButton_clicked()
{
    Settings window;
    window.setModal(true);
    connect(&window, SIGNAL(myaccepted(QString *)), this, SLOT(dialogAccepted(QString *)));
    window.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    DownloadList window;
    window.setModal(true);
    window.setDownloadList(MainWindow::download);
    window.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    DownloadList window;
    window.setModal(true);
    window.setDownloadList(MainWindow::downloadFiles);
    window.exec();
}

void MainWindow::dialogAccepted(QString *year) {
    QString yearIn = *year;
    int preYear = yearIn.toInt();
    preYear += 3;
    QString yearOut = QString::number(preYear);
    ui->yearEdit_1->setText(yearIn);
    ui->yearEdit_2->setText(yearOut);
}

void MainWindow::on_create_clicked()
{
    if(ui->create->isVisible()) {
        ui->create->setVisible(false);
        ui->exit->setVisible(false);
        bool checkDevel = false;
        bool checkRelise =  false;
        if (develSite != 0 && develSite < ui->lineEditBeta->text().toInt())
            checkDevel = true;
        if (reliseSite != 0 && reliseSite < ui->lineEditRelise->text().toInt())
            checkRelise = true;
        pMyThread = new QThread;
        pCreateCalindar = new CreateCalindar(ui->yearEdit_1->text().toInt(), ui->yearEdit_2->text().toInt(), ui->checkBox_1->isChecked(), checkDevel, checkRelise, ui->lineEditBeta->text(), ui->lineEditRelise->text());
        pCreateCalindar->moveToThread(pMyThread);
        connect(pCreateCalindar, SIGNAL(getSize(int *, QString *)), this, SLOT(getSize(int *, QString *)));
        connect(pCreateCalindar, SIGNAL(update(int *)), this, SLOT(update(int *)));
        connect(pCreateCalindar, SIGNAL(finished()), this, SLOT(finish()));
        connect(pMyThread, SIGNAL(started()), pCreateCalindar, SLOT(generate()));
        pMyThread->start();
        if (ui->checkBox_2->isChecked()) {
            pSiteThread = new QThread;
            pdownloadSite = new downloadSite();
            pdownloadSite->moveToThread(pSiteThread);
            connect(pdownloadSite, SIGNAL(downloadSiteStart(int *)), this, SLOT(downloadSiteStart(int *)));
            connect(pdownloadSite, SIGNAL(downloadSiteUpdate(int *)), this, SLOT(downloadSiteUpdate(int *)));
            connect(pdownloadSite, SIGNAL(downloadSiteFinish()), this, SLOT(downloadSiteFinish()));
            connect(pSiteThread, SIGNAL(started()), pdownloadSite, SLOT(download()));
            pSiteThread->start();
        } else {
            run++;
        }
    }
}
