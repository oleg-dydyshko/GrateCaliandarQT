#include "createcalindar.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QUrlQuery>
#include <QFileInfo>
#include <QDir>

CreateCalindar::CreateCalindar(int inyear, int outyear, bool copySiteProgram, bool beta, bool relise, QString devel, QString release)
{
    CreateCalindar::inyear = inyear;
    CreateCalindar::outyear = outyear;
    CreateCalindar::copySiteProgram = copySiteProgram;
    CreateCalindar::beta = beta;
    CreateCalindar::relise = relise;
    CreateCalindar::devel = devel;
    CreateCalindar::release = release;
}

void CreateCalindar::generate()
{
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
    networkManager = new QNetworkAccessManager();
    if (CreateCalindar::beta) {
        CreateCalindar::setViersionApp(false);
    } else {
        emit finished();
    }
    if (CreateCalindar::relise) {
        CreateCalindar::setViersionApp(true);
    } else {
        emit finished();
    }
    if (CreateCalindar::copySiteProgram) {
        connect(networkManager, &QNetworkAccessManager::finished, this, &CreateCalindar::onResult);
        networkManager->get(QNetworkRequest(QUrl("https://android.carkva-gazeta.by/admin/getFiles.php?yearIn=" + QString::number(CreateCalindar::inyear) + "&yearOut=" + QString::number(CreateCalindar::outyear))));
    } else {
        CreateCalindar::generateCaliandar();
    }
}

