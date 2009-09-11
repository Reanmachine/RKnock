#ifndef BASEWINDOW_H
#define BASEWINDOW_H

// QtCore
#include <QList>

// QtGui
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QSystemTrayIcon>
#include <QtGui/QWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QCloseEvent>

// QtXml
#include <QtXml>

#include "serverrecord.h"


namespace Ui
{
    class BaseWindow;
}

class BaseWindow : public QWidget
{
    Q_OBJECT
    QPointer<QSystemTrayIcon> tray;
    QPointer<QMenu> trayMenu;
    QPointer<QMenu> trayServersMenu;

public:
    BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

    QList<ServerRecord*>* servers() { return &m_servers; }

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void activateMenu(QSystemTrayIcon::ActivationReason reason);

    // Settings
    void saveSettings();
    void loadSettings();

    // Server Manipulation
    void updateServer(QListWidgetItem* wid);
    void updateLiveServerName(QString newText);
    void editServer(QListWidgetItem* cur, QListWidgetItem* prev);
    void newServer();
    void delServer();

    void populateServer();

    void updateServerName(QString oName, QString sName);

    void rebuildActions();

    void knockOpen();
    void knockClose();
    void cleanupForm();
private:
    Ui::BaseWindow *ui;

    ServerRecord *findRecord(QListWidgetItem* wid);

    int serverCounter;

    void insertServer(QString name, QString host, QList<int> open, QList<int> close);
    void insertServer(QDomElement el);

    void deleteMenuItems(QMenu *menu);
    QMenu* buildServerMenu(ServerRecord *rec);

    QList<ServerRecord*> m_servers;

    QString cfgFileLocation;

private slots:
    void on_btnSaveConfig_clicked();
};

#endif // BASEWINDOW_H
