#include "serverrecord.h"

#include <QStringList>

ServerRecord::ServerRecord()
{
}

void ServerRecord::fromElement(QDomElement el)
{

}

QDomElement ServerRecord::toElement(QDomDocument doc)
{

}

QString ServerRecord::toStringClose()
{
    QString output;
    output = "";

    for(int i = 0; i < this->m_serverClose.size(); i++)
    {
        int port = this->m_serverClose.at(i);
        if (i != 0)
            output.append(",");

        output.append(QString::number(port, 10));
    }

    return output;
}

void ServerRecord::fromStringClose(QString close)
{
    // Clear the old list
    m_serverClose.clear();

    QStringList ports = close.split(",");
    for (int i = 0; i < ports.size(); i++)
    {
        bool ok = false;
        QString port = ports.at(i);
        int iPort = port.toInt(&ok, 10);

        if (ok)
        {
            m_serverClose.append(iPort);
        }
    }
}

QString ServerRecord::toStringOpen()
{
    QString output;
    output = "";

    for(int i = 0; i < this->m_serverOpen.size(); i++)
    {
        int port = this->m_serverOpen.at(i);
        if (i != 0)
            output.append(",");

        output.append(QString::number(port, 10));
    }

    return output;
}

void ServerRecord::fromStringOpen(QString close)
{
    // Clear the old list
    m_serverClose.clear();

    QStringList ports = close.split(",");
    for (int i = 0; i < ports.size(); i++)
    {
        bool ok = false;
        QString port = ports.at(i);
        int iPort = port.toInt(&ok, 10);

        if (ok)
        {
            m_serverClose.append(iPort);
        }
    }
}
