#include "core.h"
#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QtGlobal>
#include <QApplication>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose, true); // Delete me when I close!
    this->setAttribute(Qt::WA_QuitOnClose, false);

    this->m_ui->lblQtVersion->setText(QString(qVersion()));
    this->m_ui->lblApplicationLine->setText(QString(RKNOCK_VERSION));

    QApplication *app = (QApplication*)QApplication::instance();
    QString line = QString("%1 %2").arg(app->organizationName(), app->applicationName());
    this->m_ui->lblApplicationLine->setText(line);
    this->m_ui->lblAppVersion->setText(app->applicationVersion());

    this->setWindowTitle(QString("About %1").arg(app->applicationName()));
}

AboutDialog::~AboutDialog()
{
    delete m_ui;
}

void AboutDialog::changeEvent(QEvent *e)
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
