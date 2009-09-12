#ifndef KNOCKENGINE_H
#define KNOCKENGINE_H

#include <QObject>
#include <QHostInfo>
#include <QHostAddress>

class KnockEngine : public QObject
{
    Q_OBJECT

protected:
    QHostAddress addr;

public:
    KnockEngine();

    bool hostReady() { return !addr.isNull(); }

    virtual bool knockPort(int port) = 0; // Port Knocking Implementation

public slots:
    void hostLookup(const QHostInfo &host);
};

#endif // KNOCKENGINE_H
