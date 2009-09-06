/********************************************************************************
** Form generated from reading ui file 'basewindow.ui'
**
** Created: Sun Sep 6 06:10:58 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindow
{
public:
    QGroupBox *grpDetails;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *txtServerName;
    QListWidget *lstServers;

    void setupUi(QWidget *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName(QString::fromUtf8("BaseWindow"));
        BaseWindow->resize(640, 480);
        BaseWindow->setMinimumSize(QSize(640, 480));
        BaseWindow->setMaximumSize(QSize(640, 480));
        grpDetails = new QGroupBox(BaseWindow);
        grpDetails->setObjectName(QString::fromUtf8("grpDetails"));
        grpDetails->setGeometry(QRect(370, 20, 261, 391));
        grpDetails->setFlat(false);
        grpDetails->setCheckable(false);
        formLayoutWidget = new QWidget(grpDetails);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 20, 241, 361));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setMargin(11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        txtServerName = new QLineEdit(formLayoutWidget);
        txtServerName->setObjectName(QString::fromUtf8("txtServerName"));

        formLayout->setWidget(0, QFormLayout::LabelRole, txtServerName);

        lstServers = new QListWidget(BaseWindow);
        lstServers->setObjectName(QString::fromUtf8("lstServers"));
        lstServers->setGeometry(QRect(20, 20, 341, 391));

        retranslateUi(BaseWindow);

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QWidget *BaseWindow)
    {
        BaseWindow->setWindowTitle(QApplication::translate("BaseWindow", "BaseWindow", 0, QApplication::UnicodeUTF8));
        grpDetails->setTitle(QApplication::translate("BaseWindow", "Server Details:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(BaseWindow);
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H
