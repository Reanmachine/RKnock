#include "basewindow.h"
#include "ui_basewindow.h"

#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>
#include <QtGui/QMessageBox>

BaseWindow::BaseWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::BaseWindow)
{
    serverCounter = 1;
    ui->setupUi(this);
}

BaseWindow::~BaseWindow()
{
    qDeleteAll(this->m_servers);
    delete ui;
}

// SLOTS //

void BaseWindow::saveSettings()
{

}

void BaseWindow::loadSettings()
{

}

void BaseWindow::newServer()
{
    ServerRecord *rec = new ServerRecord();
    rec->setServerName(QString("New Server %1").arg(this->serverCounter++));
    rec->setServerHost("");

    this->servers()->append(rec);
    this->ui->lstServers->addItem(rec->serverName());
}

void BaseWindow::delServer()
{
    /*QList<QListWidgetItem*> items = this->ui->lstServers->selectedItems();
    if (items.size() == 0)
        return; // Do nothing*/

    // Get the selected item!
    QListWidgetItem *selItem = 0;
    selItem = this->ui->lstServers->currentItem();

    if (selItem == 0)
        QMessageBox::critical(this, "No Item Selected.", "You must select an item to delete!");

    // Find the record
    ServerRecord *foundRec = 0;
    for(int i = 0; i < m_servers.size(); i++)
    {
        ServerRecord *rec = m_servers.at(i);
        if (rec->serverName() == selItem->text())
        {
            foundRec = rec;
        }
    }

    if (foundRec == 0)
    {
        QMessageBox::critical(this, "Couldn't Find Server Record!", "Couldn't find the server record in our internal database for the item you selected.", QMessageBox::Ok, QMessageBox::NoButton);
    }
    else
    {
        // Remove the item from the list!
        int delRow = this->ui->lstServers->row(selItem);
        this->ui->lstServers->takeItem(delRow); // Actual Removal
        delete selItem; // Delete the object!

        // Remove the record
        this->m_servers.removeOne(foundRec);
        delete foundRec; // Cleanup
    }
}

void BaseWindow::editServer(QListWidgetItem* cur, QListWidgetItem* prev = 0)
{
    // First Thing's First, Make sure the previous settings were saved, let's make sure we know who the previous one was!
    if (prev != 0)
        this->updateServer(prev);

    this->populateServer();
}
ServerRecord* BaseWindow::findRecord(QListWidgetItem* wid)
{
    ServerRecord *foundRec = 0;
    for(int i = 0; i < m_servers.size(); i++)
    {
        ServerRecord *rec = m_servers.at(i);
        if (rec->serverName() == wid->text())
        {
            foundRec = rec;
        }
    }

    return foundRec;
}

void BaseWindow::updateServer(QListWidgetItem* wid)
{
    ServerRecord *foundRec = this->findRecord(wid);

    if (foundRec == 0)
    {
        return; // Do shit all
    }
    else
    {
        // We found the record, let's save to it!
        foundRec->setServerName(this->ui->txtServerName->text());
        foundRec->setServerHost(this->ui->txtServerHost->text());
        foundRec->fromStringOpen(this->ui->txtOpenSequence->toPlainText());
        foundRec->fromStringClose(this->ui->txtCloseSequence->toPlainText());

        // Update the widget item
        wid->setText(this->ui->txtServerName->text());
    }
}


void BaseWindow::populateServer()
{
    QListWidgetItem *wid = 0;
    wid = this->ui->lstServers->currentItem();

    if (wid == 0)
        return;

    ServerRecord *foundRec = this->findRecord(wid);

    if (foundRec == 0)
        return;

    this->ui->txtServerName->setText(foundRec->serverName());
    this->ui->txtServerHost->setText(foundRec->serverHost());
    this->ui->txtOpenSequence->setPlainText(foundRec->toStringOpen());
    this->ui->txtCloseSequence->setPlainText(foundRec->toStringClose());
}
