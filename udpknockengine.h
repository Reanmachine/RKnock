#ifndef UDPKNOCKENGINE_H
#define UDPKNOCKENGINE_H

#import "knockengine.h"

class UdpKnockEngine : public KnockEngine
{
public:
    UdpKnockEngine();

    bool knockPort(int port);
};

#endif // UDPKNOCKENGINE_H
