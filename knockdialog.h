#ifndef KNOCKDIALOG_H
#define KNOCKDIALOG_H

// Core
#include <QtCore/QPointer>

// Gui
#include <QtGui/QDialog>

#include "serverrecord.h"

namespace Ui {
    class KnockDialog;
}

class KnockDialog : public QDialog {
    Q_OBJECT
public:
    KnockDialog(QWidget *parent = 0, ServerRecord *rec = 0);
    ~KnockDialog();

public slots:
    void knockOpen();
    void knockClose();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KnockDialog *m_ui;

    QPointer<ServerRecord> record;
};

#endif // KNOCKDIALOG_H
