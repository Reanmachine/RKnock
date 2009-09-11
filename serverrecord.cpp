#include "serverrecord.h"

#include <QStringList>
#include <QtXml>

ServerRecord::ServerRecord()
{
}

void ServerRecord::fromElement(QDomElement el)
{
    serverOpen()->clear();
    serverClose()->clear();

    QString sName = el.attribute("ServerName", "<Empty Server Name>");
    QString sHost = el.attribute("ServerHost", "<Empty Server Host>");

    setServerName(sName);
    setServerHost(sHost);

    QDomElement osq = el.firstChildElement("OpenSequence");
    QDomElement csq = el.firstChildElement("CloseSequence");


    if (!osq.isNull())
    {
        QDomElement portEl = osq.firstChildElement("Port");
        while(!portEl.isNull())
        {
            bool ok = false;
            int p = portEl.attribute("Value", "0").toInt(&ok);

            if (ok)
            {
                serverOpen()->append(p);
            }

            portEl = portEl.nextSiblingElement("Port");
        }
    }

    if (!csq.isNull())
    {
        QDomElement portEl = csq.firstChildElement("Port");
        while(!portEl.isNull())
        {
            bool ok = false;
            int p = portEl.attribute("Value", "0").toInt(&ok);

            if (ok)
            {
                serverClose()->append(p);
            }

            portEl = portEl.nextSiblingElement("Port");
        }
    }
}

QDomElement ServerRecord::toElement(QDomDocument doc)
{
    QDomElement el = doc.createElement("Server");
    el.setAttribute("ServerName", serverName());
    el.setAttribute("ServerHost", serverHost());

    QDomElement osq = doc.createElement("OpenSequence");
    for (int i = 0; i < this->m_serverOpen.size(); i++)
    {
        QDomElement e = doc.createElement("Port");
        e.setAttribute("Value", QString("%1").arg(m_serverOpen.at(i)));
        osq.appendChild(e);
    }
    el.appendChild(osq);

    QDomElement csq = doc.createElement("CloseSequence");
    for (int i = 0; i < this->m_serverClose.size(); i++)
    {
        QDomElement e = doc.createElement("Port");
        e.setAttribute("Value", QString("%1").arg(m_serverClose.at(i)));
        csq.appendChild(e);
    }
    el.appendChild(csq);

    return el;
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
    m_serverOpen.clear();

    QStringList ports = close.split(",");
    for (int i = 0; i < ports.size(); i++)
    {
        bool ok = false;
        QString port = ports.at(i);
        int iPort = port.toInt(&ok, 10);

        if (ok)
        {
            m_serverOpen.append(iPort);
        }
    }
}