void CreateCalindar::generateCaliandar()
{
    int dayyear = 0;
    for (int i = CreateCalindar::inyear; i <= CreateCalindar::outyear; i++) {
        if (QDate::isLeapYear(i)) dayyear = 366 + dayyear;
        else dayyear = 365 + dayyear;
    }
    QDate c2(CreateCalindar::inyear, CreateCalindar::JANUARY, 1);
    QJsonArray arrayListsNelel;
    int niadzeliaAdapter = 0;
    int munAdapter = 0;
    int mun = c2.month();
    labal = "Ствараем каляндар:";
    emit getSize(&dayyear, &labal);
    for (int e = 1; e <= dayyear; e++) {
        QJsonArray arrayList;
        QString postBild = "0";
        QString sviaty = "";
        QString sviatyDay = "0";
        QString pameplyia = "0";
        QString sviatyiaName = "no_sviatyia";
        QString cytanneSV = "";
        int year = c2.year();
        int Nedel = c2.dayOfWeek();
        int DayYear = c2.dayOfYear() - 1;

        CreateCalindar::sviatyia(year);

        int a = year % 19;
        int b = year % 4;
        int cx = year % 7;
        int k = (year / 100);
        int p = (13 + 8 * k) / 25;
        int q = (k / 4);
        int m = (15 - p + k - q) % 30;
        int n = (4 + k - q) % 7;
        int d = (19 * a + m) % 30;
        int ex = (2 * b + 4 * cx + 6 * d + n) % 7;
        int month_p;
        int data_p;
        if (d + ex <= 9) {
            data_p = d + ex + 22;
            month_p = CreateCalindar::MARCH;
        } else {
            data_p = d + ex - 9;
            if (d == 29 && ex == 6) data_p = 19;
            if (d == 28 && ex == 6) data_p = 18;
            month_p = CreateCalindar::APRIL;
        }
        QDate pasha(year, month_p, data_p);
        int mytnik = pasha.addDays(-70).dayOfYear();//Мытніка і фарысея
        int syrny = pasha.addDays(-70 + 14).dayOfYear();//Мясопустная
        int svetly = pasha.addDays(-70 + 14 + 56).dayOfYear();//Сьветлы
        int traechki = pasha.addDays(-70 + 14 + 56 + 49).dayOfYear();//Траецкі
        pasha.setDate(year, month_p, data_p);
        int Pasxa = pasha.dayOfYear();
        int VialikiPost = pasha.addDays(-49).dayOfYear();
        pasha.setDate(year, CreateCalindar::JUNE, 29);
        int Pavel = pasha.dayOfYear();
        pasha.setDate(year, CreateCalindar::AUGUST, 1);
        int uspenieN = pasha.dayOfYear();
        pasha.setDate(year, CreateCalindar::AUGUST, 15);
        int uspenieK = pasha.dayOfYear();
        pasha.setDate(year, CreateCalindar::NOVEMBER, 15);
        int kaladyN = pasha.dayOfYear();
        pasha.setDate(year, CreateCalindar::DECEMBER, 25);
        int kaladyK = pasha.dayOfYear();
        pasha.setDate(year, CreateCalindar::JANUARY, 5);
        int bogaziaulenne = pasha.dayOfYear();
        int bogaziaulenneNed = pasha.dayOfWeek();
        pasha.setDate(year, CreateCalindar::AUGUST, 29);
        int AdsiachenneGalavy = pasha.dayOfYear();
        int AdsiachenneGalavyNed = pasha.dayOfWeek();
        pasha.setDate(year, CreateCalindar::SEPTEMBER, 14);
        int KrygaUzvyshenne = pasha.dayOfYear();
        int KrygaUzvyshenneNed = pasha.dayOfWeek();
        pasha.setDate(year, CreateCalindar::DECEMBER, 24);
        int Kaliady = pasha.dayOfYear();
        int KaliadyNed = pasha.dayOfWeek();

        QDate sustrecha(year, CreateCalindar::FEBRUARY, 2);
        int i2 = sustrecha.dayOfYear();
        int addanne_sviata_Sustrechy = i2 + 6;
        pasha.setDate(year, month_p, data_p);
        int period1 = pasha.addDays(-64).dayOfYear();//Блудны сын(суббота)
        if (i2 >= period1 && i2 <= period1 + 2) {
            addanne_sviata_Sustrechy = period1 + 4;
        }
        if (i2 >= period1 + 3 && i2 <= period1 + 6) {
            addanne_sviata_Sustrechy = syrny + 1;
        }
        if (i2 >= syrny && i2 <= syrny + 1) {
            addanne_sviata_Sustrechy = syrny + 4;
        }
        if (i2 >= syrny + 2 && i2 <= syrny + 3) {
            addanne_sviata_Sustrechy = syrny + 5;
        }
        if (i2 >= syrny + 4 && i2 <= syrny + 6) {
            addanne_sviata_Sustrechy = syrny + 6;
        }
        if (CreateCalindar::getSviaty(year, DayYear, 2) != "" && CreateCalindar::getSviaty(year, DayYear, 2) == "5" && Nedel != CreateCalindar::SATURDAY) {
            postBild = "1";
        }
        bool post = true;
        if (!(Nedel == CreateCalindar::SUNDAY || Nedel == CreateCalindar::SATURDAY)) {
            if (DayYear <= 3 || DayYear >= 359 || (mytnik <= DayYear && DayYear <= mytnik + 4) || (syrny <= DayYear && DayYear <= syrny + 4) || (svetly <= DayYear && DayYear <= svetly + 4) || (traechki <= DayYear && DayYear <= traechki + 4)) {
            postBild = "1";
            post = false;
            }
        }
        if (!(Nedel == CreateCalindar::SUNDAY || Nedel == CreateCalindar::SATURDAY)) {
            if ((VialikiPost <= DayYear && DayYear <= Pasxa - 2) || (Pasxa + 56 <= DayYear && DayYear <= Pavel - 2) || (uspenieN - 1 <= DayYear && DayYear <= uspenieK - 2) || (kaladyN - 1 <= DayYear && DayYear <= kaladyK - 2)) {
                postBild = "2";
            }
        }
        if (Nedel == CreateCalindar::SUNDAY) {
            postBild = "0";
        }
        // чтения
        QString sviatyaChtenia = "";
        QString cytanneDop = "";

        QString sv_per = ""; //vailikia_gadziny = "";
        QString sv_per_ch = "";
        QString predsviaty = "";
            sviaty = CreateCalindar::getSviaty(year, DayYear, 0);
            if (CreateCalindar::getSviaty(year, DayYear, 2) == "4") {
                sviaty = "";
            }

        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-48).dayOfYear() - 1) {
            predsviaty = "<em>Пачатак Вялікага посту</em>";
        }

        //pasha.set(year, month_p, data_p);
        if (DayYear == pasha.addDays(57).dayOfYear() - 1) {
            predsviaty = "<em>Пачатак Пятровага посту</em>";
        }
        pasha.setDate(year, CreateCalindar::AUGUST, 1);
        if (DayYear == pasha.dayOfYear() - 1) {
            // Працэсія Пачэснага Крыжа
            cytanneDop = "Крыжу: 1 Кар 1.18-24; Ян 19.6-11, 13-20, 25-28, 30-35";
        }
        int add = 0;
        if (pasha.dayOfWeek() == CreateCalindar::SUNDAY)
            add = 1;
        if (pasha.dayOfWeek() == CreateCalindar::SATURDAY)
            add = 2;
        if (DayYear == pasha.addDays(add).dayOfYear() - 1) {
            predsviaty = "<em>Пачатак Усьпенскага посту</em>";
        }
        pasha.setDate(year, CreateCalindar::NOVEMBER, 15);
        add = 0;
        if (pasha.dayOfWeek() == CreateCalindar::SUNDAY)
            add = 1;
        if (pasha.dayOfWeek() == CreateCalindar::SATURDAY)
            add = 2;
        if (DayYear == pasha.addDays(add).dayOfYear() - 1) {
            predsviaty = "<em>Пачатак Каляднага посту</em>";
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-6).dayOfYear() - 1) {
            predsviaty = "<em>Вялікі панядзелак</em>";
        }
        if (DayYear == pasha.addDays(-5).dayOfYear() - 1) {
            predsviaty = "<em>Вялікі аўторак</em>";
        }
        if (DayYear == pasha.addDays(-4).dayOfYear() - 1) {
            predsviaty = "<em>Вялікая серада</em>";
        }
        if (DayYear == pasha.addDays(-3).dayOfYear() - 1) {
            predsviaty = "<em>Вялікі чацьвер.<br>Успамін Тайнай Вячэры</em>";
        }
        if (DayYear == pasha.addDays(-2).dayOfYear() - 1) {
            predsviaty = "<em>Вялікая пятніца.<br>Успамін мукаў і сьмерці Хрыстовай</em>";
        }
        if (DayYear == pasha.addDays(-1).dayOfYear() - 1) {
            predsviaty = "<em>Вялікая субота</em>";
        }
        QDate rog;
        QList<int> rogdestvo = {11, 12, 13, 14, 15, 16, 17};
        QList<int> rogdestvo2 = {18, 19, 20, 21, 22, 23, 24};
        for (int aMay1 : rogdestvo) {
            rog.setDate(year, CreateCalindar::DECEMBER, aMay1);
            int wik = rog.dayOfWeek();
            if (wik == CreateCalindar::SUNDAY) {
                if (rog.dayOfYear() - 1 == DayYear) {
                    sviaty.append(". Праайцоў");
                }
            }
        }
        for (int aMay1 : rogdestvo2) {
            rog.setDate(year, CreateCalindar::DECEMBER, aMay1);
            int wik = rog.dayOfWeek();
            if (wik == CreateCalindar::SUNDAY) {
                if (rog.dayOfYear() - 1 == DayYear) {
                    sviaty.append(". Сьвятых айцоў");
                }
            }
        }
        if (year == CreateCalindar::outyear) {
            QDate gc(year, month_p, data_p);
            if (DayYear < gc.addDays(-71).dayOfYear() || DayYear > 257) {
                sviatyaChtenia = "Прабачце, няма дадзеных";
                sviaty = "";
            } else {
                sviatyaChtenia = CreateCalindar::getSviaty(year, DayYear, 1);
            }
        } else {
            sviatyaChtenia = CreateCalindar::getSviaty(year, DayYear, 1);
        }

        if (CreateCalindar::getSviaty(year, DayYear, 2) == "1")
            sviatyDay = "1";

        pasha.setDate(year, CreateCalindar::JANUARY, 2);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Богазьяўленьня</em>";
        }
        pasha.setDate(year, CreateCalindar::JANUARY, 14);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Адданьне сьвята Богазьяўленьня</em>";
        }
        pasha.setDate(year, CreateCalindar::FEBRUARY, 1);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Cустрэчы Госпада нашага Ісуса Хрыста</em>";
        }
        if (DayYear == addanne_sviata_Sustrechy) {
            predsviaty = "<em>Адданьне сьвята Сустрэчы Госпада</em>";
            sv_per_ch = "Багар.: Габ 9.1-7; Лк 10.38-42, 11.27-28";
        }
        pasha.setDate(year, CreateCalindar::MARCH, 24);
        if (DayYear == pasha.dayOfYear() - 1) {
            if (predsviaty != "")
                predsviaty = predsviaty + "<br><em>Перадсьвяцьце Дабравешчаньня</em>";
            else predsviaty = "<em>Перадсьвяцьце Дабравешчаньня</em>";
        }
        pasha.setDate(year, CreateCalindar::MARCH, 26);
        if (DayYear == pasha.dayOfYear() - 1) {
            if (predsviaty != "")
                predsviaty = predsviaty + "<br><em>Адданьне сьвята Дабравешчаньня</em>";
            else predsviaty = "<em>Адданьне сьвята Дабравешчаньня</em>";
        }
        pasha.setDate(year, CreateCalindar::JULY, 31);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце працэсіі Пачэснага Крыжа</em>";
        }
        pasha.setDate(year, CreateCalindar::AUGUST, 5);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Перамяненьня</em>";
        }
        pasha.setDate(year, CreateCalindar::AUGUST, 13);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Адданьне сьвята Перамяненьня</em>";
        }
        pasha.setDate(year, CreateCalindar::AUGUST, 14);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Ўсьпеньня</em>";
        }
        pasha.setDate(year, CreateCalindar::AUGUST, 23);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Адданьне сьвята Ўсьпеньня</em>";
        }
        pasha.setDate(year, CreateCalindar::SEPTEMBER, 7);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Нараджэньня Найсьвяцейшай Багародзіцы</em>";
        }
        pasha.setDate(year, CreateCalindar::SEPTEMBER, 12);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Адданьне сьвята Нараджэньня Найсьвяцейшай Багародзіцы</em>";
        }
        pasha.setDate(year, CreateCalindar::SEPTEMBER, 13);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Крыжаўзвышэньня</em>";
        }
        pasha.setDate(year, CreateCalindar::SEPTEMBER, 21);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Адданьне сьвята Крыжаўзвышэньня</em>";
        }
        pasha.setDate(year, CreateCalindar::NOVEMBER, 20);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Ўваходу ў Храм Найсьвяцейшай Багародзіцы</em>";
        }
        pasha.setDate(year, CreateCalindar::DECEMBER, 8);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Зачацьця праведнай Ганны</em>";
        }
        pasha.setDate(year, CreateCalindar::NOVEMBER, 25);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Адданьне сьвята Ўваходу ў Храм Багародзіцы</em>";
        }
        pasha.setDate(year, CreateCalindar::DECEMBER, 20);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Перадсьвяцьце Раства Хрыстова</em>";
        }
        pasha.setDate(year, CreateCalindar::DECEMBER, 31);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "<em>Адданьне сьвята Раства Хрыстовага</em>";
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(37).dayOfYear()) {
            predsviaty = "<em>Адданьне сьвята Вялікадня</em>";
        }
        if (DayYear == pasha.addDays(37 + 9).dayOfYear()) {
            predsviaty = "<em>Адданьне сьвята Ўзьнясеньня</em>";
        }
        if (DayYear == pasha.addDays(37 + 9 + 8).dayOfYear()) {
            predsviaty = "<em>Адданьне сьвята Тройцы</em>";
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(23).dayOfYear()) {
            predsviaty = "<strong>Палова сьвята Пяцідзясятніцы</strong>";
        }
        for (int i = 7; i <= 13; i++) {
            pasha.setDate(year, CreateCalindar::SEPTEMBER, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek) {
                if (i == 12)
                    predsviaty = predsviaty + "<br><strong>Субота перад Крыжаўзвышэньнем</strong>";
                else
                    predsviaty = "<strong>Субота перад Крыжаўзвышэньнем</strong>";
                sv_per_ch = "Суб.: 1 Кар 2.6-9; Мц 10.37-11.1";
            }
        }
        for (int i = 15; i <= 21; i++) {
            pasha.setDate(year, CreateCalindar::SEPTEMBER, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek) {
                predsviaty = "<strong>Субота пасьля Крыжаўзвышэньня</strong>";
                sv_per_ch = "Суб.: 1 Кар 1.26-29; Ян 8.21-30";
            }
        }
        for (int i = 7; i <= 13; i++) {
            pasha.setDate(year, CreateCalindar::SEPTEMBER, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SUNDAY == dayofweek) {
                predsviaty = "<strong>Нядзеля перад Крыжаўзвышэньнем</strong>";
                //sv_per_ch = "Нядз.: Гал 6.11-18; Ян 3.13-17";
            }
        }
        for (int i = 15; i <= 21; i++) {
            pasha.setDate(year, CreateCalindar::SEPTEMBER, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SUNDAY == dayofweek) {
                predsviaty = "<strong>Нядзеля пасьля Крыжаўзвышэньня</strong>";
                //sv_per_ch = "Нядз.: Гал 2.16-20; Мк 8.34-9.1";
            }
        }
        for (int i = 7; i <= 13; i++) {
            pasha.setDate(year, CreateCalindar::JANUARY, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SUNDAY == dayofweek) {
                //predsviaty = "<strong>Нядзеля пасьля Богазьяўленьня</strong>";
                //sv_per_ch = "Нядз.: Эф 4.7-13; Мц 4.12-17";
            }
        }

        for (int i = 18; i <= 24; i++) {
            pasha.setDate(year, CreateCalindar::DECEMBER, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek) {
                predsviaty = "<strong>Субота перад Раством Хрыстовым</strong>";
                sv_per_ch = "Суб.: Гал 3.8-12; Лк 13.18-29";
            }
        }
        for (int i = 26; i <= 31; i++) {
            pasha.setDate(year, CreateCalindar::DECEMBER, i);
            int dayofweek = pasha.dayOfWeek();
            if ((DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek)) {
                predsviaty = "<strong>Субота пасьля Раства Хрыстовага</strong>";
                sv_per_ch = "Суб.: 1 Цім 6.11-16; Мц 12.15-21";
            }
        }
        pasha.setDate(year, CreateCalindar::JANUARY, 1);
        if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == pasha.dayOfWeek()) {
            predsviaty = "<strong>Субота пасьля Раства Хрыстовага</strong>";
            sv_per_ch = "Суб.: 1 Цім 6.11-16; Мц 12.15-21";
        }
        for (int i = 19; i <= 25; i++) {
            pasha.setDate(year, CreateCalindar::OCTOBER, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek) {
                predsviaty = "<strong>Зьмітраўская бацькоўская субота</strong>";
                sv_per_ch = "Пам.: 1 Сал 4.13-17; Ян 5.24-30";
                pameplyia = "1";
            }
        }
        for (int i = 1; i <= 5; i++) {
            pasha.setDate(year, CreateCalindar::JANUARY, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek) {
                predsviaty = "<strong>Субота перад Богазьяўленьнем</strong>";
                sv_per_ch = "Суб.: 1 Цім 3.14-4.5; Мц 3.1-11";
            }
        }
        for (int i = 30; i <= 31; i++) {
            pasha.setDate(year, CreateCalindar::DECEMBER, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek) {
                if (CreateCalindar::SATURDAY == dayofweek) {
                    predsviaty = "<strong>Субота пасьля Раства Хрыстовага</strong><br><strong>Субота перад Богазьяўленьнем</strong>";
                    sv_per_ch = "Суб.: 1 Цім 6.11-16; Мц 12.15-21;\n1 Цім 3.14-4.5; Мц 3.1-11";
                } else {
                    predsviaty = "<strong>Субота перад Богазьяўленьнем</strong>";
                    sv_per_ch = "Суб.: 1 Цім 3.14-4.5; Мц 3.1-11";
                }
            }
        }
        for (int i = 7; i <= 13; i++) {
            pasha.setDate(year, CreateCalindar::JANUARY, i);
            int dayofweek = pasha.dayOfWeek();
            if (DayYear == pasha.dayOfYear() - 1 && CreateCalindar::SATURDAY == dayofweek) {
                predsviaty = "<strong>Субота пасьля Богазьяўленьня</strong>";
                sv_per_ch = "Суб.: Эф 6.10-17; Мц 4.1-11";
            }
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-51).dayOfYear()) {
            predsviaty = "<em>Усіх сьвятых айцоў\nманахаў і посьнікаў</em>";
            sv_per_ch = "Айцам.: Гал 5.22-6.2; Мц 11.27-30";
        }
        //pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(8).dayOfYear()) {
            predsviaty = "<strong>Радаўніца</strong>";
            sv_per_ch = "Пам.: 1 Кар 15.47-57; Ян 5.24-30";
            pameplyia = "1";
        }
        pasha.setDate(year, CreateCalindar::DECEMBER, 24);
        if (DayYear == pasha.dayOfYear() - 1) {
            predsviaty = "СЬВЯТЫ ВЕЧАР ПЕРАД РАСТВОМ ХРЫСТОВЫМ";
        }
        pasha.setDate(year, month_p, data_p);
        QDate typonDate(year, CreateCalindar::FEBRUARY, 17);
        if (DayYear == pasha.addDays(-44).dayOfYear() && DayYear != typonDate.dayOfYear() - 1) {
            QDate vtt(year, CreateCalindar::FEBRUARY, 17);
            if (vtt.dayOfYear() - 1 != pasha.dayOfYear()) {
            sv_per.append("Вялікамуч. Тодара Тырона");
            sv_per_ch += "Вялікамуч.: 2 Цім 2.1-10; Ян 15.17-16.2";
            }
        }
        //pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-22).dayOfYear()) {
            QString br = "";
            if (sv_per != "")
                br = "<br>";
            sv_per.append(br).append("Вялебнага Яна Лесьвічніка");
            sv_per_ch = "Вялеб.: Эф 5.9-19; Мц 4.25-5.12";
        }
        //pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-15).dayOfYear()) {
            QString br = "";
            if (sv_per != "")
                br = "<br>";
            sv_per.append(br).append("Вялебнай Марыі Ягіпецкай");
            sv_per_ch = "Вялеб.: Гал 3.23-29; Лк 7.36-50";
        }
        pasha.setDate(year, CreateCalindar::FEBRUARY, 28);
        add = 0;
        if (pasha.isLeapYear(year))
            add = 1;
        if (DayYear == pasha.addDays(add).dayOfYear() - 1) {
            QString br = "";
            if (sv_per != "")
                br = "<br>";
            sv_per.append(br).append("Вялеб. Касьяна Рымляніна");
        }
        pasha.setDate(year, CreateCalindar::DECEMBER, 25);
        int pastvoW = pasha.dayOfWeek();
        for (int i = 26; i <= 31; i++) {
            QDate pastvo(year, CreateCalindar::DECEMBER, i);
            int iazepW = pastvo.dayOfWeek();
            if (pastvoW != CreateCalindar::SUNDAY) {
                if (DayYear == pastvo.dayOfYear() - 1 && CreateCalindar::SUNDAY == iazepW) {
                    QString br = "";
                    if (sv_per != "")
                        br = "<br>";
                    sv_per.append(br).append("Праведнага Язэпа Абручніка, Давіда цара і Якуба, брата Гасподняга");
                }
            } else {
                if (DayYear == pastvo.dayOfYear() - 1 && CreateCalindar::MONDAY == iazepW) {
                    QString br = "";
                    if (sv_per != "")
                        br = "<br>";
                    sv_per.append(br).append("Праведнага Язэпа Абручніка, Давіда цара і Якуба, брата Гасподняга");
                }
            }
        }
        for (int i = 13; i <= 19; i++) {
            pasha.setDate(year, CreateCalindar::JULY, i);
            int wik = pasha.dayOfWeek();
            if (wik == CreateCalindar::SUNDAY && pasha.dayOfYear() - 1 == DayYear) {
                sviaty.append(", Айцоў першых 6-ці Ўсяленскіх сабораў");
                sv_per_ch = "Айцам.: Гбр 13.7-16; Ян 17.1-13";
            }
        }
        for (int i = 11; i <= 17; i++) {
            pasha.setDate(year, CreateCalindar::OCTOBER, i);
            int wik = pasha.dayOfWeek();
            if (wik == CreateCalindar::SUNDAY && pasha.dayOfYear() - 1 == DayYear) {
                sviaty.append(", Айцоў VII Сусьветнага Сабору");
                cytanneSV = "Айцам.: Габ 13.7-16; Ян 17.1-13";
            }
        }
        pasha.setDate(year, CreateCalindar::SEPTEMBER, 1);
        if (DayYear == pasha.dayOfYear() - 1) {
            QString br = "";
            if (sv_per != "")
                br = "<br>";
            sv_per.insert(0, "<font color=#d00505>Пачатак царкоўнага году</font>" + br);
            sv_per_ch = "Новаму году.: 2 Цім 2.1-7; Лк 4.16-22";
        }

        // Памінаньне памёрлых
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-58).dayOfYear()) {
            predsviaty = "<em>Мясапусная задушная субота</em>";
            pameplyia = "1";
            sv_per_ch = "Пам.: 1 Сал 4.13-17; Ян 5.24-30";
        }
        //pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-37).dayOfYear()) {
            predsviaty = "<em>Бацькоўская (задушная) субота</em>";
            pameplyia = "1";
            sv_per_ch = "Пам.: 1 Сал 4.13-17; Ян 5.24-30";
        }
        //pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-30).dayOfYear()) {
            predsviaty = "<em>Бацькоўская (задушная) субота</em>";
            pameplyia = "1";
            sv_per_ch = "Пам.: 1 Сал 4.13-17; Ян 5.24-30";
        }
        //pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-23).dayOfYear()) {
            predsviaty = "<em>Бацькоўская (задушная) субота</em>";
            pameplyia = "1";
            sv_per_ch = "Пам.: 1 Кар 15.47-57; Ян 5.24-30";
        }
        //pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(47).dayOfYear()) {
            predsviaty = "<em>Траецкая бацькоўская субота</em>";
            sv_per_ch = "Пам.: 1 Сал 4.13-17; Ян 5.24-30";
            pameplyia = "1";
        }
        pasha.setDate(year, CreateCalindar::NOVEMBER, 2);
        if (DayYear == pasha.addDays(-1).dayOfYear()) {
            predsviaty = "<strong>Дзяды</strong>";
            sv_per_ch = "Пам.: 1 Кар 15.39-57; Ян 5.24-30";
            pameplyia = "1";
        }
        QString vilikiiaGadziny = "Вялікія гадзіны: Габ 1.1-12; Мц 1.18-25; Гал 3.23-29; Лк 2.1-20; Габ 1.10-2.3; Мц 2.1-12; Габ 2.11-18; Мц 2.13-23";
        pasha.setDate(year, CreateCalindar::DECEMBER, 24);
        add = 0;
        if (pasha.dayOfWeek() == CreateCalindar::SUNDAY)
            add = -2;
        if (pasha.dayOfWeek() == CreateCalindar::SATURDAY)
            add = -1;
        if (DayYear == pasha.addDays(add).dayOfYear() - 1) {
            sv_per_ch = vilikiiaGadziny;
        }
        pasha.setDate(year, CreateCalindar::JANUARY, 5);
        add = 0;
        if (pasha.dayOfWeek() == CreateCalindar::SUNDAY)
            add = -2;
        if (pasha.dayOfWeek() == CreateCalindar::SATURDAY)
            add = -1;
        if (DayYear == pasha.addDays(add).dayOfYear() - 1) {
            sv_per_ch = vilikiiaGadziny;
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-2).dayOfYear() - 1) {
            predsviaty = "<em>Вялікая пятніца.<br>Успамін мукаў і сьмерці Хрыстовай</em>";
            sv_per_ch = vilikiiaGadziny;
        }
        pasha.setDate(year, CreateCalindar::DECEMBER, 24);
        if (DayYear == pasha.dayOfYear() - 1 && (pasha.dayOfWeek() == CreateCalindar::SATURDAY || pasha.dayOfWeek() == CreateCalindar::SUNDAY)) {
            cytanneDop = "На вячэрні: Гал 3.15-22; Мц 13.31-36";
        } /*else if (DayYear == pasha.dayOfYear() - 1) {
            cytanneDop = "На вячэрні: Быц 1.1-13; Лікі 24.2-3, 5-9, 17-18; Міх 4.6-7, 5.1-4; Іс 11.1-10;\nЕр 3.35-4.4; Дан 2.31-36, 44-45; Іс 9.5-6, 7.10-16, 8.1-4, 9-10";
        }*/
        pasha.setDate(year, CreateCalindar::JANUARY, 5);
        if (DayYear == pasha.dayOfYear() - 1 && (pasha.dayOfWeek() == CreateCalindar::SATURDAY || pasha.dayOfWeek() == CreateCalindar::SUNDAY)) {
            cytanneDop = "На вячэрні: 1 Кар 10.1-4; Лк 3.1-18";
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-16).dayOfYear()) {
            predsviaty = "<em>Субота акафісту</em>";
            sv_per_ch = "Багародзіцы: Габ 9.1-7; Лк 10.38-42, 11.27-28";
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(-9).dayOfYear()) {
            predsviaty = "<em>Лазарава субота</em>";
            sv_per_ch = "На вячэрні: Быц 49.1-2, 8-12; Саф 3.14-19; Зах 9.9-15";
        }
        QString sviachanni = "";
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.dayOfYear() - 1) {
            sviachanni = "Блаславеньне велікодных страваў";
        }
        if (DayYear == pasha.addDays(-7).dayOfYear() - 1) {
            sviachanni = "Блаславеньне вербаў";
        }
        pasha.setDate(year, CreateCalindar::JANUARY, 6);
        if (DayYear == pasha.dayOfYear() - 1) {
            sviachanni = "Вялікае асьвячэньне вады";
        }
        pasha.setDate(year, CreateCalindar::FEBRUARY, 2);
        if (DayYear == pasha.dayOfYear() - 1) {
            sviachanni = "Блаславеньне сьвечак";
        }
        pasha.setDate(year, month_p, data_p);
        if (DayYear == pasha.addDays(49).dayOfYear() - 1) {
            sviachanni = "Пасьля Літургіі Вячэрня з укленчаньнем";
        }
        pasha.setDate(year, CreateCalindar::AUGUST, 6);
        if (DayYear == pasha.dayOfYear() - 1) {
            sviachanni = "Блаславеньне садавіны";
        }
        pasha.setDate(year, CreateCalindar::AUGUST, 15);
        if (DayYear == pasha.dayOfYear() - 1) {
            sviachanni = "Блаславеньне духмяных зёлак";
        }
        QString sviatyia_new_o = sviatyia_new[DayYear][0]; // [DayYear][0];
        if (sviatyia_new_o != "" || sv_per != "") {
            QString br = "";
            if (sviatyia_new_o != "" && sv_per != "")
                br = "<br>";
            if (sv_per.contains("Пачатак царкоўнага году")) {
                sviatyiaName = sv_per + br + sviatyia_new_o;
            } else {
                sviatyiaName = sviatyia_new_o + br + sv_per;
            }
        }
        for (int dny = 24; dny <= 30; dny++) {
            pasha.setDate(year, CreateCalindar::JUNE, dny);
            int wik = pasha.dayOfWeek();
            if (wik == CreateCalindar::SUNDAY) {
                if (pasha.dayOfYear() - 1 == DayYear) {
                    QString br = "";
                    if (sviatyiaName != "")
                        br = "<br>";
                    sviatyiaName.append(br).append("Берасьцейскай іконы Маці Божай");
                }
            }
        }

        if (sviatyia_new[DayYear][2] == "7") {
            int sv1 = sviatyiaName.indexOf("$");
                if (sv1 != -1) {
                    sviatyiaName = "<font color=#d00505><strong>" + sviatyiaName.mid(0, sv1 + 1) + "</strong></font>" + sviatyiaName.mid(sv1 + 1);
                } else {
                    int sv2 = sviatyiaName.indexOf("<br>");
                    if (sv_per != "" && sv2 != -1)
                        sviatyiaName = "<font color=#d00505><strong>" + sviatyiaName.mid(0, sv2) + "</strong></font>" + sviatyiaName.mid(sv2);
                    else
                        sviatyiaName = "<font color=#d00505><strong>" + sviatyiaName + "</strong></font>";
                }
            }
        if (sviatyia_new[DayYear][2] == "6") {
            int sv1 = sviatyia_new_o.indexOf("$");
            if (sv1 != -1) {
                sviatyiaName = "<font color=#d00505>" + sviatyiaName.mid(0, sv1 + 1) + "</font>" + sviatyiaName.mid(sv1 + 1);
            } else {
                int sv2 = sviatyiaName.indexOf("<br>");
                if (sv_per != "" && sv2 != -1)
                    sviatyiaName = "<font color=#d00505>" + sviatyiaName.mid(0, sv2) + "</font>" + sviatyiaName.mid(sv2);
                else
                    sviatyiaName = "<font color=#d00505>" + sviatyiaName + "</font>";
            }
        }
        sviatyiaName = sviatyiaName.replace("$", "");

        if (bogaziaulenneNed == CreateCalindar::SATURDAY) {
            bogaziaulenne = bogaziaulenne - 1;
        }
        if (bogaziaulenneNed == CreateCalindar::SUNDAY) {
            bogaziaulenne = bogaziaulenne - 2;
        }
        if (AdsiachenneGalavyNed == CreateCalindar::SUNDAY) {
            AdsiachenneGalavy = AdsiachenneGalavy - 2;
        }
        if (KrygaUzvyshenneNed == CreateCalindar::SUNDAY) {
            KrygaUzvyshenne = KrygaUzvyshenne - 2;
        }
        if (KaliadyNed == CreateCalindar::SATURDAY) {
            Kaliady = Kaliady - 1;
        }
        if (KaliadyNed == CreateCalindar::SUNDAY) {
            Kaliady = Kaliady - 2;
        }
        QString tipicon = "0";

        if (sviatyia_new[DayYear][3] == "1") {
            tipicon = "1";
        }
        /*if (sviatyia_new[DayYear][3] == "2") {
            tipicon = "2";
        }*/
        if (sviatyia_new[DayYear][3] == "3") {
            tipicon = "3";
        }
        if (sviatyia_new[DayYear][3] == "4") {
            tipicon = "4";
        }
        if (sviatyia_new[DayYear][3] == "5") {
            tipicon = "5";
        }
        /*if (sviatyDay == "1") {
            tipicon = "2";
        }*/

        pasha.setDate(year, month_p, data_p);
        int pasxa = pasha.dayOfYear() - 1;
        int uvachod = pasha.addDays(-7).dayOfYear() - 1;
        int uzniasenne = pasha.addDays(-7 + 46).dayOfYear() - 1;
        int troica = pasha.addDays(-7 + 46 + 10).dayOfYear() - 1;
        int denSvDuxa = pasha.addDays(-7 + 46 + 10 + 1).dayOfYear() - 1;

        bool Strogipost = false;
        if (bogaziaulenne - 1 == DayYear || VialikiPost == DayYear || Pasxa - 3 == DayYear || AdsiachenneGalavy - 1 == DayYear || KrygaUzvyshenne - 1 == DayYear || Kaliady - 1 == DayYear) {
            postBild = "3";
            Strogipost = true;
        }

        // Переходящие праздники
        if (DayYear == pasxa) {
            post = false;
            postBild = "0";
        }
        if (DayYear == uvachod) {
            post = false;
            postBild = "0";
        }
        if (DayYear == uzniasenne) {
            post = false;
            postBild = "0";
        }
        if (DayYear == troica) {
            post = false;
            postBild = "0";
        }
        if (DayYear == denSvDuxa) {
            post = false;
            postBild = "0";
        }
        // когда выпадают ВЯЛІКІЯ СЬВЯТЫ относительно Пасхі
        QDate calendar_pasha(year, CreateCalindar::JANUARY, 1);
        int i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "Абр: Кал 2.8-12; Лк 2.20-21, 40-52";
                sviaty = "<strong>" + sviaty + "</strong>\nАБРЭЗАНЬНЕ ГАСПОДНЯЕ";
            } else {
                sviatyaChtenia = "На ютрані: Ян 10.9-16;\nКал 2.8-12; Лк 2.20-21, 40-52";
                sviaty = "АБРЭЗАНЬНЕ ГАСПОДНЯЕ";
            }
            post = false;
            postBild = "0";
            sviatyDay = "2";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::JUNE, 24);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            sviaty = "НАРАДЖЭНЬНЕ СЬВ. ЯНА ПРАДВЕСЬНІКА І ХРЫСЬЦІЦЕЛЯ ГАСПОДНЯГА";
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "На ютрані: Лк 1.24-25, 57-68, 76, 80;\nРым 13.12-14.4; Лк 1.5-25, 57-68, 76, 80";
            } else {
                sviatyaChtenia = "На ютрані: Лк 1.24-25, 57-68, 76, 80;\nРым 13.12-14.4; Лк 1.5-25, 57-68, 76, 80";
            }
            post = false;
            postBild = "0";
            sviatyDay = "2";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::JUNE, 29);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            sviaty = "СЬВЯТЫХ СЛАЎНЫХ І ЎСЯХВАЛЬНЫХ ВЯРХОЎНЫХ АПОСТАЛАЎ ПЯТРА І ПАЎЛА";
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "На ютрані: Ян 21.15-25;\n2 Кар 11.21-12.9; Мц 16.13-19";
            } else {
                sviatyaChtenia = "На ютрані: Ян 21.15-25;\n2 Кар 11.21-12.9; Мц 16.13-19";
            }
            post = false;
            postBild = "0";
            sviatyDay = "2";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::AUGUST, 29);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            sviaty = "АДСЯЧЭНЬНЕ ГАЛАВЫ СЬВ. ЯНА ПРАДВЕСЬНІКА І ХРЫСЬЦІЦЕЛЯ";
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "На ютрані: Мц 14.1-13;\nДз 13.25-32; Мк 6.14-30";
            } else {
                sviatyaChtenia = "На ютрані: Мц 14.1-13;\nДз 13.25-32; Мк 6.14-30";
            }
            sviatyDay = "2";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::OCTOBER, 1);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            sviaty = "ПОКРЫВА НАЙСЬВЯЦЕЙШАЙ БАГАРОДЗІЦЫ";
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "На ютрані: Лк 1.39-49, 56;\nГаб 9.1-7; Лк 10.38-42, 11.27-28";
            } else {
                sviatyaChtenia = "На ютрані: Лк 1.39-49, 56;\nГаб 9.1-7; Лк 10.38-42, 11.27-28";
            }
            post = false;
            postBild = "0";
            sviatyDay = "2";
            //tipicon = "2";
        }
        // когда выпадают ДВУНАДЗЯСЯТЫЯ СЬВЯТЫ относительно Пасхі, кроме зависящих от неё
        calendar_pasha.setDate(year, CreateCalindar::JANUARY, 6);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            sviaty = "БОГАЗЬЯЎЛЕНЬНЕ (Вадохрышча)";
            post = false;
            postBild = "0";
            sviatyaChtenia = "На ютрані: Мк 1.9-11;\nЦіт 2.11-14, 3.4-7; Мц 3.13-17";
            sv_per_ch = "На асьвячэньне вады: 1 Кар 10.1-4; Мк 1.9-11";
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::FEBRUARY, 2);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            post = false;
            postBild = "0";
            if (calendar_pasha.dayOfWeek() == CreateCalindar::SUNDAY) {
                sviaty.append("\n").append("\nСУСТРЭЧА ГОСПАДА НАШАГА ІСУСА ХРЫСТА (ГРАМНІЦЫ)");
                cytanneDop = "Сустрэчы: Габ 7.7-17; Лк 2.22-40";
            } else {
                sviaty = "СУСТРЭЧА ГОСПАДА НАШАГА ІСУСА ХРЫСТА (ГРАМНІЦЫ)";
                sviatyaChtenia = "На ютрані: Лк 2.25-32;\nГаб 7.7-17; Лк 2.22-40";
            }
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::MARCH, 25);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            QString linurgia = "Літургія сьв. Яна Залатавуснага";
            int bagar = calendar_pasha.dayOfWeek();
            if (bagar <= CreateCalindar::FRIDAY) linurgia = "Літургія сьв. Яна Залатавуснага з вячэрняй"; //Літургія сьв. Васіля Вялікага
            post = false;
            postBild = "0";
            if (Nedel == CreateCalindar::SUNDAY) {
                sviaty.append("\n").append("\nДАБРАВЕШЧАНЬНЕ НАЙСЬВЯЦЕЙШАЙ БАГАРОДЗІЦЫ");
                cytanneDop = "Дабравешчаньне: Тон 8. На ютрані: Лк 1.39-49, 56;\nГаб 9.11-14; Мк 10.32-45;\nГаб 2.11-18; Лк 1.24-38";
            } else {
                sviaty = "ДАБРАВЕШЧАНЬНЕ НАЙСЬВЯЦЕЙШАЙ БАГАРОДЗІЦЫ";
                sviatyaChtenia = "Тон 8. На ютрані: Лк 1.39-49, 56;\nГаб 9.11-14; Мк 10.32-45;\n" + linurgia + " Габ 2.11-18; Лк 1.24-38";
            }
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::AUGUST, 6);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            post = false;
            postBild = "0";
            sviaty = "ПЕРАМЯНЕНЬНЕ ГОСПАДА НАШАГА ІСУСА ХРЫСТА";
            sviatyaChtenia = "На ютрані: Лк 9.28-36;\n2 Пт 1.10-19; Мц 17.1-9";
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::AUGUST, 15);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            post = false;
            postBild = "0";
            sviaty = "УСЬПЕНЬНЕ НАЙСЬВЯЦЕЙШАЙ БАГАРОДЗІЦЫ";
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "На ютрані: Лк 1.39-49, 56;\nФлп 2.5-11; Лк 10.38-42, 11.27-28";
            } else {
                sviatyaChtenia = "На ютрані: Лк 1.39-49, 56;\nФлп 2.5-11; Лк 10.38-42, 11.27-28";
            }
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::SEPTEMBER, 8);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            post = false;
            postBild = "0";
            sviaty = "НАРАДЖЭНЬНЕ НАЙСЬВЯЦЕЙШАЙ БАГАРОДЗІЦЫ";
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "На ютрані: Лк 1.39-49, 56;\nФлп 2.5-11; Лк 10.38-42, 11.27-28";
            } else {
                sviatyaChtenia = "На ютрані: Лк 1.39-49, 56;\nФлп 2.5-11; Лк 10.38-42, 11.27-28";
            }
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::SEPTEMBER, 14);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            sviaty = "УЗВЫШЭНЬНЕ ПАЧЭСНАГА І ЖЫЦЬЦЯДАЙНАГА КРЫЖА";
            sviatyaChtenia = "На ютрані: Ян 12.28-36;\n1 Кар 1.18-24; Ян 19.6-11, 13-20, 25-28, 30-35";
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::NOVEMBER, 21);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            post = false;
            postBild = "0";
            sviaty = "УВАХОД У ХРАМ НАЙСЬВЯЦЕЙШАЙ БАГАРОДЗІЦЫ";
            if (Nedel == CreateCalindar::SUNDAY && !sviatyaChtenia.isEmpty()) {
                cytanneDop = "На ютрані: Лк 1.39-49, 56;\nГаб 9.1-7; Лк 10.38-42, 11.27-28";
            } else {
                sviatyaChtenia = "На ютрані: Лк 1.39-49, 56;\nГаб 9.1-7; Лк 10.38-42, 11.27-28";
            }
            sviatyDay = "1";
            //tipicon = "2";
        }
        calendar_pasha.setDate(year, CreateCalindar::DECEMBER, 25);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            post = false;
            postBild = "0";
            sviaty = "НАРАДЖЭНЬНЕ ГОСПАДА НАШАГА ІСУСА ХРЫСТА (РАСТВО)";
            sviatyaChtenia = "На ютрані: Мц 1.18-25;\nГал 4.4-7; Мц 2.1-12";
            sviatyDay = "1";
            //tipicon = "2";
        }
        // когда выпадают ПРЕДПРАЗДНИЧНЫЕ ДНИ относительно Пасхі
        calendar_pasha.setDate(year, CreateCalindar::JANUARY, 5);
        i3 = calendar_pasha.dayOfYear() - 1;
        if (DayYear == i3) {
            if (calendar_pasha.dayOfWeek() == CreateCalindar::SUNDAY) {
                predsviaty = "СЬВЯТЫ ВЕЧАР ПЕРАД БОГАЗЬЯЎЛЕНЬНЕМ";
            } else {
                sviaty = "СЬВЯТЫ ВЕЧАР ПЕРАД БОГАЗЬЯЎЛЕНЬНЕМ";
                sviatyaChtenia = "1 Кар 9.19-27; Лк 3.1-18";
            }
        }

        pasha.setDate(year, month_p, data_p);
        int vialikaiaSubota = pasha.addDays(-1).dayOfYear() - 1;
        if (!Strogipost) {
            if ((Nedel == CreateCalindar::FRIDAY && post) || vialikaiaSubota == DayYear) {
                postBild = "2";
            }
        }
        if (Nedel == CreateCalindar::SUNDAY)
            niadzeliaAdapter++;
        if (mun != c2.month()) {
            mun = c2.month();
            munAdapter++;
        }
        QDate gc(year, month_p, data_p);
        QDate tdate(year, c2.month(), c2.day());
        int raznica = tdate.dayOfYear() - gc.dayOfYear();
        int javaNedel = Nedel + 1;
        if (javaNedel == 8) javaNedel = 1;
        arrayList.append(QString::number(javaNedel)); //День недели 0
        arrayList.append(QString::number(c2.day())); // Дата 1
        arrayList.append(QString::number(c2.month() - 1)); // Месяц 2
        arrayList.append(QString::number(year)); // Год 3

        arrayList.append(sviatyiaName); // Имена Святых 4
        if (sviatyDay.contains("1")) {
            arrayList.append("1");// Обозначение Двунадесятого праздника 5
        } else if (sviatyDay.contains("2")) {
            arrayList.append("2");// Обозначение обычного праздника 5
        } else if (Nedel == CreateCalindar::SUNDAY) {
            arrayList.append("3"); // Обозначение воскресенья 5
        } else {
            arrayList.append("0"); // обычный день 5
        }
        if (sviaty != "") arrayList.append(sviaty); // Праздники 6
        else arrayList.append("no_sviaty"); // нет праздников 6
        arrayList.append(postBild); // значение поста(0-обычный день, 1-нет поста, 2-пост, 3-строги пост) 7
        arrayList.append(predsviaty); //Предпраздники 8

        if (sviatyia_new[DayYear][1] != "") {
            cytanneSV = sviatyia_new[DayYear][1].replace("<br>", "\n");
        }
        if (sv_per_ch != "") {
            if (cytanneSV == "")
                cytanneSV = sv_per_ch;
            else
                cytanneDop = sv_per_ch;
        }
        QString ton = "0";
        //if (Nedel == CreateCalindar::SUNDAY) {
        if (sviatyaChtenia != "") {
             for (int i = 1; i <= 8; i++) {
                if (sviatyaChtenia.contains("Тон " + QString::number(i))) {
                    int t1 = sviatyaChtenia.indexOf("Тон " + QString::number(i) + ".");
                    sviatyaChtenia = sviatyaChtenia.mid(t1 + 6).trimmed();
                    ton = QString::number(i);
                    break;
                }
            }
        }
        //}
        sviatyaChtenia = translateToBelarus(sviatyaChtenia);
        cytanneSV = translateToBelarus(cytanneSV);
        cytanneDop = translateToBelarus(cytanneDop);
        QString maranata = translateToBelarus(MaranAta(DayYear, year));
        arrayList.append(sviatyaChtenia); // Церковные чтения на каждый день 9
        arrayList.append(cytanneSV); // чтения святых 10
        arrayList.append(cytanneDop); // чтения дополнительные 11
        arrayList.append(tipicon); // знаки типикона 12
        arrayList.append(maranata); // Чтения маран аты 13
        arrayList.append(pascha_pravas(DayYear, year)); // Православные праздники 14
        arrayList.append(gosudarstvo(DayYear, year)); // Государственные праздники Выходные 15
        arrayList.append(gosudarstvoRab(DayYear, year)); // Государственные праздники Рабочие 16
        arrayList.append(profesional(DayYear, year)); // Професиональные праздники 17
        arrayList.append(pameplyia); // Умершие 18
        arrayList.append(sviatyPKC(DayYear, year)); // Римо-каталические праздники 19

        if (year == CreateCalindar::outyear) {
            if (DayYear < gc.dayOfYear() || DayYear > 257) {
                arrayList.append("0"); // Тон в Воскресенье 20
            } else {
                arrayList.append(ton); // Тон в Воскресенье 20
            }
        } else {
            arrayList.append(ton); // Тон в Воскресенье 20
        }
        arrayList.append(sviachanni); // Блаславеньні на сьвяты 21
        arrayList.append(QString::number(raznica)); // Количество дней до и после Пасхи 22
        arrayList.append(QString::number(munAdapter)); // Номер позиции в месячном адапторе 23
        int dayInYear = c2.dayOfYear();
        if (!c2.isLeapYear(year) && dayInYear > 59) dayInYear++;
        arrayList.append(QString::number(dayInYear)); // День в году 24
        arrayList.append(QString::number(e - 1)); //Номер позиции в адапторе 25
        arrayList.append(QString::number(niadzeliaAdapter)); //Номер позиции в недельном адапторе 26
        arrayListsNelel.append(arrayList);
        c2 = c2.addDays(1);
        emit update(&e);
    }
        QString saveFileName = malitounikPatch +  "/malitounik-bgkc/src/main/res/raw/caliandar.json";
        QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
        QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
        // Создаём объект файла и открываем его на запись
        QFile jsonFile(saveFileName);
        if (jsonFile.open(QIODevice::WriteOnly))
        {
            // Записываем текущий объект Json в файл
            jsonFile.write(QJsonDocument(arrayListsNelel).toJson(QJsonDocument::Compact));
            jsonFile.close();   // Закрываем файл
        }
    gratePamiatekaVernikau(CreateCalindar::outyear - 1);
    emit finished();
}

