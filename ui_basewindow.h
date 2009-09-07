/********************************************************************************
** Form generated from reading ui file 'basewindow.ui'
**
** Created: Sun Sep 6 09:28:44 2009
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindow
{
public:
    QGroupBox *grpDetails;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vlayServerDetails;
    QLabel *lblServerName;
    QLineEdit *txtServerName;
    QLabel *lblServerHost;
    QLineEdit *txtServerHost;
    QLabel *lblOpenSequence;
    QPlainTextEdit *txtOpenSequence;
    QLabel *lblCloseSequence;
    QPlainTextEdit *txtCloseSequence;
    QListWidget *lstServers;
    QPushButton *btnSaveConfig;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddServer;
    QPushButton *btnDelServer;

    void setupUi(QWidget *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName(QString::fromUtf8("BaseWindow"));
        BaseWindow->resize(640, 480);
        BaseWindow->setMinimumSize(QSize(640, 480));
        BaseWindow->setMaximumSize(QSize(640, 480));
        grpDetails = new QGroupBox(BaseWindow);
        grpDetails->setObjectName(QString::fromUtf8("grpDetails"));
        grpDetails->setGeometry(QRect(370, 10, 261, 401));
        grpDetails->setFlat(false);
        grpDetails->setCheckable(false);
        verticalLayoutWidget = new QWidget(grpDetails);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 241, 371));
        vlayServerDetails = new QVBoxLayout(verticalLayoutWidget);
        vlayServerDetails->setSpacing(6);
        vlayServerDetails->setMargin(5);
        vlayServerDetails->setObjectName(QString::fromUtf8("vlayServerDetails"));
        vlayServerDetails->setContentsMargins(0, 0, 0, 0);
        lblServerName = new QLabel(verticalLayoutWidget);
        lblServerName->setObjectName(QString::fromUtf8("lblServerName"));
        lblServerName->setMaximumSize(QSize(16777215, 24));

        vlayServerDetails->addWidget(lblServerName);

        txtServerName = new QLineEdit(verticalLayoutWidget);
        txtServerName->setObjectName(QString::fromUtf8("txtServerName"));

        vlayServerDetails->addWidget(txtServerName);

        lblServerHost = new QLabel(verticalLayoutWidget);
        lblServerHost->setObjectName(QString::fromUtf8("lblServerHost"));
        lblServerHost->setMaximumSize(QSize(16777215, 32));

        vlayServerDetails->addWidget(lblServerHost);

        txtServerHost = new QLineEdit(verticalLayoutWidget);
        txtServerHost->setObjectName(QString::fromUtf8("txtServerHost"));

        vlayServerDetails->addWidget(txtServerHost);

        lblOpenSequence = new QLabel(verticalLayoutWidget);
        lblOpenSequence->setObjectName(QString::fromUtf8("lblOpenSequence"));
        lblOpenSequence->setMaximumSize(QSize(16777215, 32));

        vlayServerDetails->addWidget(lblOpenSequence);

        txtOpenSequence = new QPlainTextEdit(verticalLayoutWidget);
        txtOpenSequence->setObjectName(QString::fromUtf8("txtOpenSequence"));
        txtOpenSequence->setTabChangesFocus(true);

        vlayServerDetails->addWidget(txtOpenSequence);

        lblCloseSequence = new QLabel(verticalLayoutWidget);
        lblCloseSequence->setObjectName(QString::fromUtf8("lblCloseSequence"));

        vlayServerDetails->addWidget(lblCloseSequence);

        txtCloseSequence = new QPlainTextEdit(verticalLayoutWidget);
        txtCloseSequence->setObjectName(QString::fromUtf8("txtCloseSequence"));
        txtCloseSequence->setTabChangesFocus(true);

        vlayServerDetails->addWidget(txtCloseSequence);

        lstServers = new QListWidget(BaseWindow);
        lstServers->setObjectName(QString::fromUtf8("lstServers"));
        lstServers->setGeometry(QRect(10, 10, 351, 401));
        btnSaveConfig = new QPushButton(BaseWindow);
        btnSaveConfig->setObjectName(QString::fromUtf8("btnSaveConfig"));
        btnSaveConfig->setGeometry(QRect(510, 450, 121, 23));
        widget = new QWidget(BaseWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 420, 351, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnAddServer = new QPushButton(widget);
        btnAddServer->setObjectName(QString::fromUtf8("btnAddServer"));

        horizontalLayout->addWidget(btnAddServer);

        btnDelServer = new QPushButton(widget);
        btnDelServer->setObjectName(QString::fromUtf8("btnDelServer"));

        horizontalLayout->addWidget(btnDelServer);


        retranslateUi(BaseWindow);
        QObject::connect(btnAddServer, SIGNAL(clicked()), BaseWindow, SLOT(newServer()));
        QObject::connect(btnDelServer, SIGNAL(clicked()), BaseWindow, SLOT(delServer()));
        QObject::connect(lstServers, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), BaseWindow, SLOT(editServer(QListWidgetItem*,QListWidgetItem*)));
        QObject::connect(txtServerName, SIGNAL(textChanged(QString)), BaseWindow, SLOT(updateLiveServerName(QString)));

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QWidget *BaseWindow)
    {
        BaseWindow->setWindowTitle(QApplication::translate("BaseWindow", "BaseWindow", 0, QApplication::UnicodeUTF8));
        grpDetails->setTitle(QApplication::translate("BaseWindow", "Server Details:", 0, QApplication::UnicodeUTF8));
        lblServerName->setText(QApplication::translate("BaseWindow", "Server Name:", 0, QApplication::UnicodeUTF8));
        lblServerHost->setText(QApplication::translate("BaseWindow", "Server Hostname/IP:", 0, QApplication::UnicodeUTF8));
        lblOpenSequence->setText(QApplication::translate("BaseWindow", "Open Sequence:", 0, QApplication::UnicodeUTF8));
        lblCloseSequence->setText(QApplication::translate("BaseWindow", "Close Sequence:", 0, QApplication::UnicodeUTF8));
        btnSaveConfig->setText(QApplication::translate("BaseWindow", "Save Settings...", 0, QApplication::UnicodeUTF8));
        btnAddServer->setText(QApplication::translate("BaseWindow", "Add Server...", 0, QApplication::UnicodeUTF8));
        btnDelServer->setText(QApplication::translate("BaseWindow", "Delete Server", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(BaseWindow);
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H
