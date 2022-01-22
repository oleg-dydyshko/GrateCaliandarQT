#ifndef CREATECALINDAR_H
#define CREATECALINDAR_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonArray>

class CreateCalindar: public QObject
{
    Q_OBJECT
public:
    int const MONDAY = 1;
    int const TUESDAY = 2;
    int const FRIDAY = 5;
    int const SATURDAY = 6;
    int const SUNDAY = 7;
    int const JANUARY = 1;
    int const FEBRUARY = 2;
    int const MARCH = 3;
    int const APRIL = 4;
    int const MAY = 5;
    int const JUNE = 6;
    int const JULY = 7;
    int const AUGUST = 8;
    int const SEPTEMBER = 9;
    int const OCTOBER= 10;
    int const NOVEMBER = 11;
    int const DECEMBER = 12;
    CreateCalindar(int inyear, int outyear, bool copySiteProgram, bool beta, bool relise, QString devel, QString release);
private:
    int inyear;
    int outyear;
    bool copySiteProgram;
    bool beta;
    bool relise;
    QString devel;
    QString release;
    QJsonArray ja;
    int position = 0;
    QString svitya[367][3];
    QString sviatyia_new[366][4];
    int YearG = 2020;
    QString carkvaPatch;
    QString malitounikPatch;
    QNetworkAccessManager *networkManager;
    void setViersionApp(bool relise);
    void getSviatyYear(int Year);
    QString getSviaty(int year, int DayYear, int f);
    int den(int Year, int DayYaer);
    QString translateToBelarus(QString paralel);
    QString MaranAta(int pageNumber, int year);
    QString profesional(int DayYear, int year);
    QString gosudarstvoRab(int DayYear, int year);
    QString gosudarstvo(int DayYear, int year);
    QString pascha_pravas(int DayYear, int year);
    QString sviatyPKC(int DayYear, int year);
    void gratePamiatekaVernikau(int year);
    void generateCaliandar();
public slots:
    void sviatyia(int year);
    void generate();
private slots:
    void onResult(QNetworkReply *reply);
    void onDownload(QNetworkReply *reply);
signals:
    void finished();
    void update(int *);
    void getSize(int *, QString *);
};

#endif // CREATECALINDAR_H