void CreateCalindar::setViersionApp(bool relise) {
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    QUrl url("https://android.carkva-gazeta.by/admin/android.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrlQuery params;
    params.addQueryItem("saveProgram", "1");
    params.addQueryItem("updateCode", "1");
    if (relise && !CreateCalindar::release.isEmpty()) {
        params.addQueryItem("reliseApp", CreateCalindar::release);
        emit finished();
    }
    if (!relise && !CreateCalindar::devel.isEmpty()) {
        params.addQueryItem("devApp", CreateCalindar::devel);
        emit finished();
    }
    manager->post(request, params.query().toUtf8());
}

void CreateCalindar::onResult(QNetworkReply *reply)
{
    if(!reply->error()){
        position = 0;
        disconnect(networkManager, &QNetworkAccessManager::finished, this, &CreateCalindar::onResult);
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
            QJsonArray download = document.array();
            labal = "Запамповываем файлы з сайта Царквы:";
            for (int i = 0; i < download.size();i++) {
                QJsonValue val = download.at(i);
                QJsonArray arr = val.toArray();
                QString filePath = arr[0].toString().replace("carkva-gazeta.by", "android.carkva-gazeta.by");
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
                    ja.append(filePath);
                }
            }
            size = ja.size();
            if (size == 0) {
                size = 1;
                emit getSize(&size, &labal);
                emit update(&size);
                CreateCalindar::generateCaliandar();
            } else {
                emit getSize(&size, &labal);
                connect(networkManager, &QNetworkAccessManager::finished, this, &CreateCalindar::onDownload);
                networkManager->get(QNetworkRequest(QUrl(ja.at(position).toString())));
            }
    }
    reply->deleteLater();
}

