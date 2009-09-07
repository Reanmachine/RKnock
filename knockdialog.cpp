#include "knockdialog.h"
#include "ui_knockdialog.h"

KnockDialog::KnockDialog(QWidget *parent, ServerRecord *rec) :
    QDialog(parent),
    m_ui(new Ui::KnockDialog)
{
    m_ui->setupUi(this);

    this->record = rec;
}

KnockDialog::~KnockDialog()
{
    delete m_ui;
}

void KnockDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

// SLOTS //

void knockOpen();
void knockClose();
