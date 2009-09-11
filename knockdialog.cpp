#include "knockdialog.h"
#include "ui_knockdialog.h"

#include "knockerthread.h"

KnockDialog::KnockDialog(QWidget *parent, ServerRecord *rec, KnockDialog::KnockMode mode) :
    QDialog(parent),
    m_ui(new Ui::KnockDialog)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    m_ui->setupUi(this);

    this->setWindowTitle(QString("Knocking: %1").arg(rec->serverHost()));
    this->mode = mode;
    this->record = rec;
    this->locked = false;

    if (mode == KnockDialog::Open)
        knockOpen();
    if (mode == KnockDialog::Close)
        knockClose();
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

void KnockDialog::knockOpen()
{
    this->m_ui->progressBar->setMaximum(record->serverOpen()->size());
    this->m_ui->progressBar->setValue(0);

    thread = new KnockerThread(record->serverHost(), record->serverOpen());
    connect(thread, SIGNAL(beginSequence()), this, SLOT(lockForm()));
    connect(thread, SIGNAL(endSequence()), this, SLOT(unlockForm()));
    connect(thread, SIGNAL(status(QString)), this, SLOT(updateStatus(QString)));
    connect(thread, SIGNAL(step()), this, SLOT(knockStep()));

    thread->start();
}

void KnockDialog::knockClose()
{
    this->m_ui->progressBar->setMaximum(record->serverClose()->size());
    this->m_ui->progressBar->setValue(0);

    thread = new KnockerThread(record->serverHost(), record->serverClose());
    connect(thread, SIGNAL(beginSequence()), this, SLOT(lockForm()));
    connect(thread, SIGNAL(endSequence()), this, SLOT(unlockForm()));
    connect(thread, SIGNAL(status(QString)), this, SLOT(updateStatus(QString)));
    connect(thread, SIGNAL(step()), this, SLOT(knockStep()));

    thread->start();
}

void KnockDialog::updateStatus(QString status)
{
    this->m_ui->lstDetails->addItem(status);
    this->m_ui->lstDetails->scrollToBottom();
}

void KnockDialog::lockForm()
{
    this->locked = true;
    this->m_ui->btnClose->setEnabled(false);
    this->m_ui->btnAbort->setEnabled(true);
}

void KnockDialog::unlockForm()
{
    this->locked = false;
    this->m_ui->btnClose->setEnabled(true);
    this->m_ui->btnAbort->setEnabled(false);
}

void KnockDialog::on_btnClose_clicked()
{
    this->unlockForm();
    this->done(1);
}

void KnockDialog::closeEvent(QCloseEvent *event)
{
    if (!locked)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void KnockDialog::abort()
{
    if (this->thread.isNull())
        return;

    this->thread->catchTerminated();
}

void KnockDialog::knockStep()
{
    this->m_ui->progressBar->setValue(this->m_ui->progressBar->value()+1);
}
