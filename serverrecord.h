#ifndef SERVERRECORD_H
#define SERVERRECORD_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDomDocument>
#include <QDomElement>

class ServerRecord : public QObject
{
    Q_OBJECT
private:
    QString m_serverName;
    QString m_serverHost;
    QList<int> m_serverOpen;
    QList<int> m_serverClose;

public:
    ServerRecord();

    QString serverName() { return this->m_serverName; }
    QString serverHost() { return this->m_serverHost; }
    QList<int> *serverOpen() { return &(this->m_serverOpen); }
    QList<int> *serverClose() { return &(this->m_serverClose); }

    void setServerName(QString name) { serverNameUpdated(this->m_serverName, name); this->m_serverName = name; }
    void setServerHost(QString host) { this->m_serverHost = host; }

    void fromStringOpen(QString open);
    void fromStringClose(QString close);

    QString toStringOpen();
    QString toStringClose();

    // Xml Translation Functions
    QDomElement toElement(QDomDocument doc);
    void fromElement(QDomElement el);

signals:
    void serverNameUpdated(QString oName, QString sName);
    void knockOpen();
    void knockClose();

};

#endif // SERVERRECORD_H
