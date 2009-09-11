#include "basewindow.h"
#include "ui_basewindow.h"

#include "knockdialog.h"

#include <QApplication>
#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>
#include <QtGui/QMessageBox>
#include <QtXml>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QSysInfo>

BaseWindow::BaseWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::BaseWindow)
{
    serverCounter = 1;
    ui->setupUi(this);

    QApplication *app = (QApplication*)QApplication::instance();
    this->setWindowTitle(QString("%1 %2 (v%3)").arg(app->organizationName(), app->applicationName(), app->applicationVersion()));

    // Icon
    QIcon ico(":/resources/RKnock.ico");
    this->setWindowIcon(ico);

    // Find the config file, does it exist?
#ifdef Q_WS_WIN
    QString fSection;
    QString mSection;
    QString lSection = "Settings.xml";

    if (QSysInfo::windowsVersion() < QSysInfo::WV_2000)
    {
        // All Versions before win2000
        fSection = QDir::currentPath(); // Where we are :)
        mSection = "";
    }
    else if (QSysInfo::windowsVersion() < QSysInfo::WV_VISTA)
    {
        fSection = QDir::homePath();
        mSection = QString("Application Data/%1/%2").arg(app->organizationName(), app->applicationName());
    }
    else
    {
        fSection = QDir::homePath();
        mSection = QString("AppData/Roaming/%1/%2").arg(app->organizationName(), app->applicationName());
    }

    if (mSection.size() == 0)
        this->cfgFileLocation = QString("%1/%2").arg(fSection, lSection);
    else
        this->cfgFileLocation = QString("%1/%2/%3").arg(fSection, mSection, lSection);

    //this->cfgFileLocation = QtDir::homePath().append("\\").append("
#else
    QString path = QString("%1/.%2/%3").arg(QDir::homePath(), app->organizationName(), app->applicationName());
    QString file = QString("%1/Settings.xml").arg(path);

    this->cfgFileLocation = file;
#endif

    if (QFile(this->cfgFileLocation).exists())
        this->loadSettings();

    this->tray = new QSystemTrayIcon(this);
    this->trayMenu = new QMenu(this);
    this->trayServersMenu = new QMenu("Servers", this->trayMenu);

    this->tray->setContextMenu(this->trayMenu);
    this->tray->setIcon(QIcon(":/resources/RKnock.ico"));
    this->tray->setVisible(true);

    QAction *subaction = 0;
    QMenu *submenu = 0;

    // Open Dialog
    subaction = this->trayMenu->addAction("Open Configuration Dialog...");
    //this->trayMenu->addSeparator();
    connect(subaction, SIGNAL(triggered()), this, SLOT(show()));

    this->trayMenu->addMenu(trayServersMenu);

    this->trayMenu->addSeparator();
    subaction = this->trayMenu->addAction("Exit...");
    connect(subaction, SIGNAL(triggered()), app, SLOT(quit()));

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activateMenu(QSystemTrayIcon::ActivationReason)));

    this->rebuildActions();
}

BaseWindow::~BaseWindow()
{
    qDeleteAll(this->m_servers);
    delete ui;
}
void BaseWindow::insertServer(QDomElement el)
{
    ServerRecord *rec = new ServerRecord();
    rec->fromElement(el);

    this->m_servers.append(rec);

    // Create the List Item
    QListWidgetItem *item = new QListWidgetItem(rec->serverName());
    this->ui->lstServers->addItem(item);
    connect(rec, SIGNAL(serverNameUpdated(QString,QString)), this, SLOT(updateServerName(QString,QString))); // Automagic updates (I hope!)
    connect(rec, SIGNAL(knockOpen()), this, SLOT(knockOpen()));
    connect(rec, SIGNAL(knockClose()), this, SLOT(knockClose()));
}

void BaseWindow::insertServer(QString name, QString host, QList<int> open, QList<int> close)
{
    // Build the Record
    ServerRecord *rec = new ServerRecord();
    rec->setServerName(name);
    rec->setServerHost(host);

    for(int i = 0; i < open.size(); i++)
        rec->serverOpen()->append(open.at(i));
    for(int i = 0; i < close.size(); i++)
        rec->serverClose()->append(close.at(i));

    this->m_servers.append(rec);

    // Create the List Item
    QListWidgetItem *item = new QListWidgetItem(name);
    this->ui->lstServers->addItem(item);
    connect(rec, SIGNAL(serverNameUpdated(QString,QString)), this, SLOT(updateServerName(QString,QString))); // Automagic updates (I hope!)
    connect(rec, SIGNAL(knockOpen()), this, SLOT(knockOpen()));
    connect(rec, SIGNAL(knockClose()), this, SLOT(knockClose()));
}

void BaseWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox question(QMessageBox::Question, "Save Changes?", "Closing this window you may lose some of your changes to the configuration.\n\nWould you like to save before exiting?", (QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel));
    int result = question.exec();

    if (result == QMessageBox::Cancel)
    {
        event->ignore();
    }
    else
    {
        if (result == QMessageBox::Yes)
        {
            QListWidgetItem *item = 0;
            item = this->ui->lstServers->currentItem();

            if (item != 0)
                this->updateServer(item); // Update any changes
            this->saveSettings(); // Save the config
            this->rebuildActions();
        }

        event->ignore();
        this->hide();
    }
}

// SLOTS //

