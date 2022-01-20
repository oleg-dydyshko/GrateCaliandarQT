#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>

int run = 0;
int develSite = 0;
int reliseSite = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    manager->get(QNetworkRequest(QUrl("https://carkva-gazeta.by/updateMalitounikBGKC.json")));
    QDate date = QDate::currentDate();
    ui->yearEdit_1->setText(QString::number(date.addYears(-2).year()));
    ui->yearEdit_2->setText(QString::number(date.addYears(1).year()));
    ui->exit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        ui->lineEditBeta->setText(devel.toString());
        ui->lineEditRelise->setText(release.toString());
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
    }
}

void MainWindow::downloadSiteStart(int *size) {
    ui->progressBar_2->setMaximum(*size);
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
