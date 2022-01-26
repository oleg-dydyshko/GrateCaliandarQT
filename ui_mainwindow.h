/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *create;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *yearEdit_1;
    QLabel *label_2;
    QLineEdit *yearEdit_2;
    QLabel *label_3;
    QProgressBar *progressBar;
    QPushButton *exit;
    QProgressBar *progressBar_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton;
    QSpinBox *lineEditBeta;
    QSpinBox *lineEditRelise;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(353, 460);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(353, 460));
        MainWindow->setMaximumSize(QSize(353, 460));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/image/krest.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setMaximumSize(QSize(353, 460));
        create = new QPushButton(centralwidget);
        create->setObjectName(QString::fromUtf8("create"));
        create->setGeometry(QRect(100, 88, 143, 34));
        create->setLayoutDirection(Qt::LeftToRight);
        create->setAutoExclusive(false);
        checkBox_1 = new QCheckBox(centralwidget);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(6, 127, 221, 22));
        checkBox_1->setChecked(true);
        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(6, 155, 273, 22));
        checkBox_2->setTabletTracking(false);
        checkBox_2->setChecked(true);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(6, 371, 341, 34));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        yearEdit_1 = new QLineEdit(layoutWidget);
        yearEdit_1->setObjectName(QString::fromUtf8("yearEdit_1"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(yearEdit_1->sizePolicy().hasHeightForWidth());
        yearEdit_1->setSizePolicy(sizePolicy2);
        yearEdit_1->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(yearEdit_1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        yearEdit_2 = new QLineEdit(layoutWidget);
        yearEdit_2->setObjectName(QString::fromUtf8("yearEdit_2"));
        sizePolicy2.setHeightForWidth(yearEdit_2->sizePolicy().hasHeightForWidth());
        yearEdit_2->setSizePolicy(sizePolicy2);
        yearEdit_2->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(yearEdit_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(6, 36, 341, 26));
        progressBar->setMaximum(1);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);
        progressBar->setInvertedAppearance(false);
        exit = new QPushButton(centralwidget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(130, 415, 84, 34));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(exit->sizePolicy().hasHeightForWidth());
        exit->setSizePolicy(sizePolicy3);
        progressBar_2 = new QProgressBar(centralwidget);
        progressBar_2->setObjectName(QString::fromUtf8("progressBar_2"));
        progressBar_2->setEnabled(true);
        progressBar_2->setGeometry(QRect(6, 190, 341, 26));
        progressBar_2->setMaximum(1);
        progressBar_2->setValue(0);
        progressBar_2->setAlignment(Qt::AlignCenter);
        progressBar_2->setTextVisible(true);
        progressBar_2->setInvertedAppearance(false);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 16, 331, 20));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(6, 240, 331, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(6, 310, 331, 20));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(317, 0, 31, 34));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/image/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon1);
        pushButton->setIconSize(QSize(20, 20));
        lineEditBeta = new QSpinBox(centralwidget);
        lineEditBeta->setObjectName(QString::fromUtf8("lineEditBeta"));
        lineEditBeta->setGeometry(QRect(6, 260, 81, 32));
        lineEditBeta->setMinimum(43900);
        lineEditBeta->setMaximum(100000);
        lineEditBeta->setValue(44000);
        lineEditRelise = new QSpinBox(centralwidget);
        lineEditRelise->setObjectName(QString::fromUtf8("lineEditRelise"));
        lineEditRelise->setGeometry(QRect(6, 330, 81, 32));
        lineEditRelise->setMinimum(43900);
        lineEditRelise->setMaximum(100000);
        lineEditRelise->setValue(44000);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 60, 331, 18));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 210, 331, 18));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\262\320\260\321\200\321\213\321\206\321\214 \320\272\320\260\320\273\321\217\320\275\320\264\320\260\321\200", nullptr));
        create->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\262\320\260\321\200\321\213\321\206\321\214 \320\272\320\260\320\273\321\217\320\275\320\264\320\260\321\200", nullptr));
        checkBox_1->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\260\320\274\320\277\320\260\320\262\320\260\321\206\321\214 \321\204\320\260\320\271\320\273\321\213 \320\267 \321\201\320\260\320\271\321\202\320\260", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "\320\240\321\215\320\267\320\265\321\200\320\262\320\276\320\262\320\260\320\265 \320\272\320\260\320\277\321\226\321\217\320\262\320\260\320\275\321\214\320\275\320\265 \321\204\320\260\320\271\320\273\320\260\321\236 \321\201\320\260\320\271\321\202\320\260", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\227", nullptr));
        yearEdit_1->setText(QCoreApplication::translate("MainWindow", "2019", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\277\320\260", nullptr));
        yearEdit_2->setText(QCoreApplication::translate("MainWindow", "2022", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\263\320\276\320\264", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "\320\223\320\260\321\202\320\276\320\262\320\260!", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\206\321\226\321\201\320\275\321\226\321\206\320\265 \"\320\241\321\202\320\262\320\260\321\200\321\213\321\206\321\214 \320\272\320\260\320\273\321\217\320\275\320\264\320\260\321\200\"", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\320\264\320\260\321\206\321\214 \320\260\320\261\320\275\320\260\321\236\320\273\320\265\320\275\321\214\320\275\320\265 \320\221\320\265\321\202\320\260 \320\262\320\265\321\200\321\201\321\226\321\226", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\320\264\320\260\321\206\321\214 \320\260\320\261\320\275\320\260\321\236\320\273\320\265\320\275\321\214\320\275\320\265 \320\240\320\260\320\261\320\276\321\207\320\260\320\271 \320\262\320\265\321\200\321\201\321\226\321\226", nullptr));
        pushButton->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\221\321\203\320\264\320\267\320\265 \320\267\320\260\320\277\320\260\320\274\320\277\320\276\320\262\320\260\320\275\320\260: 0", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\221\321\203\320\264\320\267\320\265 \320\267\320\260\320\277\320\260\320\274\320\277\320\276\320\262\320\260\320\275\320\260: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
