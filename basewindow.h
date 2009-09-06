#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtGui/QWidget>
#include <QtGui/QListWidgetItem>
#include <QList>


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
    void editServer(QListWidgetItem* cur, QListWidgetItem* prev);
    void newServer();
    void delServer();

    void populateServer();

private:
    Ui::BaseWindow *ui;

    ServerRecord *findRecord(QListWidgetItem* wid);

    int serverCounter;

    QList<ServerRecord*> m_servers;
};

#endif // BASEWINDOW_H
