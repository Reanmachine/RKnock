#include "udpknockengine.h"
#include "knockengine.h"
#include <QUdpSocket>

UdpKnockEngine::UdpKnockEngine()
{
}

bool UdpKnockEngine::knockPort(int port)
{
    QUdpSocket sock;

    sock.writeDatagram(QString("Knock, Knock!").toAscii(), this->addr, (quint16)port);

    if (sock.error())
        return false;
    else
        return true;
}
