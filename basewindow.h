#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtGui/QWidget>
#include <QtGui/QListWidgetItem>
#include <QList>
#include <QtXml>


#include "serverrecord.h"


namespace Ui
{
    class BaseWindow;
}

class BaseWindow : public QWidget
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = 0);
    ~BaseWindow();

    QList<ServerRecord*>* servers() { return &m_servers; }

public slots:
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

private:
    Ui::BaseWindow *ui;

    ServerRecord *findRecord(QListWidgetItem* wid);

    int serverCounter;

    void insertServer(QString name, QString host, QList<int> open, QList<int> close);
    void insertServer(QDomElement el);

    QList<ServerRecord*> m_servers;

    QString cfgFileLocation;

private slots:
    void on_btnSaveConfig_clicked();
};

#endif // BASEWINDOW_H
