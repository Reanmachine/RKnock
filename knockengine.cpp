#include <QtDebug>
#include "knockengine.h"

KnockEngine::KnockEngine()
{

}


void KnockEngine::hostLookup(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError)
    {
        qDebug() << "Host Lookup Failed: " << host.errorString();
        return;
    }

    if (host.addresses().size() > 0)
    {
        this->addr = host.addresses().at(0); // First Address
    }
    else
    {
        qDebug() << "No Addresses Found.";
    }
}

