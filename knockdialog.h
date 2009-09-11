#ifndef KNOCKDIALOG_H
#define KNOCKDIALOG_H

// Core
#include <QtCore/QPointer>

// Gui
#include <QtGui/QDialog>
#include <QtGui/QCloseEvent>

#include "serverrecord.h"
#include "knockerthread.h"

namespace Ui {
    class KnockDialog;
}

class KnockDialog : public QDialog {
    Q_OBJECT
    Q_ENUMS(KnockMode)

public:
    enum KnockMode { Open, Close };

    KnockDialog(QWidget *parent = 0, ServerRecord *rec = 0, KnockDialog::KnockMode mode = KnockDialog::Open);
    ~KnockDialog();

public slots:
    void knockOpen();
    void knockClose();
    void updateStatus(QString status);
    void lockForm();
    void unlockForm();
    void abort();
    void knockStep();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

private:
    Ui::KnockDialog *m_ui;

    bool locked;

    KnockMode mode;
    QPointer<KnockerThread> thread;

    QPointer<ServerRecord> record;

private slots:
    void on_btnClose_clicked();
};

#endif // KNOCKDIALOG_H