void CreateCalindar::onDownload(QNetworkReply *reply)
{
    if(reply->error()) {
        return;
    }
    QByteArray read = reply->readAll();
        QString getFile = ja.at(position).toString();
        getFile = getFile.replace("https://android.carkva-gazeta.by", "");
        int t1 = getFile.lastIndexOf("/");
        QString filename = carkvaPatch + getFile;
        QString dir = carkvaPatch + getFile.mid(0, t1);
        QDir qdir(dir);
        if (!qdir.exists()) {
            qdir.mkpath(dir);
        }
        if (getFile.contains("/admin/getFilesCaliandar.php?year=")) {
            int t2 = getFile.mid(t1).lastIndexOf("=");
            QString yaer = getFile.mid(t1).mid(t2 + 1);
            QJsonDocument document = QJsonDocument::fromJson(read);
            QJsonArray root = document.array();
            QByteArray stringV = root[0].toString().toUtf8();
            filename = carkvaPatch + "/calendar-cytanne_" + yaer + ".php";
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(stringV);
            }
            file.close();
        } else {
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(read);
            }
            file.close();
        }
        if (getFile.contains("/admin/pesny")) {
            QString filenameprogram = malitounikPatch + "/malitounik-bgkc/src/main/res/raw" + getFile.mid(t1);
            QFile file(filenameprogram);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(read);
            }
            file.close();
        }
        if (getFile.contains("/admin/parafii_bgkc/") || getFile.contains("/chytanne/Semucha/") || getFile.contains("/admin/prynagodnyia/") || getFile.contains("/admin/bogashlugbovya/")) {
            QString filenameprogram = malitounikPatch + "/resources/src/main/res/raw" + getFile.mid(t1);
            QFile file(filenameprogram);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(read);
            }
            file.close();
        }
        position++;
        if (position < ja.size()) {
            emit update(&position);
            getFile = ja.at(position).toString();
            networkManager->get(QNetworkRequest(QUrl(getFile)));
        } else {
            CreateCalindar::generateCaliandar();
        }
    reply->deleteLater();
}

