#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    QString dirName = QDir::homePath() + "/.malitounik-bgkc";
    QDir dirs(dirName);
    if (!dirs.exists()) {
        QDate date = QDate::currentDate();
        ui->spinBox->setValue(date.addYears(-2).year());
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
        ui->lineEdit->setText(carkva.toString());
        ui->lineEdit_2->setText(malitounik.toString());
        ui->spinBox->setValue(jsonYear.toString().toInt());
    }
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    QDir directory;
    QString path = QFileDialog::getExistingDirectory (this, tr("Абярыце каталог"), directory.path());
    if (path.isNull() == false )
    {
        directory.setPath(path);
        ui->lineEdit->setText(directory.path());
    }
}

void Settings::on_pushButton_2_clicked()
{
    QDir directory;
    QString path = QFileDialog::getExistingDirectory (this, tr("Абярыце каталог"), directory.path());
    if (path.isNull() == false )
    {
        directory.setPath(path);
        ui->lineEdit_2->setText(directory.path());
    }
}

void Settings::on_buttonBox_accepted()
{
    QString lineEdit = ui->lineEdit->text();
    QString lineEdit_2 = ui->lineEdit_2->text();
    QString year = ui->spinBox->text();
    QMap<QString, QString> qmap = QMap<QString, QString>();
    qmap.insert("carkva", lineEdit);
    qmap.insert("malitounik", lineEdit_2);
    qmap.insert("year", year);
    QVariantMap vmap;
    QMapIterator<QString, QString> i(qmap);
    while (i.hasNext()) {
        i.next();
        vmap.insert(i.key(), i.value());
    }
    QString dirName = QDir::homePath() + "/.malitounik-bgkc";
    QDir dirs(dirName);
    if (!dirs.exists()) {
        dirs.mkpath(dirName);
    }
    QString saveFileName = dirName + "/settings.json";
    QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
    // Создаём объект файла и открываем его на запись
    QFile jsonFile(saveFileName);
    if (jsonFile.open(QIODevice::WriteOnly))
    {
        // Записываем текущий объект Json в файл
        jsonFile.write(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Compact));
        jsonFile.close();   // Закрываем файл
    }
    emit myaccepted(&year);
}
