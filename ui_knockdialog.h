/********************************************************************************
** Form generated from reading ui file 'knockdialog.ui'
**
** Created: Thu Sep 10 23:11:09 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_KNOCKDIALOG_H
#define UI_KNOCKDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KnockDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QProgressBar *progressBar;
    QFrame *line;
    QListWidget *lstDetails;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAbort;
    QPushButton *btnClose;

    void setupUi(QDialog *KnockDialog)
    {
        if (KnockDialog->objectName().isEmpty())
            KnockDialog->setObjectName(QString::fromUtf8("KnockDialog"));
        KnockDialog->resize(400, 160);
        KnockDialog->setMinimumSize(QSize(400, 160));
        KnockDialog->setMaximumSize(QSize(400, 160));
        layoutWidget = new QWidget(KnockDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 381, 145));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        lstDetails = new QListWidget(layoutWidget);
        lstDetails->setObjectName(QString::fromUtf8("lstDetails"));

        verticalLayout->addWidget(lstDetails);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAbort = new QPushButton(layoutWidget);
        btnAbort->setObjectName(QString::fromUtf8("btnAbort"));
        btnAbort->setEnabled(false);

        horizontalLayout->addWidget(btnAbort);

        btnClose = new QPushButton(layoutWidget);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(KnockDialog);
        QObject::connect(btnAbort, SIGNAL(clicked()), KnockDialog, SLOT(abort()));

        QMetaObject::connectSlotsByName(KnockDialog);
    } // setupUi

    void retranslateUi(QDialog *KnockDialog)
    {
        KnockDialog->setWindowTitle(QApplication::translate("KnockDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        btnAbort->setText(QApplication::translate("KnockDialog", "Abort", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("KnockDialog", "Close...", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(KnockDialog);
    } // retranslateUi

};

namespace Ui {
    class KnockDialog: public Ui_KnockDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KNOCKDIALOG_H