void BaseWindow::activateMenu(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
    {
        this->show();
    }

    if (reason == QSystemTrayIcon::Context)
    {
        this->tray->show();
    }
}

void BaseWindow::saveSettings()
{
    QDomDocument doc;

    QDomElement root = doc.createElement("RKnockSettings");
    root.setAttribute("Version", "1.0.0.0000");
    doc.appendChild(root);

    for(int i = 0; i < m_servers.size(); i++)
    {
        ServerRecord *rec = m_servers.at(i);
        QDomElement server = rec->toElement(doc);
        root.appendChild(server);
    }

    QFileInfo cfgFileInfo(this->cfgFileLocation);
    QDir cfgPath = cfgFileInfo.absoluteDir();

    // If the folder dosen't exist, make it!
    if (!cfgPath.exists())
        cfgPath.mkpath(".");

    QFile cfgFile(this->cfgFileLocation);

    QString xmlOut = doc.toString();
    if (!cfgFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Unable to open Settings file for write.", QString("We were unable to open `%1` for writing, details below:\n\n%2").arg(cfgFileInfo.filePath(), cfgFile.errorString()));
        return;
    }

    QTextStream out(&cfgFile);
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>\n" << xmlOut;
}

void BaseWindow::loadSettings()
{
    QFile cfgFile(this->cfgFileLocation);
    if (!cfgFile.exists())
        return;

    if (!cfgFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QDomDocument doc;

    if (!doc.setContent(&cfgFile))
    {
        cfgFile.close();
        return;
    }

    cfgFile.close();

    QDomNodeList root = doc.elementsByTagName("Server");
    for (int i = 0; i < root.size(); i++)
    {
        QDomElement server = root.at(i).toElement();

        this->insertServer(server);
    }
}

void BaseWindow::updateServerName(QString oName, QString sName)
{
    for(int i = 0; i < this->ui->lstServers->count(); i++)
    {
        QListWidgetItem *item = this->ui->lstServers->item(i);
        if (item->text() == oName)
        {
            item->setText(sName);
            return;
        }
    }
}

void BaseWindow::newServer()
{
    // Add New Server Entry
    this->insertServer(QString("New Server %1").arg(this->serverCounter++), QString(), QList<int>(), QList<int>());
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
    if (wid == 0)
        return 0;

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

void BaseWindow::updateLiveServerName(QString newText)
{
    QListWidgetItem *wid = 0;
    wid = this->ui->lstServers->currentItem();

    if (wid == 0)
        return;

    ServerRecord *foundRec = this->findRecord(wid);

    if (foundRec == 0)
        return; // Do shit all

    foundRec->setServerName(newText);
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
        //wid->setText(this->ui->txtServerName->text());
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

void BaseWindow::on_btnSaveConfig_clicked()
{
    this->ui->btnSaveConfig->setEnabled(false);
    QListWidgetItem *item = 0;
    item = this->ui->lstServers->currentItem();

    this->updateServer(item); // Update any changes
    this->saveSettings(); // Save the config

    this->rebuildActions();
    this->ui->btnSaveConfig->setEnabled(true);

    this->hide();
}

void BaseWindow::rebuildActions()
{

    // Delete previous Servers & Thier Menus
    this->deleteMenuItems(this->trayServersMenu);

    for(int i = 0; i < this->servers()->size(); i++)
    {
        QMenu *menu = this->buildServerMenu(this->servers()->at(i));

        this->trayServersMenu->addMenu(menu);
    }

}

QMenu* BaseWindow::buildServerMenu(ServerRecord *rec)
{
    QString menuName("%1 (%2)");
    menuName = menuName.arg(rec->serverName(), rec->serverHost());

    // Build the base menu
    QMenu *menu = new QMenu(menuName);

    QAction *open = menu->addAction("Knock Open...");
    QAction *close = menu->addAction("Knock Close...");

    // Connect the actions
    connect(open, SIGNAL(triggered()), rec, SIGNAL(knockOpen()));
    connect(close, SIGNAL(triggered()), rec, SIGNAL(knockClose()));

    return menu;
}

void BaseWindow::deleteMenuItems(QMenu *menu)
{
    QList<QAction*> mActions = menu->actions();

    for (int i = 0; i < mActions.size(); i++)
    {
        QAction *act = mActions.at(i);

        menu->removeAction(act); // Remove the action!

        QMenu *men = 0;
        men = act->menu();
        if (men != 0)
        {
            this->deleteMenuItems(men); // Recursion
            men->deleteLater();
        }

        act->deleteLater();
    }

    // Note at this point mActions has dangling pointers...
}

void BaseWindow::knockOpen()
{
    ServerRecord *rec = (ServerRecord*)sender(); // Get the record

    KnockDialog *dialog = new KnockDialog(this, rec, KnockDialog::Open);
    connect(dialog, SIGNAL(finished()), this, SLOT(cleanupForm()));
    dialog->show();
}

void BaseWindow::knockClose()
{
    ServerRecord *rec = (ServerRecord*)sender(); // Get the record

    KnockDialog *dialog = new KnockDialog(this, rec, KnockDialog::Close);
    connect(dialog, SIGNAL(finished(int)), this, SLOT(cleanupForm()));
    dialog->show();
}

void BaseWindow::cleanupForm()
{
    sender()->deleteLater(); // Queue the sender for later deletion!
}
