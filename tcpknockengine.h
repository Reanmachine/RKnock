#ifndef TCPKNOCKENGINE_H
#define TCPKNOCKENGINE_H

#include "knockengine.h"

class TcpKnockEngine : public KnockEngine
{
public:
    TcpKnockEngine();

    bool knockPort(int port);
};

#endif // TCPKNOCKENGINE_H