void CreateCalindar::sviatyia(int Year) {
        QDate gregorianCalendar = QDate::currentDate();
        QString saveFileName = carkvaPatch + "/calendarsviatyia.txt";
        QFileInfo fileInfo(saveFileName);
        QDir::setCurrent(fileInfo.path());
        QFile file(saveFileName);
        QString line = "";
        if (file.open(QIODevice::ReadOnly))
        {
            int e = 0, e2 = 59;
            while(!file.atEnd())
            {
                line=file.readLine();
                QStringList re1 = line.split("<>");
                if (gregorianCalendar.isLeapYear(Year)) {
                    for (int q = 0; q < re1.size(); q++) {
                        if (e == 0)
                            // исправление чтения на 1 января
                            sviatyia_new[e][q] = re1[q].trimmed().replace("<br>", "\n");
                        else
                            sviatyia_new[e][q] = re1[q].trimmed();
                    }
                } else {
                    if (e == 59) {
                        e++;
                        continue;
                    }
                    if (e < 59) {
                        for (int q = 0; q < re1.size(); q++) {
                            if (e == 0)
                                // исправление чтения на 1 января
                                sviatyia_new[e][q] = re1[q].trimmed().replace("<br>", "\n");
                            else
                                sviatyia_new[e][q] = re1[q].trimmed();
                        }
                    } else {
                        for (int q = 0; q < re1.size(); q++) {
                            sviatyia_new[e2][q] = re1[q].trimmed();
                        }
                        e2++;
                    }
                }
                e++;
            }
            file.close();
        }
    }

    void CreateCalindar::getSviatyYear(int Year) {
        if (Year != YearG || svitya[0][0] == "") {
            YearG = Year;
            QString sb = "";
            QString saveFileName = carkvaPatch + "/calendar-cytanne_" + QString::number(Year) + ".php";
            QFileInfo fileInfo(saveFileName);
            QDir::setCurrent(fileInfo.path());
            QFile file(saveFileName);
            if (!file.exists()) {
                int calendar = QDate::currentDate().year();
                saveFileName = carkvaPatch + "/calendar-cytanne_" + QString::number(calendar) + ".php";
            }
            if (file.open(QIODevice::ReadOnly))
            {
                while(!file.atEnd())
                {
                    sb = sb + file.readLine();
                }
                file.close();
            }
            QStringList res = sb.split("$calendar[]=array(");
            for (int i = 1; i < res.size(); i++) {
                QStringList red = res[i].split("cytanne");
                int t1 = red[0].indexOf("=>\"");
                int t2 = red[0].indexOf("-->", t1 + 3);
                int t3 = red[0].indexOf("\"", t1 + 3);
                QString cviaty;
                if (t2 != -1) {
                    cviaty = red[0].mid(t2 + 3, t3 - (t2 + 3));
                } else {
                    cviaty = red[0].mid(t1 + 3, t3 - (t1 + 3));
                }
                cviaty = cviaty.replace("<br>", " ");
                QString cytanne = "";
                int v1 = red[1].indexOf("ahref.\"");
                if (v1 != -1) {
                    int v2 = red[1].indexOf("</a>", v1);
                    if (v2 != -1)
                        cytanne = red[1].mid(v1 + 7, v2 - (v1 + 7)).replace("<br>", "\n");
                    else
                        cytanne = red[1].mid(v1 + 7).replace("<br>", "\n");
                }
                QString number = "";
                int s1 = red[0].indexOf("<!--");
                if (s1 != -1) {
                    int s2 = red[0].indexOf("-->", s1 + 4);
                    QString pre_res = red[0].mid(s1 + 4, s2 - (s1 + 4));
                    int s3 = pre_res.indexOf(" ");
                    if (s3 != -1) {
                        number = pre_res.mid(0, s3);
                    } else {
                        number = pre_res;
                    }
                }
                svitya[i - 1][0] = cviaty;
                svitya[i - 1][1] = cytanne;
                svitya[i - 1][2] = number;
            }
        }
    }

    QString CreateCalindar::getSviaty(int Year, int DayYaer, int f) {
        getSviatyYear(Year);
        return svitya[den(Year, DayYaer)][f];
    }

    int CreateCalindar::den(int Year, int DayYaer) {
            int data_p, month_p;
            int a = Year % 19;
            int b = Year % 4;
            int cx = Year % 7;
            int k = (Year / 100);
            int p = (13 + 8 * k) / 25;
            int q = (k / 4);
            int m = (15 - p + k - q) % 30;
            int n = (4 + k - q) % 7;
            int d = (19 * a + m) % 30;
            int ex = (2 * b + 4 * cx + 6 * d + n) % 7;
            if (d + ex <= 9) {
                data_p = d + ex + 22;
                month_p = CreateCalindar::MARCH;
            } else {
                data_p = d + ex - 9;
                if (d == 29 && ex == 6) data_p = 19;
                if (d == 28 && ex == 6) data_p = 18;
                month_p = CreateCalindar::APRIL;
            }
            QDate pasha(Year, month_p, data_p);
            int pashaDay = pasha.dayOfYear() - 1;
            int nachaloGoda = 365 - pashaDay;
            int tekusiyDen;
            if (DayYaer < pashaDay) tekusiyDen = nachaloGoda + DayYaer;
            else tekusiyDen = DayYaer - pashaDay;
            return tekusiyDen;
    }

    QString CreateCalindar::translateToBelarus(QString paralel) {
            paralel = paralel.replace("Ёва", "Ёў");
            paralel = paralel.replace("Флп", "Плп");
            paralel = paralel.replace("Кал", "Клс");
            paralel = paralel.replace("Езэк", "Езк");
            paralel = paralel.replace("1 Сал", "1 Фес");
            paralel = paralel.replace("2 Сал", "2 Фес");
            paralel = paralel.replace("Яэль", "Ёіл");
            paralel = paralel.replace("Габ", "Гбр");
            paralel = paralel.replace("Муд", "Мдр");
            paralel = paralel.replace("Друг", "Дрг");
            //paralel = paralel.replace("Лк", "Лук");

            paralel = paralel.replace("Быт", "Быц");
            paralel = paralel.replace("Исх", "Вых");
            paralel = paralel.replace("Лев", "Ляв");
            paralel = paralel.replace("Чис", "Лікі");
            paralel = paralel.replace("Втор", "Дрг");
            paralel = paralel.replace("Руфь", "Рут");
            paralel = paralel.replace("1 Пар", "1 Лет");
            paralel = paralel.replace("2 Пар", "2 Лет");
            paralel = paralel.replace("1 Езд", "1 Эзд");
            paralel = paralel.replace("Неем", "Нээм");
            paralel = paralel.replace("2 Езд", "2 Эзд");
            paralel = paralel.replace("Тов", "Тав");
            paralel = paralel.replace("Иудифь", "Юдт");
            paralel = paralel.replace("Есф", "Эст");
            paralel = paralel.replace("Иов", "Ёва");
            //paralel = paralel.replace("Пс", "Пс");
            paralel = paralel.replace("Притч", "Высл");
            paralel = paralel.replace("Еккл", "Экл");
            paralel = paralel.replace("Песн", "Псн");
            paralel = paralel.replace("Прем", "Мдр");
            paralel = paralel.replace("Сир", "Сір");
            paralel = paralel.replace("Ис", "Іс");
            paralel = paralel.replace("Посл Иер", "Пасл Ер");
            paralel = paralel.replace("Иер", "Ер");
            paralel = paralel.replace("Иез", "Езк");
            //paralel = paralel.replace("Дан", "Дан");
            paralel = paralel.replace("Ос", "Ас");
            paralel = paralel.replace("Иоил", "Ёіл");
            //paralel = paralel.replace("Ам", "Ам");
            paralel = paralel.replace("Авд", "Аўдз");
            paralel = paralel.replace("Иона", "Ёны");
            paralel = paralel.replace("Мих", "Міх");
            paralel = paralel.replace("Наум", "Нвм");
            paralel = paralel.replace("Авв", "Абк");
            paralel = paralel.replace("Соф", "Саф");
            paralel = paralel.replace("Агг", "Аг");
            paralel = paralel.replace("3 Езд", "3 Эзд");
            paralel = paralel.replace("Мф", "Мц");
            paralel = paralel.replace("Ин", "Ян");
            paralel = paralel.replace("Деян", "Дз");
            paralel = paralel.replace("Иак", "Як");
            paralel = paralel.replace("1 Пет", "1 Пт");
            paralel = paralel.replace("2 Пет", "2 Пт");
            paralel = paralel.replace("1 Ин", "1 Ян");
            paralel = paralel.replace("2 Ин", "2 Ян");
            paralel = paralel.replace("3 Ин", "3 Ян");
            paralel = paralel.replace("Иуд", "Юд");
            paralel = paralel.replace("Рим", "Рым");
            paralel = paralel.replace("1 Кор", "1 Кар");
            paralel = paralel.replace("2 Кор", "2 Кар");
            //paralel = paralel.replace("Гал", "Гал");
            paralel = paralel.replace("Еф", "Эф");
            paralel = paralel.replace("Флп", "Плп");
            paralel = paralel.replace("Кол", "Клс");
            paralel = paralel.replace("1 Тим", "1 Цім");
            paralel = paralel.replace("2 Тим", "2 Цім");
            paralel = paralel.replace("Тит", "Ціт");
            //paralel = paralel.replace("Флм", "Флм");
            paralel = paralel.replace("Евр", "Гбр");
            paralel = paralel.replace("Откр", "Адкр");
            return paralel;
     }

    QString CreateCalindar::MaranAta(int pageNumber, int year) {
            QString maranata[366];
            maranata[0] = "Пс 1-2; Быт 1-2; Мф 1";
            maranata[1] = "Пс 3-4; Быт 3-5; Мф 2";
            maranata[2] = "Пс 5-6; Быт 6-8; Мф 3";
            maranata[3] = "Пс 7-8; Быт 9-11; Мф 4";
            maranata[4] = "Пс 9; Быт 12-14; Мф 5.1-20";
            maranata[5] = "Пс 10-11; Быт 15-17; Мф 5.21-48";
            maranata[6] = "Пс 12-13; Быт 18-19; Мф 6.1-18";
            maranata[7] = "Пс 14-15; Быт 20-22; Мф 6.19-7.6";
            maranata[8] = "Пс 16; Быт 23-24; Мф 7.7-29";
            maranata[9] = "Пс 17; Быт 25-26; Мф 8.1-27";
            maranata[10] = "Пс 18-19; Быт 27-28; Мф 8.28-9.17";
            maranata[11] = "Пс 20-21; Быт 29-30; Мф 9.18-38";
            maranata[12] = "Пс 22-23; Быт 31-33; Мф 10.1-23";
            maranata[13] = "Пс 24-25; Быт 34-35; Мф 10.24-42";
            maranata[14] = "Пс 26-27; Быт 36-37; Мф 11";
            maranata[15] = "Пс 28-29; Быт 38-39; Мф 12.1-21";
            maranata[16] = "Пс 30; Быт 40-41; Мф 12.22-50";
            maranata[17] = "Пс 31-32; Быт 42-43; Мф 13.1-23";
            maranata[18] = "Пс 33; Быт 44-45; Мф 13.24-43";
            maranata[19] = "Пс 34-35; Быт 46-48; Мф 13.44-14.12";
            maranata[20] = "Пс 36; Быт 49-50; Мф 14.13-36";
            maranata[21] = "Пс 37-38; Исх 1-2; Мф 15.1-28";
            maranata[22] = "Пс 39; Исх 3-5; Мф 15.29-16.12";
            maranata[23] = "Пс 40-41; Исх 6-7; Мф 16.13-17.13";
            maranata[24] = "Пс 42-43; Исх 8-9; Мф 17.14-18.14";
            maranata[25] = "Пс 44-45; Исх 10-12; Мф 18.15-35";
            maranata[26] = "Пс 46-47; Исх 13-14; Мф 19.1-15";
            maranata[27] = "Пс 48-49; Исх 15; Мф 19.16-20.16";
            maranata[28] = "Пс 50-51; Исх 16-17; Мф 20.17-34";
            maranata[29] = "Пс 52-53; Исх 18-19; Мф 21.1-32";
            maranata[30] = "Пс 54; Исх 20-21; Мф 21.33-22.14";
            maranata[31] = "Пс 55-56; Исх 22-23; Мф 22.15-46";
            maranata[32] = "Пс 57-58; Исх 24-25; Мф 23";
            maranata[33] = "Пс 59-60; Исх 26-27; Мф 24.1-35";
            maranata[34] = "Пс 61-62; Исх 28; Мф 24.36-51";
            maranata[35] = "Пс 63-64; Исх 29-30; Мф 25.1-30";
            maranata[36] = "Пс 65-66; Исх 31; Мф 25.31-46";
            maranata[37] = "Пс 67; Исх 32-33; Мф 26.1-30";
            maranata[38] = "Пс 68; Исх 34-35; Мф 26.31-56";
            maranata[39] = "Пс 69-70; Исх 36-37; Мф 26.57-75";
            maranata[40] = "Пс 71; Исх 38-39; Мф 27.1-26";
            maranata[41] = "Пс 72; Исх 40; Мф 27.27-44";
            maranata[42] = "Пс 73-74; Лев 1-3; Мф 27.45-66";
            maranata[43] = "Пс 75-76; Лев 4-5; Мф 28";
            maranata[44] = "Пс 77; Лев 6-7; Деян 1";
            maranata[45] = "Пс 78-79; Лев 8; Деян 2.1-21";
            maranata[46] = "Пс 80-81; Лев 9-10; Деян 2.22-47";
            maranata[47] = "Пс 82; Лев 11-12; Деян 3";
            maranata[48] = "Пс 83-84; Лев 13-14; Деян 4.1-31";
            maranata[49] = "Пс 85-86; Лев 15; Деян 4.32-5.11";
            maranata[50] = "Пс 87; Лев 16-17; Деян 5.12-42";
            maranata[51] = "Пс 88; Лев 18-20; Деян 6";
            maranata[52] = "Пс 89; Лев 21-22; Деян 7.1-53";
            maranata[53] = "Пс 90; Лев 23-24; Деян 7.54-8.8";
            maranata[54] = "Пс 91-92; Лев 25; Деян 8.9-40";
            maranata[55] = "Пс 93-94; Лев 26-27; Деян 9.1-31";
            maranata[56] = "Пс 95-96; Чис 1-2; Деян 9.32-43";
            maranata[57] = "Пс 97-98; Чис 3-4; Деян 10.1-23";
            maranata[58] = "Пс 99-100; Чис 5-6; Деян 10.24-48";
            maranata[59] = "Пс 101; Чис 7-8; Деян 11.1-18";
            maranata[60] = "Пс 102; Чис 9-10; Деян 11.19-30";
            maranata[61] = "Пс 103; Чис 11-12; Деян 12";
            maranata[62] = "Пс 104; Чис 13-14; Деян 13.1-12";
            maranata[63] = "Пс 105;  Чис 15; Деян 13.13-52";
            maranata[64] = "Пс 106; Чис 16-17; Деян 14";
            maranata[65] = "Пс 107; Чис 18-19; Деян 15.1-21";
            maranata[66] = "Пс 108; Чис 20-21; Деян 15.22-35";
            maranata[67] = "Пс 109-110; Чис 22-23; Деян 15.36-16.15";
            maranata[68] = "Пс 111-112; Чис 24-26; Деян 16.16-40";
            maranata[69] = "Пс 113; Чис 27-28; Деян 17.1-15";
            maranata[70] = "Пс 114-115; Чис 29-31; Деян 17.16-34";
            maranata[71] = "Пс 117; Чис 32-33; Деян 18.1-23";
            maranata[72] = "Пс 118; Чис 34-36; Деян 18.24-19.7";
            maranata[73] = "Пс 119-121; Втор 1-2; Деян 19.8-40";
            maranata[74] = "Пс 122-123; Втор 3-4; Деян 20.1-16";
            maranata[75] = "Пс 124-125; Втор 5-7; Деян 20.17-38";
            maranata[76] = "Пс 126-127; Втор 8-9; Деян 21.1-16";
            maranata[77] = "Пс 128-129; Втор 10-11; Деян 21.17-36";
            maranata[78] = "Пс 130-131; Втор 12-13; Деян 21.37-22.21";
            maranata[79] = "Пс 132-133; Втор 14-15; Деян 22.22-23.11";
            maranata[80] = "Пс 134; Втор 16-17; Деян 23.12-35";
            maranata[81] = "Пс 135; Втор 18-21; Деян 24";
            maranata[82] = "Пс 136-137; Втор 22-24; Деян 25.1-12";
            maranata[83] = "Пс 138; Втор 25-27; Деян 25.13-26.1";
            maranata[84] = "Пс 139-140; Втор 28; Деян 26.2-18";
            maranata[85] = "Пс 141-142; Втор 29-30; Деян 26.19-32";
            maranata[86] = "Пс 143; Втор 31-32; Деян 27.1-26";
            maranata[87] = "Пс 144-145; Втор 33-34; Деян 27.27-44";
            maranata[88] = "Пс 146-147; Нав 1-2; Деян 28.1-16";
            maranata[89] = "Пс 148; Нав 3-4; Деян 28.17-31";
            maranata[90] = "Пс 149-151; Нав 5-6; Мк 1.1-20";
            maranata[91] = "Пс 1-2; Нав 7-9; Мк 1.21-45";
            maranata[92] = "Пс 3-4; Нав 10-12; Мк 2.1-22";
            maranata[93] = "Пс 5-6; Нав 13-15; Мк 2.23-3.12";
            maranata[94] = "Пс 7-8; Нав 16-19; Мк 3.13-35";
            maranata[95] = "Пс 9; Нав 20-22; Мк 4.1-20";
            maranata[96] = "Пс 10-11; Нав 23-24; Мк 4.21-41";
            maranata[97] = "Пс 12-13; Суд 1-2; Мк 5.1-20";
            maranata[98] = "Пс 14-15; Суд 3-4; Мк 5.21-43";
            maranata[99] = "Пс 16; Суд 5-6; Мк 6.1-29";
            maranata[100] = "Пс 17; Суд 7-8; Мк 6.30-56";
            maranata[101] = "Пс 18-19; Суд 9; Мк 7.1-23";
            maranata[102] = "Пс 20-21; Суд 10-11; Мк 7.24-8.13";
            maranata[103] = "Пс 22-23; Суд 12-13; Мк 8.14-26";
            maranata[104] = "Пс 24-25; Суд 14-16; Мк 8.27-9.13";
            maranata[105] = "Пс 26-27; Суд 17-18; Мк 9.14-32";
            maranata[106] = "Пс 28-29; Суд 19-21; Мк 9.33-50";
            maranata[107] = "Пс 30; Руфь 1-4; Мк 10.1-31";
            maranata[108] = "Пс 31-32; 1 Цар 1-2; Мк 10.32-52";
            maranata[109] = "Пс 33; 1 Цар 3-7; Мк 11.1-26";
            maranata[110] = "Пс 34-35; 1 Цар 8-10; Мк 11.27-12.17";
            maranata[111] = "Пс 36; 1 Цар 11-13; Мк 12.18-44";
            maranata[112] = "Пс 37-38; 1 Цар 14-15; Мк 13";
            maranata[113] = "Пс 39; 1 Цар 16-17; Мк 14.1-26";
            maranata[114] = "Пс 40-41; 1 Цар 18-19; Мк 14.27-52";
            maranata[115] = "Пс 42-43; 1 Цар 20-22; Мк 14.53-72";
            maranata[116] = "Пс 44-45; 1 Цар 23-25; Мк 15.1-20";
            maranata[117] = "Пс 46-47; 1 Цар 26-28; Мк 15.21-47";
            maranata[118] = "Пс 48-49; 1 Цар 29-31; Мк 16";
            maranata[119] = "Пс 50-51; 2 Цар 1-3; Иуды";
            maranata[120] = "Пс 52-53; 2 Цар 4-6; 1 Пет 1.1-21";
            maranata[121] = "Пс 54; 2 Цар 7-8; 1 Пет 1.22-2.25";
            maranata[122] = "Пс 55-56; 2 Цар 9-11; 1 Пет 3";
            maranata[123] = "Пс 57-58; 2 Цар 12-14; 1 Пет 4";
            maranata[124] = "Пс 59-60; 2 Цар 15-17; 1 Пет 5";
            maranata[125] = "Пс 61-62; 2 Цар 18-19; 2 Пет 1";
            maranata[126] = "Пс 63-64; 2 Цар 20-21; 2 Пет 2";
            maranata[127] = "Пс 65-66; 2 Цар 22; 2 Пет 3";
            maranata[128] = "Пс 67; 2 Цар 23-24; Иак 1";
            maranata[129] = "Пс 68; 3 Цар 1; Иак 2.1-3.13";
            maranata[130] = "Пс 69-70; 3 Цар 2-3; Иак 3.14-4.12";
            maranata[131] = "Пс 71; 3 Цар 4-6; Иак 4.13-5.20";
            maranata[132] = "Пс 72; 3 Цар 7-8; Лк 1.1-25";
            maranata[133] = "Пс 73-74; 3 Цар 9; Лк 1.26-56";
            maranata[134] = "Пс 75-76; 3 Цар 10-11; Лк 1.57-80";
            maranata[135] = "Пс 77; 3 Цар 12-14; Лк 2.1-20";
            maranata[136] = "Пс 78-79; 3 Цар 15-17; Лк 2.21-52";
            maranata[137] = "Пс 80-81; 3 Цар 18-19; Лк 3";
            maranata[138] = "Пс 82; 3 Цар 20-21; Лк 4.1-13";
            maranata[139] = "Пс 83-84; 3 Цар 22; Лк 4.14-44";
            maranata[140] = "Пс 85-86; 4 Цар 1-3; Лк 5.1-16";
            maranata[141] = "Пс 87; 4 Цар 4-5; Лк 5.17-39";
            maranata[142] = "Пс 88; 4 Цар 6-7; Лк 6.1-16";
            maranata[143] = "Пс 89; 4 Цар 8-9; Лк 6.17-49";
            maranata[144] = "Пс 90; 4 Цар 10-12; Лк 7.1-35";
            maranata[145] = "Пс 91-92; 4 Цар 13-15; Лк 7.36-50";
            maranata[146] = "Пс 93-94; 4 Цар 16-17; Лк 8.1-21";
            maranata[147] = "Пс 95-96; 4 Цар 18-19; Лк 8.22-39";
            maranata[148] = "Пс 97-98; 4 Цар 20-22; Лк 8.40-56";
            maranata[149] = "Пс 99-100; 4 Цар 23-25; Лк 9.1-17";
            maranata[150] = "Пс 101; 1 Пар 1-2; Лк 9.18-36";
            maranata[151] = "Пс 102; 1 Пар 3-4; Лк 9.37-62";
            maranata[152] = "Пс 103; 1 Пар 5-6; Лк 10.1-24";
            maranata[153] = "Пс 104; 1 Пар 7-8; Лк 10.25-42";
            maranata[154] = "Пс 105; 1 Пар 9-10; Лк 11.1-13";
            maranata[155] = "Пс 106; 1 Пар 11-13; Лк 11.14-36";
            maranata[156] = "Пс 107; 1 Пар 14-16; Лк 11.37-54";
            maranata[157] = "Пс 108; 1 Пар 17-19; Лк 12.1-21";
            maranata[158] = "Пс 109-110; 1 Пар 20-22; Лк 12.22-48";
            maranata[159] = "Пс 111-112; 1 Пар 23-25; Лк 12.49-59";
            maranata[160] = "Пс 113; 1 Пар 26-29; Лк 13.1-21";
            maranata[161] = "Пс 114-116; 2 Пар 1-4; Лк 13.22-35";
            maranata[162] = "Пс 117; 2 Пар 5-7; Лк 14.1-24";
            maranata[163] = "Пс 118; 2 Пар 8-9; Лк 14.25-15.10";
            maranata[164] = "Пс 119-121; 2 Пар 10-12; Лк 15.11-32";
            maranata[165] = "Пс 122-123; 2 Пар 13-15; Лк 16";
            maranata[166] = "Пс 124-125; 2 Пар 16-18; Лк 17.1-19";
            maranata[167] = "Пс 126-127; 2 Пар 19-20; Лк 17.20-18.14";
            maranata[168] = "Пс 128-129; 2 Пар 21-23; Лк 18.15-43";
            maranata[169] = "Пс 130-131; 2 Пар 24-25; Лк 19.1-27";
            maranata[170] = "Пс 132-133; 2 Пар 26-28; Лк 19.28-48";
            maranata[171] = "Пс 134; 2 Пар 29-30; Лк 20.1-19";
            maranata[172] = "Пс 135; 2 Пар 31-32; Лк 20.20-21.4";
            maranata[173] = "Пс 136-137; 2 Пар 33-34; Лк 21.5-38";
            maranata[174] = "Пс 138; 2 Пар 35-37; Лк 22.1-38";
            maranata[175] = "Пс 139-140; 1 Езд 1-6; Лк 22.39-65";
            maranata[176] = "Пс 141-142; 1 Езд 7-10; Лк 22.66-23.25";
            maranata[177] = "Пс 143; Неем 1-4; Лк 23.26-49";
            maranata[178] = "Пс 144-145; Неем 5-8; Лк 23.50-24.12";
            maranata[179] = "Пс 146-147; Неем 9-13; Лк 24.13-35";
            maranata[180] = "Пс 148; 2 Езд 1-4; Лк 24.36-53";
            maranata[181] = "Пс 149-151; 2 Езд 5-9; 1 Фес 1.1-2.16";
            maranata[182] = "Пс 1-2; 3 Езд 1-2; 1 Фес 2.17-3.13";
            maranata[183] = "Пс 3-4; 3 Езд 3.1-5.20; 1 Фес 4";
            maranata[184] = "Пс 5-6; 3 Езд 5.21-6.34; 1 Фес 5";
            maranata[185] = "Пс 7-8; 3 Езд 6.35-7.70; 2 Фес 1";
            maranata[186] = "Пс 9; 3 Езд 8.1-9.25; 2 Фес 2";
            maranata[187] = "Пс 10-11; 3 Езд 9.26-10.60; 2 Фес 3";
            maranata[188] = "Пс 12-13; 3 Езд 11-12; 1 Кор 1";
            maranata[189] = "Пс 14-15; 3 Езд 13; 1 Кор 2";
            maranata[190] = "Пс 16; 3 Езд 14; 1 Кор 3";
            maranata[191] = "Пс 17; 3 Езд 15; 1 Кор 4";
            maranata[192] = "Пс 18-19; 3 Езд 16; 1 Кор 5";
            maranata[193] = "Пс 20-21; Тов 1-5; 1 Кор 6";
            maranata[194] = "Пс 22-23; Тов 6-9; 1 Кор 7";
            maranata[195] = "Пс 24-25; Тов 10-14; 1 Кор 8";
            maranata[196] = "Пс 26-27; Иудифь 1-6; 1 Кор 9";
            maranata[197] = "Пс 28-29; Иудифь 7.1-10.10; 1 Кор 10.1-13";
            maranata[198] = "Пс 30; Иудифь 10.11-16.25; 1 Кор 10.14-11.1";
            maranata[199] = "Пс 31-32; Есф 1-5; 1 Кор 11.2-34";
            maranata[200] = "Пс 33; Есф 6-10; 1 Кор 12";
            maranata[201] = "Пс 34-35; Иов 1-3; 1 Кор 13";
            maranata[202] = "Пс 36; Иов 4-7; 1 Кор 14";
            maranata[203] = "Пс 37-38; Иов 8-10; 1 Кор 15.1-34";
            maranata[204] = "Пс 39; Иов 11-14; 1 Кор 15.35-58";
            maranata[205] = "Пс 40-41; Иов 15-21; 1 Кор 16";
            maranata[206] = "Пс 42-43; Иов 22-31; 2 Кор 1.1-2.4";
            maranata[207] = "Пс 44-45; Иов 32-37; 2 Кор 2.5-3.6";
            maranata[208] = "Пс 46-47; Иов 38-42; 2 Кор 3.7-4.18";
            maranata[209] = "Пс 48-49; Притч 1-3; 2 Кор 5.1-6.2";
            maranata[210] = "Пс 50-51; Притч 4-7; 2 Кор 6.3-7.1";
            maranata[211] = "Пс 52-53; Притч 8-9; 2 Кор 7.2-16";
            maranata[212] = "Пс 54; Притч 10-11; 2 Кор 8-9";
            maranata[213] = "Пс 55-56; Притч 12-15; 2 Кор 10";
            maranata[214] = "Пс 57-58; Притч 16-18; 2 Кор 11.1-15";
            maranata[215] = "Пс 59-60; Притч 19-21; 2 Кор 11.16-32";
            maranata[216] = "Пс 61-62; Притч 22-24; 2 Кор 12";
            maranata[217] = "Пс 63-64; Притч 25-26; 2 Кор 13";
            maranata[218] = "Пс 65-66; Притч 27-28; Рим 1.1-17";
            maranata[219] = "Пс 67; Притч 29-31; Рим 1.18-32";
            maranata[220] = "Пс 68; Еккл 1-5; Рим 2";
            maranata[221] = "Пс 69-70; Еккл 6-12; Рим 3";
            maranata[222] = "Пс 71; Песн 1-8; Рим 4";
            maranata[223] = "Пс 72; Прем 1-3; Рим 5.1-11";
            maranata[224] = "Пс 73-74; Прем 4-6; Рим 5.12-21";
            maranata[225] = "Пс 75-76; Прем 7-11; Рим 6.1-14";
            maranata[226] = "Пс 77; Прем 12-14; Рим 6.15-7.6";
            maranata[227] = "Пс 78-79; Прем 15-16; Рим 7.7-25";
            maranata[228] = "Пс 80-81; Прем 17-19; Рим 8.1-17";
            maranata[229] = "Пс 82; Сир 1.1-3.16; Рим 8.18-39";
            maranata[230] = "Пс 83-84; Сир 3.17-5.18; Рим 9.1-29";
            maranata[231] = "Пс 85-86; Сир 6-7; Рим 9.30-10.21";
            maranata[232] = "Пс 87; Сир 8-10; Рим 11.1-24";
            maranata[233] = "Пс 88; Сир 11-13; Рим 11.25-36";
            maranata[234] = "Пс 89; Сир 14-17; Рим 12";
            maranata[235] = "Пс 90; Сир 18-20; Рим 13";
            maranata[236] = "Пс 91-92; Сир 21-23; Рим 14.1-15.6";
            maranata[237] = "Пс 93-94; Сир 24-26; Рим 15.7-13";
            maranata[238] = "Пс 95-96; Сир 27-30; Рим 15.14-33";
            maranata[239] = "Пс 97-98; Сир 31-33; Рим 16";
            maranata[240] = "Пс 99-100; Сир 34-36; Гал 1";
            maranata[241] = "Пс 101; Сир 37-39; Гал 2";
            maranata[242] = "Пс 102; Сир 40-41; Гал 3.1-14";
            maranata[243] = "Пс 103; Сир 42-43; Гал 3.15-25";
            maranata[244] = "Пс 104; Сир 44-45; Гал 3.26-4.20";
            maranata[245] = "Пс 105; Сир 46-48; Гал 4.21-5.15";
            maranata[246] = "Пс 106; Сир 49-50; Гал 5.16-26";
            maranata[247] = "Пс 107; Сир 51; Гал 6";
            maranata[248] = "Пс 108; Ис 1-4; Еф 1.1-14";
            maranata[249] = "Пс 109-110; Ис 5-6; Еф 1.15-2.10";
            maranata[250] = "Пс 111-112; Ис 7-9; Еф 2.11-22";
            maranata[251] = "Пс 113; Ис 10-12; Еф 3.1-12";
            maranata[252] = "Пс 114-116; Ис 13-16; Еф 3.13-21";
            maranata[253] = "Пс 117; Ис 17-21; Еф 4.1-16";
            maranata[254] = "Пс 118; Ис 22-25; Еф 4.17-5.2";
            maranata[255] = "Пс 119-121; Ис 26-27; Еф 5.3-21";
            maranata[256] = "Пс 122-123; Ис 28-29; Еф 5.22-6.9";
            maranata[257] = "Пс 124-125; Ис 30-32; Еф 6.10-24";
            maranata[258] = "Пс 126-127; Ис 33-35; Флп 1";
            maranata[259] = "Пс 128-129; Ис 36-39; Флп 2.1-18";
            maranata[260] = "Пс 130-131; Ис 40-41; Флп 2.19-3.11";
            maranata[261] = "Пс 132-133; Ис 42-44; Флп 3.12-4.3";
            maranata[262] = "Пс 134; Ис 45-48; Флп 4.4-23";
            maranata[263] = "Пс 135; Ис 49-52; Кол 1.1-23";
            maranata[264] = "Пс 136-137; Ис 53-55; Кол 1.24-2.5";
            maranata[265] = "Пс 138; Ис 56-58; Кол 2.6-23";
            maranata[266] = "Пс 139-140; Ис 59-61; Кол 3.1-4.1";
            maranata[267] = "Пс 141-142; Ис 62-63; Кол 4.2-18";
            maranata[268] = "Пс 143; Ис 64-65; Флм";
            maranata[269] = "Пс 144-145; Ис 66; Евр 1";
            maranata[270] = "Пс 146-147; Иер 1-2; Евр 2";
            maranata[271] = "Пс 148; Иер 3-4; Евр 3";
            maranata[272] = "Пс 149-151; Иер 5-6; Евр 4.1-13";
            maranata[273] = "Пс 1-2; Иер 7-8; Евр 4.14-5.10";
            maranata[274] = "Пс 3-4; Иер 9-10; Евр 5.11-6.20";
            maranata[275] = "Пс 5-6; Иер 11-12; Евр 7";
            maranata[276] = "Пс 7-8; Иер 13-14; Евр 8";
            maranata[277] = "Пс 9; Иер 15-16; Евр 9.1-10";
            maranata[278] = "Пс 10-11; Иер 17-18; Евр 9.11-28";
            maranata[279] = "Пс 12-13; Иер 19-22; Евр 10.1-18";
            maranata[280] = "Пс 14-15; Иер 23-25; Евр 10.19-39";
            maranata[281] = "Пс 16; Иер 26-28; Евр 11.1-16";
            maranata[282] = "Пс 17; Иер 29-30; Евр 11.17-40";
            maranata[283] = "Пс 18-19; Иер 31-32; Евр 12.1-13";
            maranata[284] = "Пс 20-21; Иер 33; Евр 12.14-29";
            maranata[285] = "Пс 22-23; Иер 34-35; Евр 13";
            maranata[286] = "Пс 24-25; Иер 36-37; Тит 1";
            maranata[287] = "Пс 26-27; Иер 38-40; Тит 2";
            maranata[288] = "Пс 28-29; Иер 41-43; Тит 3";
            maranata[289] = "Пс 30; Иер 44-47; 1 Тим 1";
            maranata[290] = "Пс 31-32; Иер 48-49; 1 Тим 2";
            maranata[291] = "Пс 33; Иер 50-51; 1 Тим 3";
            maranata[292] = "Пс 34-35; Иер 52; 1 Тим 4";
            maranata[293] = "Пс 36; Посл Иер 1; 1 Тим 5";
            maranata[294] = "Пс 37-38; Плач 1-2; 1 Тим 6";
            maranata[295] = "Пс 39; Плач 3-5; 2 Тим 1";
            maranata[296] = "Пс 40-41; Вар 1-2; 2 Тим 2";
            maranata[297] = "Пс 42-43; Вар 3-5; 2 Тим 3";
            maranata[298] = "Пс 44-45; Иез 1-2; 2 Тим 4";
            maranata[299] = "Пс 46-47; Иез 3-4; Ин 1.1-18";
            maranata[300] = "Пс 48-49; Иез 5-7; Ин 1.19-51";
            maranata[301] = "Пс 50-51; Иез 8-10; Ин 2";
            maranata[302] = "Пс 52-53; Иез 11-12; Ин 3.1-21";
            maranata[303] = "Пс 54; Иез 13-15; Ин 3.22-36";
            maranata[304] = "Пс 55-56; Иез 16; Ин 4.1-26";
            maranata[305] = "Пс 57-58; Иез 17-19; Ин 4.27-54";
            maranata[306] = "Пс 59-60; Иез 20-21; Ин 5.1-30";
            maranata[307] = "Пс 61-62; Иез 22-23; Ин 5.31-47";
            maranata[308] = "Пс 63-64; Иез 24-26; Ин 6.1-24";
            maranata[309] = "Пс 65-66; Иез 27-28; Ин 6.25-59";
            maranata[310] = "Пс 67; Иез 29-30; Ин 6.60-71";
            maranata[311] = "Пс 68; Иез 31-32; Ин 7.1-24";
            maranata[312] = "Пс 69-70; Иез 33-34; Ин 7.25-8.11";
            maranata[313] = "Пс 71; Иез 35-36; Ин 8.12-30";
            maranata[314] = "Пс 72; Иез 37; Ин 8.31-47";
            maranata[315] = "Пс 73-74; Иез 38-39; Ин 8.48-59";
            maranata[316] = "Пс 75-76; Иез 40-42; Ин 9";
            maranata[317] = "Пс 77; Иез 43-44; Ин 10.1-21";
            maranata[318] = "Пс 78-79; Иез 45-46; Ин 10.22-42";
            maranata[319] = "Пс 80-81; Иез 47-48; Ин 11.1-16";
            maranata[320] = "Пс 82; Дан 1-2; Ин 11.17-57";
            maranata[321] = "Пс 83-84; Дан 3-4; Ин 12.1-19";
            maranata[322] = "Пс 85-86; Дан 5-6; Ин 12.20-50";
            maranata[323] = "Пс 87; Дан 7-8; Ин 13.1-30";
            maranata[324] = "Пс 88; Дан 9-10; Ин 13.31-14.14";
            maranata[325] = "Пс 89; Дан 11-12; Ин 14.15-31";
            maranata[326] = "Пс 90; Дан 13-14; Ин 15.1-17";
            maranata[327] = "Пс 91-92; Ос 1-3; Ин 15.18-16.16";
            maranata[328] = "Пс 93-94; Ос 4-7; Ин 16.17-33";
            maranata[329] = "Пс 95-96; Ос 8-10; Ин 17";
            maranata[330] = "Пс 97-98; Ос 11-14; Ин 18.1-27";
            maranata[331] = "Пс 99-100; Иоил 1-3; Ин 18.28-19.16";
            maranata[332] = "Пс 101; Ам 1-4; Ин 19.17-42";
            maranata[333] = "Пс 102; Ам 5-9; Ин 20.1-18";
            maranata[334] = "Пс 103; Авд; Ин 20.19-31";
            maranata[335] = "Пс 104; Иона 1-4; Ин 21";
            maranata[336] = "Пс 105; Мих 1-3; 1 Ин 1.1-2.14";
            maranata[337] = "Пс 106; Мих 4-5; 1 Ин 2.15-3.10";
            maranata[338] = "Пс 107; Мих 6-7; 1 Ин 3.11-24";
            maranata[339] = "Пс 108; Наум 1-3; 1 Ин 4";
            maranata[340] = "Пс 109-110; Авв 1-3; 1 Ин 5";
            maranata[341] = "Пс 111-112; Соф 1-3; 2 Ин 1";
            maranata[342] = "Пс 113; Агг 1-2; 3 Ин 1";
            maranata[343] = "Пс 114-116; Зах 1-3; Откр 1";
            maranata[344] = "Пс 117; Зах 4-6; Откр 2.1-17";
            maranata[345] = "Пс 118; Зах 7-8; Откр 2.18-3.6";
            maranata[346] = "Пс 119-121; Зах 9-11; Откр 3.7-22";
            maranata[347] = "Пс 122-123; Зах 12-14; Откр 4";
            maranata[348] = "Пс 124-125; Мал 1-2; Откр 5";
            maranata[349] = "Пс 126-127; Мал 3-4; Откр 6";
            maranata[350] = "Пс 128-129; 1 Мак 1-2; Откр 7";
            maranata[351] = "Пс 130-131; 1 Мак 3-4; Откр 8";
            maranata[352] = "Пс 132-133; 1 Мак 5-6; Откр 9";
            maranata[353] = "Пс 134; 1 Мак 7-8; Откр 10";
            maranata[354] = "Пс 135; 1 Мак 9-10; Откр 11";
            maranata[355] = "Пс 136-137; 1 Мак 11-13; Откр 12";
            maranata[356] = "Пс 138; 1 Мак 14-16; Откр 13";
            maranata[357] = "Пс 139; 2 Мак 1-2; Откр 14";
            maranata[358] = "Пс 140-141; 2 Мак 3-4; Откр 15";
            maranata[359] = "Пс 142; 2 Мак 5-6; Откр 16";
            maranata[360] = "Пс 143; 2 Мак 7-8; Откр 17";
            maranata[361] = "Пс 144; 2 Мак 9-10; Откр 18";
            maranata[362] = "Пс 145-146; 2 Мак 11-12; Откр 19";
            maranata[363] = "Пс 147; 2 Мак 13-15; Откр 20";
            maranata[364] = "Пс 148; 3 Мак 1-3; Откр 21";
            maranata[365] = "Пс 149-151; 3 Мак 4-7; Откр 22";

            QString cytanneMaranaty;
            QDate gregorianCalendar = QDate::currentDate();
            if (gregorianCalendar.isLeapYear(year)) {
                cytanneMaranaty = maranata[pageNumber];
            } else {
                if (pageNumber < 59) {
                    if (pageNumber == 58) cytanneMaranaty = maranata[58] + "; " + maranata[59];
                    else cytanneMaranaty = maranata[pageNumber];
                } else {
                    int page = pageNumber + 1;
                    if (page == 60) cytanneMaranaty = maranata[60] + "; " + maranata[59];
                    else cytanneMaranaty = maranata[page];
                }
            }
            return cytanneMaranaty;
        }

    void CreateCalindar::gratePamiatekaVernikau(int year) {
            QString data = "";
            int dataP;
            int monthP;
            int a = year % 19;
            int b = year % 4;
            int cx = year % 7;
            int ks = year / 100;
            int p = (13 + 8 * ks) / 25;
            int q = ks / 4;
            int m = (15 - p + ks - q) % 30;
            int n = (4 + ks - q) % 7;
            int d = (19 * a + m) % 30;
            int ex = (2 * b + 4 * cx + 6 * d + n) % 7;
            if (d + ex <= 9) {
                dataP = d + ex + 22;
                monthP = CreateCalindar::MARCH;
            } else {
                dataP = d + ex - 9;
                if (d == 29 && ex == 6) dataP = 19;
                if (d == 28 && ex == 6) dataP = 18;
                monthP = CreateCalindar::APRIL;
            }
            QString monthName[] = {"", "студзеня", "лютага", "сакавіка", "красавіка", "траўня", "чэрвеня", "ліпеня", "жніўня", "верасьня", "кастрычніка", "лістапада", "сьнежня"};
            QDate calendar(year, monthP, dataP);
            int pashaD = calendar.day();
            int pashaM = calendar.month();
            int erusalimD = calendar.addDays(-7).day();
            int erusalimM = calendar.addDays(-7).month();
            int uznasenneD = calendar.addDays(-7 + 46).day();
            int uznasenneM = calendar.addDays(-7 + 46).month();
            int troicaD = calendar.addDays(-7 + 46 + 10).day();
            int troicaM = calendar.addDays(-7 + 46 + 10).month();
            calendar.setDate(year, monthP, dataP);
            int postMytnikND = calendar.addDays(-70).day();
            int postMytnikNM = calendar.addDays(-70).month();
            int postMytnikKD = calendar.addDays(-70 + 7).day();
            int postMytnikKM = calendar.addDays(-70 + 7).month();
            calendar.setDate(year, monthP, dataP);
            int nopostSvetluKD = calendar.addDays(7).day();
            int nopostSvetluKM = calendar.addDays(7).month();
            calendar.setDate(year, monthP, dataP);
            int nopostTroicaND = calendar.addDays(49).day();
            int nopostTroicaNM = calendar.addDays(49).month();
            int nopostTroicaKD = calendar.addDays(49 + 7).day();
            int nopostTroicaKM = calendar.addDays(49 + 7).month();
            calendar.setDate(year, monthP, dataP);
            int postPetrKD = calendar.addDays(57).day();
            int postPetrKM = calendar.addDays(57).month();
            calendar.setDate(year, monthP, dataP);
            int postVialikiND = calendar.addDays(-48).day();
            int postVialikiNM = calendar.addDays(-48).month();
            calendar.setDate(year, monthP, dataP);
            int postVialikiKD = calendar.addDays(-1).day();
            int postVialikiKM = calendar.addDays(-1).month();
            int postVialikaiPiatKD = calendar.addDays(-1 + -1).day();
            int postVialikaiPiatKM = calendar.addDays(-1 + -1).month();
            data.append("<!DOCTYPE HTML><font color=\"#d00505\"><strong>ЕЎХАРЫСТЫЧНЫ ПОСТ ПЕРАД СЬВЯТЫМ ПРЫЧАСЬЦЕМ</strong></font>\n");
            data.append("<em>Ня менш за 1 гадзiну перад пачаткам Боскай Літургіі трэба ўстрымацца ад ежы i напояў.</em>\n");
            data.append("Чыстая вада, а таксама прыём прыпісаных лекаў не забараняецца.\n");
            data.append("<font color=\"#d00505\"><strong>АДЗНАЧЭНЬНЕ СЬВЯТАЎ</strong></font>\n");
            data.append("Згодна з кан. 880 Кодэксу Канонаў Усходніх Цэркваў вернікі Беларускай Грэка-Каталіцкай Царквы абавязаны сьвяткаваць, акрамя <strong>кожнай нядзелі</strong>, наступныя царкоўныя сьвяты:\n");
            data.append("<strong>1.</strong> <em>Сьвяты, якія заўсёды ў нядзелю:</em>\n");
            data.append("<strong>- Уваход Гасподні ў Ерусалім (Вербніца) ").append(QString::number(erusalimD)).append(" ").append(monthName[erusalimM]).append(";</strong>\n");
            data.append("<strong>- Уваскрасеньне Хрыстова (Вялiкдзень) ").append(QString::number(pashaD)).append(" ").append(monthName[pashaM]).append(";</strong>\n");
            data.append("<strong>- Зыход Сьвятога Духа (Тройца) – ").append(QString::number(troicaD)).append(" ").append(monthName[troicaM]).append(";</strong>\n");
            data.append("<strong>2. Богазьяўленьне (Вадохрышча) – 6 студзеня;</strong>\n");
            data.append("<strong>3. Дабравешчаньне Найсьвяцейшай Багародзiцы – 25 сакавіка;</strong>\n");
            data.append("<strong>4. Узьнясеньне Гасподняе (Ушэсьце) – ").append(QString::number(uznasenneD)).append(" ").append(monthName[uznasenneM]).append(";</strong>\n");
            data.append("<strong>5. Сьвята Вярхоўных Апосталаў Пятра і Паўла – 29 чэрвеня;</strong>\n");
            data.append("<strong>6. Усьпеньне Найсьвяцейшай Багародзiцы – 15 жніўня;</strong>\n");
            data.append("<strong>7. Нараджэньне Хрыстова (Раство) – 25 сьнежня.</strong>\n");
            data.append("У гэтыя царкоўныя сьвяты і ў нядзелі вернiкi <strong>абавязаны браць удзел у сьв. Лiтургii</strong> i ўстрымлівацца ад цяжкай фiзiчнай працы.\n");
            data.append("Ва ўсе iншыя сьвяты сьвятары адпраўляюць сьв. Лiтургiю для тых, якiя змогуць i пажадаюць сьвяткаваць. Аднак Царква таксама асабліва заахвочвае вернікаў браць удзел у набажэнствах наступных сьвятаў:\n<strong>• Абрэзаньне Гасподняе</strong>, <em>1 студзеня</em>;\n<strong>• Перамяненьне Гасподняе</strong>, <em>6 жніўня</em>;\n<strong>• Нараджэньне Найсьвяцейшай Багародзіцы</strong>, <em>8 верасьня</em>;\n<strong>• Узвышэньне Пачэснага Крыжа Гасподняга (Крыжаўзвышэньне)</strong>, <em>14 верасьня</em>.\n");
            data.append("<font color=\"#d00505\"><strong>АБАВЯЗКОВЫЯ ПАСТЫ</strong></font>\n");
            data.append("• <em><strong>Усе пятнiцы</strong> на працягу году вернікі БГКЦ абавязаны ўстрымлiвацца ад мясных страваў.\n");
            data.append("Посту ў пятніцу няма ў сьвяты Гасподнiя i Багародзiчныя, а таксама ў перыяд:</em>\n");
            data.append("- ад Раства (25 сьнежня) да Богазьяўленьня (6 студзеня);\n");
            data.append("- ад Нядзелi мытнiка i фарысея (").append(QString::number(postMytnikND)).append(" ").append(monthName[postMytnikNM]).append(") да Нядзелi блуднага сына (").append(QString::number(postMytnikKD)).append(" ").append(monthName[postMytnikKM]).append(");\n");
            data.append("- ад Вялiкадня (").append(QString::number(pashaD)).append(" ").append(monthName[pashaM]).append(") да Нядзелi Тамаша (").append(QString::number(nopostSvetluKD)).append(" ").append(monthName[nopostSvetluKM]).append(");\n");
            data.append("- ад Тройцы (").append(QString::number(nopostTroicaND)).append(" ").append(monthName[nopostTroicaNM]).append(") да Нядзелi ўсiх сьвятых (").append(QString::number(nopostTroicaKD)).append(" ").append(monthName[nopostTroicaKM]).append(").\n");
            data.append("<em>• Асаблівы час, калі вернікі прыкладаюць узмоцненыя намаганьні для свайго духоўнага росту, абмяжоўваюць сябе ў ежы, а таксама ўстрымліваюцца ад арганiзацыi публiчных забаў з музыкай i танцамi:</em>\n");
            data.append("<strong>- Вялiкi пост і Вялікі тыдзень:</strong><em> ").append(QString::number(postVialikiND)).append(" ").append(monthName[postVialikiNM]).append(" – ").append(QString::number(postVialikiKD)).append(" ").append(monthName[postVialikiKM]).append(";</em>\n");
            data.append("<strong>- Пятроўскі пост:</strong><em> ").append(QString::number(postPetrKD)).append(" ").append(monthName[postPetrKM]).append(" - 28 чэрвеня;</em>\n");
            data.append("<strong>- Усьпенскі пост:</strong><em> 1 жніўня - 14 жніўня;</em>\n");
            data.append("<strong>- Калядны пост (Пiлiпаўка):</strong><em> 15 лістапада – 24 сьнежня.</em>\n");
            data.append("<strong>Грэка-католiкi абавязаны:</strong>\n");
            data.append("• <em>Устрымлiвацца ад мясных i малочных страваў:</em>\n");
            data.append("- у першы дзень Вялiкага посту (").append(QString::number(postVialikiND)).append(" ").append(monthName[postVialikiNM]).append(");\n");
            data.append("- у Вялiкую пятнiцу (").append(QString::number(postVialikaiPiatKD)).append(" ").append(monthName[postVialikaiPiatKM]).append(");\n");
            data.append("• <em>Устрымлiвацца ад мясных страваў i абмяжоўвацца адным пасілкам у дзень:</em>\n");
            data.append("- у Сьвяты вечар перад Раством (24 сьнежня);\n");
            data.append("- у Сьвяты вечар перад Богазьяўленьнем (5 студзеня);\n");
            data.append("- на Ўзвышэньне сьв. Крыжа (14 верасьня);\n");
            data.append("- на Адсячэньне галавы сьв. Яна Хрысьцiцеля (29 жніўня).\n");
            data.append("<font color=\"#d00505\"><strong>АД ПОСТУ ЗВОЛЬНЕНЫЯ:</strong></font>\n");
            data.append("- дзецi да 14 гадоў i тыя, чый узрост больш за 60 гадоў;\n");
            data.append("- хворыя фiзiчна i душэўна, цяжарныя жанчыны, а таксама тыя, што кормяць грудзьмi;\n");
            data.append("- тыя, што выздараўлiваюць пасьля цяжкай хваробы;\n");
            data.append("- тыя, што не распараджаюцца сабой у поўнай меры (напрыклад, тыя, што жывуць у чужых; зьнябожаныя; тыя, што жывуць з ахвяраваньня i г. д.)\n");
            data.append("Таксама бiскуп i парахi могуць звольнiць верніка ад посту дзеля нейкiх важкiх прычынаў. Спаведнiк можа гэта зрабiць у спавядальнi.");

            QString saveFileName = malitounikPatch + "/malitounik-bgkc/src/main/res/raw/pamiatka.html";
            QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
            QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
            QFile file(saveFileName);
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(data.toUtf8());
                file.close();   // Закрываем файл
            }
        }

        QString CreateCalindar::sviatyPKC(int DayYear, int year) {
            ++DayYear;
            QString sabytiePKC = "";
            int a = year % 19;
            int b = year % 4;
            int cx = year % 7;
            int k = (year / 100);
            int p = (13 + 8 * k) / 25;
            int q = (k / 4);
            int m = (15 - p + k - q) % 30;
            int n = (4 + k - q) % 7;
            int d = (19 * a + m) % 30;
            int ex = (2 * b + 4 * cx + 6 * d + n) % 7;
            int month_p;
            int data_p;
            if (d + ex <= 9) {
                data_p = d + ex + 22;
                month_p = CreateCalindar::MARCH;
            } else {
                data_p = d + ex - 9;
                if (d == 29 && ex == 6) data_p = 19;
                if (d == 28 && ex == 6) data_p = 18;
                month_p = CreateCalindar::APRIL;
            }
            QDate pkc(year, CreateCalindar::JANUARY, 1);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Сьвятой Багародзіцы Марыі\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::JANUARY, 6);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Аб’яўленьне Пана (Тры Каралі)\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::JANUARY, 7);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Хрост Пана\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::FEBRUARY, 2);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Ахвяраваньне Пана\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::MARCH, 19);
            int uzaf = 0;
            if (pkc.dayOfWeek() == CreateCalindar::SUNDAY) {
                uzaf = 1;
            }
            if (pkc.addDays(uzaf).dayOfYear() == DayYear) {
                sabytiePKC = "Сьвятога Юзафа\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::JUNE, 29);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Сьвятых апосталаў Пятра і Паўла\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::JULY, 2);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Найсьвяцейшай Панны Марыі Будслаўскай\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::AUGUST, 6);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Перамяненьне Пана\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::AUGUST, 15);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Унебаўзяцьце Найсьвяцейшай Панны Марыі\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::SEPTEMBER, 8);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Нараджэньне Найсьвяцейшай Панны Марыі\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::SEPTEMBER, 14);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Узвышэньня Сьвятога Крыжа\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::SEPTEMBER, 29);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Сьвятых Арханёлаў\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::NOVEMBER, 1);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Усіх Сьвятых\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::NOVEMBER, 2);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Успамін усіх памерлых вернікаў\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::DECEMBER, 8);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Беззаганнага Зачацьця Найсьвяцейшай Панны Марыі\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::DECEMBER, 25);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Нараджэньне Пана\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, month_p, data_p);
            if (pkc.addDays(-46).dayOfYear() == DayYear) {
                sabytiePKC = "Папялец (пачатак Вялікага посту)\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, month_p, data_p);
            int nachPalNed = pkc.addDays(-7).dayOfYear();
            int konPalNed = pkc.addDays(-7 + 14).dayOfYear();
            pkc.setDate(year, CreateCalindar::MARCH, 25);
            bool perenos = false;
            for (int i = nachPalNed; i < konPalNed; i++) {
                if (i == pkc.dayOfYear()) {
                    perenos = true;
                }
            }
            if (perenos) {
                if (konPalNed + 1 == DayYear) {
                    sabytiePKC = "Зьвеставаньне Пана\n(паводле календара РКЦ)";
                }
            } else {
                if (pkc.dayOfYear() == DayYear) {
                    sabytiePKC = "Зьвеставаньне Пана\n(паводле календара РКЦ)";
                }
            }
            if (nachPalNed == DayYear) {
                sabytiePKC = "Пальмовая нядзеля\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, month_p, data_p);
            if (pkc.dayOfYear() == DayYear) {
                sabytiePKC = "Уваскрасеньне Пана (Вялікдзень)\n(паводле календара РКЦ)";
            }
            if (konPalNed == DayYear) {
                sabytiePKC = "Божай Міласэрнасьці\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, month_p, data_p);
            if (pkc.addDays(39).dayOfYear() == DayYear) {
                sabytiePKC = "Унебаўшэсьце Пана\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, month_p, data_p);
            if (pkc.addDays(49).dayOfYear() == DayYear) {
                sabytiePKC = "Спасланьне Духа Сьвятога\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, month_p, data_p);
            if (pkc.addDays(60).dayOfYear() == DayYear) {
                sabytiePKC = "Найсьвяцейшага Цела і Крыві Хрыста (Божага Цела)\n(паводле календара РКЦ)";
            }
            if (pkc.addDays(60 + 8).dayOfYear() == DayYear) {
                sabytiePKC = "Найсьвяцейшага Сэрца Езуса\n(паводле календара РКЦ)";
            }

            int add = 0;
            if (pkc.addDays(60 + 8).dayOfWeek() == CreateCalindar::FRIDAY && pkc.addDays(60 + 8).month() == CreateCalindar::JUNE && pkc.addDays(60 + 8).day() == 24) {
                add = -1;
            }
            pkc.setDate(year, CreateCalindar::JUNE, 24);
            if (pkc.addDays(add).dayOfYear() == DayYear) {
                sabytiePKC = "Нараджэньне сьв. Яна Хрысьціцеля\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, month_p, data_p);
            if (pkc.addDays(56).dayOfYear() == DayYear) {
                sabytiePKC = "Найсьвяцейшай Тройцы\n(паводле календара РКЦ)";
            }
            pkc.setDate(year, CreateCalindar::DECEMBER, 25);
            int count = 0;
            int dayToAdvent = 0;
            for (int i = 50; i > 0; i--) {
                if (count == 4) {
                    if (pkc.addDays(dayToAdvent).dayOfYear() == DayYear && pkc.addDays(dayToAdvent).dayOfWeek() == CreateCalindar::SUNDAY) {
                        sabytiePKC = "1-ая нядзеля Адвэнту\n(паводле календара РКЦ)";
                        break;
                    }
                }
                dayToAdvent--;
                if (pkc.addDays(dayToAdvent).dayOfWeek() == CreateCalindar::SUNDAY) count++;
            }
            pkc.setDate(year, CreateCalindar::DECEMBER, 25);
            int count2 = 0;
            dayToAdvent = 0;
            for (int i = 50; i > 0; i--) {
                if (count2 == 5) {
                    if (pkc.addDays(dayToAdvent).dayOfYear() == DayYear && pkc.addDays(dayToAdvent).dayOfWeek() == CreateCalindar::SUNDAY) {
                        sabytiePKC = "Хрыста — Валадара Сусьвету\n(паводле календара РКЦ)";
                        break;
                    }
                }
                dayToAdvent--;
                if (pkc.addDays(dayToAdvent).dayOfWeek() == CreateCalindar::SUNDAY) count2++;
            }
            pkc.setDate(year, CreateCalindar::DECEMBER, 25);
            if (pkc.dayOfWeek() == CreateCalindar::SUNDAY) {
                if (pkc.addDays(5).dayOfYear() == DayYear) {
                    sabytiePKC = "Сьвятой Сям’і\n(паводле календара РКЦ)";
                }
            } else {
                pkc.setDate(year, CreateCalindar::DECEMBER, 26);
                dayToAdvent = 0;
                for (int i = 0; i < 6; i++) {
                    if (pkc.addDays(dayToAdvent).dayOfWeek() == CreateCalindar::SUNDAY) {
                        if (pkc.addDays(dayToAdvent).dayOfYear() == DayYear) {
                            sabytiePKC = "Сьвятой Сям’і\n(паводле календара РКЦ)";
                            break;
                        }
                    }
                    dayToAdvent++;
                }
            }
            return sabytiePKC;
        }

        //Вялікдзень паводле юльянскага календара
        QString CreateCalindar::pascha_pravas(int DayYear, int year) {
            ++DayYear;
            int data_p, month_p;
            int a = (19 * (year % 19) + 15) % 30;
            int b = (2 * (year % 4) + 4 * (year % 7) + 6 * a + 6) % 7;
            if (a + b > 9) {
                data_p = a + b - 9;
                month_p = CreateCalindar::APRIL;
            } else {
                data_p = 22 + a + b;
                month_p = CreateCalindar::MARCH;
            }
            QDate pravas(year, month_p, data_p);
            //Праваслаўныя сьвяты
            if (pravas.addDays(13).dayOfYear() == DayYear)
                return "Пасха Хрыстова\n(паводле юльянскага календара)";
            if (pravas.addDays(13 + -7).dayOfYear() == DayYear)
                return "Вербная нядзеля\n(паводле юльянскага календара)";
            if (pravas.addDays(13 + -7 + 46).dayOfYear() == DayYear)
                return "Узьнясеньне Гасподняе\n(паводле юльянскага календара)";
            if (pravas.addDays(13 + -7 + 46 + 10).dayOfYear() == DayYear)
                return "Зыход Сьвятога Духа\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::JANUARY, 19);
            if (pravas.dayOfYear() == DayYear)
                return "Богазьяўленьне\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::FEBRUARY, 15);
            if (pravas.dayOfYear() == DayYear)
                return "Сустрэча Госпада (Грамніцы)\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::APRIL, 7);
            if (pravas.dayOfYear() == DayYear)
                return "Дабравешчаньне\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::AUGUST, 19);
            if (pravas.dayOfYear() == DayYear)
                return "Перамяненьне Гасподняе\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::AUGUST, 28);
            if (pravas.dayOfYear() == DayYear)
                return "Усьпеньне Багародзіцы\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::SEPTEMBER, 21);
            if (pravas.dayOfYear() == DayYear)
                return "Нараджэньне Багародзіцы\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::SEPTEMBER, 27);
            if (pravas.dayOfYear() == DayYear)
                return "Крыжаўзвышэньне\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::DECEMBER, 4);
            if (pravas.dayOfYear() == DayYear)
                return "Уваход у Храм Багародзіцы\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::JANUARY, 7);
            if (pravas.dayOfYear() == DayYear)
                return "Нараджэньне Хрыстова\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::JANUARY, 14);
            if (pravas.dayOfYear() == DayYear)
                return "Абрэзаньне Гасподняе\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::JULY, 7);
            if (pravas.dayOfYear() == DayYear)
                return "Нараджэньне сьв. Яна Хрысьціцеля\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::JULY, 12);
            if (pravas.dayOfYear() == DayYear)
                return "Вярхоўных ап. Пятра і Паўла\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::SEPTEMBER, 11);
            if (pravas.dayOfYear() == DayYear)
                return "Адсячэньне галавы\nсьв. Яна Хрысьціцеля\n(паводле юльянскага календара)";
            pravas.setDate(year, CreateCalindar::OCTOBER, 14);
            if (pravas.dayOfYear() == DayYear)
                return "Покрыва Багародзіцы\n(паводле юльянскага календара)";
            return "";
        }

        // Дзяржаўныя сьвяты ў Беларусі
        QString CreateCalindar::gosudarstvo(int DayYear, int year) {
            ++DayYear;
            int data_p, month_p;
            int a = (19 * (year % 19) + 15) % 30;
            int b = (2 * (year % 4) + 4 * (year % 7) + 6 * a + 6) % 7;
            if (a + b > 9) {
                data_p = a + b - 9;
                month_p = CreateCalindar::APRIL;
            } else {
                data_p = 22 + a + b;
                month_p = CreateCalindar::MARCH;
            }
            QDate gosud(year, CreateCalindar::JANUARY, 1);
            if (gosud.dayOfYear() == DayYear) return "Новы год (непрац.)";
            if (gosud.addDays(1).dayOfYear() == DayYear) return "Новы год (непрац.)";
            gosud.setDate(year, CreateCalindar::JANUARY, 7);
            if (gosud.dayOfYear() == DayYear)
                return "Раство Хрыстова\n(паводле календара праваслаўнай канфесіі) (непрац.)";
            gosud.setDate(year, CreateCalindar::MARCH, 8);
            if (gosud.dayOfYear() == DayYear) return "Дзень жанчынаў (непрац.)";
            gosud.setDate(year, month_p, data_p);
            if (gosud.addDays(22).dayOfYear() == DayYear)
                return "Радаўніца\n(паводле календара праваслаўнай канфесіі) (непрац.)";
            gosud.setDate(year, CreateCalindar::MAY, 1);
            if (gosud.dayOfYear() == DayYear) return "Сьвята працы (непрац.)";
            gosud.setDate(year, CreateCalindar::MAY, 9);
            if (gosud.dayOfYear() == DayYear) return "Дзень Перамогі (непрац.)";
            gosud.setDate(year, CreateCalindar::JULY, 3);
            if (gosud.dayOfYear() == DayYear)
                return "Дзень Незалежнасьці Рэспублікі Беларусь (Дзень Рэспублікі) (непрац.)";
            gosud.setDate(year, CreateCalindar::NOVEMBER, 7);
            if (gosud.dayOfYear() == DayYear)
                return "Дзень Кастрычніцкай рэвалюцыі (непрац.)";
            gosud.setDate(year, CreateCalindar::DECEMBER, 25);
            if (gosud.dayOfYear() == DayYear)
                return "Раство Хрыстова\n(паводле календара каталіцкай канфесіі) (непрац.)";
            return "";
        }

        QString CreateCalindar::gosudarstvoRab(int DayYear, int year) {
            ++DayYear;
            int data_p, month_p, data_p2, month_p2;
            int a = year % 19;
            int b = year % 4;
            int cx = year % 7;
            int k = (year / 100);
            int p = (13 + 8 * k) / 25;
            int q = (k / 4);
            int m = (15 - p + k - q) % 30;
            int n = (4 + k - q) % 7;
            int d = (19 * a + m) % 30;
            int ex = (2 * b + 4 * cx + 6 * d + n) % 7;
            if (d + ex <= 9) {
                data_p = d + ex + 22;
                month_p = CreateCalindar::MARCH;
            } else {
                data_p = d + ex - 9;
                if (d == 29 && ex == 6) data_p = 19;
                if (d == 28 && ex == 6) data_p = 18;
                month_p = CreateCalindar::APRIL;
            }
            int a2 = (19 * (year % 19) + 15) % 30;
            int b2 = (2 * (year % 4) + 4 * (year % 7) + 6 * a2 + 6) % 7;
            if (a2 + b2 > 9) {
                data_p2 = a2 + b2 - 9;
                month_p2 = CreateCalindar::APRIL;
            } else {
                data_p2 = 22 + a2 + b2;
                month_p2 = CreateCalindar::MARCH;
            }
            QDate gosud(year, CreateCalindar::MARCH, 15);
            if (gosud.dayOfYear() == DayYear)
                return "Дзень Канстытуцыі Рэспублікі Беларусь";
            gosud.setDate(year, CreateCalindar::APRIL, 2);
            if (gosud.dayOfYear() == DayYear)
                return "Дзень яднаньня народаў Беларусі і Расеі";
            // другая нядзеля траўня
            int may[] = {8, 9, 10, 11, 12, 13, 14};
            for (int aMay : may) {
                gosud.setDate(year, CreateCalindar::MAY, aMay);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        return "Дзень Дзяржаўнага герба Рэспублікі Беларусь і Дзяржаўнага сьцяга Рэспублікі Беларусь";
                }
            }
            gosud.setDate(year, CreateCalindar::FEBRUARY, 23);
            if (gosud.dayOfYear() == DayYear)
                return "Дзень абаронцаў Айчыны і Ўзброеных Сілаў Рэспублікі Беларусь";
            gosud.setDate(year, month_p, data_p);
            if (gosud.dayOfYear() == DayYear) return "Вялікдзень (паводле календара каталіцкай канфесіі)";
            gosud.setDate(year, month_p2, data_p2);
            if (gosud.addDays(13).dayOfYear() == DayYear) return "Вялікдзень (паводле календара праваслаўнай канфесіі)";
            gosud.setDate(year, CreateCalindar::SEPTEMBER, 17);
            if (gosud.dayOfYear() == DayYear) return "Дзень народнага адзінства";
            gosud.setDate(year, CreateCalindar::NOVEMBER, 2);
            if (gosud.dayOfYear() == DayYear) return "Дзень памяці";
            gosud.setDate(year, CreateCalindar::FEBRUARY, 15);
            if (gosud.dayOfYear() == DayYear)
                return "Дзень памяці воінаў-інтэрнацыяналістаў";
            gosud.setDate(year, CreateCalindar::APRIL, 26);
            if (gosud.dayOfYear() == DayYear) return "Дзень чарнобыльскай трагедыі";
            gosud.setDate(year, CreateCalindar::JUNE, 22);
            if (gosud.dayOfYear() == DayYear)
                return "Дзень усенароднай памяці ахвяраў Вялікай Айчыннай вайны";
            return "";
        }

        QString CreateCalindar::profesional(int DayYear, int year) {
            ++DayYear;
            QString result = "";
            int may1[] = {1, 2, 3, 4, 5, 6, 7}; // 1 тыдзень
            int may2[] = {8, 9, 10, 11, 12, 13, 14}; // 2 тыдзень
            int may3[] = {15, 16, 17, 18, 19, 20, 21}; // 3 тыдзень
            int may4[] = {22, 23, 24, 25, 26, 27, 28}; // 4 тыдзень
            int may5[] = {24, 25, 26, 27, 28, 29, 30}; // Апошні тыдзень
            int may6[] = {25, 26, 27, 28, 29, 30, 31}; // Апошні тыдзень
            QDate gosud(year, CreateCalindar::JANUARY, 5);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работнікаў сацыяльнай абароны\n");
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::JANUARY, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень банкаўскіх і фінансавых работнікаў\n");
                }
            }
            gosud.setDate(year, CreateCalindar::JANUARY, 19);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень выратавальніка\n");
            for (int aMay6 : may6) {
                gosud.setDate(year, CreateCalindar::JANUARY, aMay6);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень беларускай навукі\n");
                }
            }
            gosud.setDate(year, CreateCalindar::FEBRUARY, 21);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работнікаў землеўпарадкавальнай і картографа-геадэзічнай службы\n");
            gosud.setDate(year, CreateCalindar::MARCH, 4);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень міліцыі\n");
            gosud.setDate(year, CreateCalindar::MARCH, 18);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень унутраных войскаў\n");
            gosud.setDate(year, CreateCalindar::MARCH, 23);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работнікаў гідраметэаралагічнай службы\n");
            for (int aMay4 : may4) {
                gosud.setDate(year, CreateCalindar::MARCH, aMay4);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў бытавога абслугоўваньня насельніцтва і жыльлёва-камунальнай гаспадаркі\n");
                }
            }
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::APRIL, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень геолага\n");
                }
            }
            gosud.setDate(year, CreateCalindar::APRIL, 22);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень судовага эксьперта\n");

            gosud.setDate(year, CreateCalindar::MAY, 5);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень друку\n");
            gosud.setDate(year, CreateCalindar::MAY, 7);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работнікаў радыё, тэлебачаньня і сувязі\n");
            for (int aMay3 : may3) {
                gosud.setDate(year, CreateCalindar::MAY, aMay3);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SATURDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў фізічнай культуры і спорту\n");
                }
            }
            gosud.setDate(year, CreateCalindar::MAY, 28);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень памежніка\n");
            for (int aMay6 : may6) {
                gosud.setDate(year, CreateCalindar::MAY, aMay6);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень хіміка\n");
                }
            }
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::JUNE, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень меліяратара\n");
                }
            }
            for (int aMay2 : may2) {
                gosud.setDate(year, CreateCalindar::JUNE, aMay2);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў лёгкай прамысловасьці\n");
                }
            }
            for (int aMay3 : may3) {
                gosud.setDate(year, CreateCalindar::JUNE, aMay3);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень медычных работнікаў\n");
                }
            }
            gosud.setDate(year, CreateCalindar::JUNE, 26);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работнікаў пракуратуры\n");
            for (int aMay6 : may5) {
                gosud.setDate(year, CreateCalindar::JUNE, aMay6);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SATURDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень вынаходніка і рацыяналізатара\n");
                }
            }
            gosud.setDate(year, CreateCalindar::JUNE, 30);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень эканаміста\n");
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::JULY, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SATURDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень кааперацыі\n");
                }
            }
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::JULY, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў воднага транспарту\n");
                }
            }
            for (int aMay2 : may2) {
                gosud.setDate(year, CreateCalindar::JULY, aMay2);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў падатковых органаў\n");
                }
            }
            for (int aMay3 : may3) {
                gosud.setDate(year, CreateCalindar::JULY, aMay3);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень металурга\n");
                }
            }
            gosud.setDate(year, CreateCalindar::JULY, 25);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень пажарнай службы\n");

            for (int aMay6 : may6) {
                gosud.setDate(year, CreateCalindar::JULY, aMay6);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў гандлю\n");
                }
            }
            gosud.setDate(year, CreateCalindar::AUGUST, 2);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень дэсантнікаў і сіл сьпецыяльных аперацыяў\n");
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::AUGUST, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень чыгуначніка\n");
                }
            }
            for (int aMay2 : may2) {
                gosud.setDate(year, CreateCalindar::AUGUST, aMay2);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень будаўніка\n");
                }
            }
            for (int aMay3 : may3) {
                gosud.setDate(year, CreateCalindar::AUGUST, aMay3);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень Ваенна-паветраных сілаў\n");
                }
            }
            for (int aMay6 : may6) {
                gosud.setDate(year, CreateCalindar::AUGUST, aMay6);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень шахцёра\n");
                }
            }
            gosud.setDate(year, CreateCalindar::AUGUST, 23);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работнікаў дзяржаўнай статыстыкі\n");
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::SEPTEMBER, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў газавай, нафтавай і паліўнай прамысловасьці\n");
                }
            }
            gosud.setDate(year, CreateCalindar::SEPTEMBER, 12);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень супрацоўніка органаў папярэдняга сьледзтва\n");
            for (int aMay2 : may2) {
                gosud.setDate(year, CreateCalindar::SEPTEMBER, aMay2);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень танкістаў\n");
                }
            }
            gosud.setDate(year, CreateCalindar::SEPTEMBER, 15);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень бібліятэк\n");
            gosud.setDate(year, CreateCalindar::SEPTEMBER, 20);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень мытніка\n");
            for (int aMay3 : may3) {
                gosud.setDate(year, CreateCalindar::SEPTEMBER, aMay3);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў лесу\n");
                }
            }
            for (int aMay5 : may5) {
                gosud.setDate(year, CreateCalindar::SEPTEMBER, aMay5);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень машынабудаўніка\n");
                }
            }
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::OCTOBER, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень настаўніка\n");
                }
            }
            gosud.setDate(year, CreateCalindar::OCTOBER, 6);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень архівіста\n");
            for (int aMay2 : may2) {
                gosud.setDate(year, CreateCalindar::OCTOBER, aMay2);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў культуры\n");
                }
            }
            gosud.setDate(year, CreateCalindar::OCTOBER, 14);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень стандартызацыі\n");
            gosud.setDate(year, CreateCalindar::OCTOBER, 15);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работнікаў фармацэўтычнай і мікрабіялагічнай прамысловасьці\n");
            for (int aMay6 : may6) {
                gosud.setDate(year, CreateCalindar::OCTOBER, aMay6);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень аўтамабіліста і дарожніка\n");
                }
            }
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::NOVEMBER, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў грамадзянскай авіяцыі\n");
                }
            }
            for (int aMay3 : may3) {
                gosud.setDate(year, CreateCalindar::NOVEMBER, aMay3);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень работнікаў сельскай гаспадаркі і перапрацоўчай прамысловасьці аграпрамысловага комплексу\n");
                }
            }
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::DECEMBER, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SATURDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень страхавых работнікаў\n");
                }
            }
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::DECEMBER, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень юрыста\n");
                }
            }
            gosud.setDate(year, CreateCalindar::DECEMBER, 17);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень беларускага кіно\n");
            gosud.setDate(year, CreateCalindar::DECEMBER, 20);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень работніка органаў дзяржаўнай бясьпекі\n");
            gosud.setDate(year, CreateCalindar::DECEMBER, 22);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень энэргетыка\n");
            gosud.setDate(year, CreateCalindar::JANUARY, 21);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень інжынерных войскаў\n");
            for (int aMay1 : may2) {
                gosud.setDate(year, CreateCalindar::APRIL, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень войскаў супрацьпаветранай абароны\n");
                }
            }
            gosud.setDate(year, CreateCalindar::AUGUST, 6);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень чыгуначных войскаў\n");
            gosud.setDate(year, CreateCalindar::NOVEMBER, 19);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень ракетных войскаў і артылерыі\n");
            gosud.setDate(year, CreateCalindar::MARCH, 15);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень спажыўца\n");
            gosud.setDate(year, CreateCalindar::MAY, 15);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень сям'і\n");
            gosud.setDate(year, CreateCalindar::JUNE, 5);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень аховы навакольнага асяроддзя\n");
            for (int aMay1 : may5) {
                gosud.setDate(year, CreateCalindar::JUNE, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень моладзі\n");
                }
            }
            gosud.setDate(year, CreateCalindar::SEPTEMBER, 1);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень ведаў\n");
            for (int aMay1 : may1) {
                gosud.setDate(year, CreateCalindar::SEPTEMBER, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::SUNDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень беларускага пісьменства\n");
                }
            }
            for (int aMay1 : may3) {
                gosud.setDate(year, CreateCalindar::SEPTEMBER, aMay1);
                int wik = gosud.dayOfWeek();
                if (wik == CreateCalindar::TUESDAY) {
                    if (gosud.dayOfYear() == DayYear)
                        result.insert(0, "Дзень міру\n");
                }
            }
            gosud.setDate(year, CreateCalindar::OCTOBER, 1);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень пажылых людзей\n");
            gosud.setDate(year, CreateCalindar::OCTOBER, 14);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень маці\n");
            gosud.setDate(year, CreateCalindar::OCTOBER, 21);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень бацькі\n");
            gosud.setDate(year, CreateCalindar::DECEMBER, 3);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень інвалідаў Рэспублікі Беларусь\n");
            gosud.setDate(year, CreateCalindar::DECEMBER, 10);
            if (gosud.dayOfYear() == DayYear)
                result.insert(0, "Дзень правоў чалавека\n");
            return result.trimmed();
        }
