#include <QtGui/QApplication>
#include "core.h"
#include "basewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("RKnock");
    a.setApplicationVersion(RKNOCK_VERSION);
    a.setOrganizationName("Reanmachine");
    a.setOrganizationDomain("reanmachine.com");

    BaseWindow w;
    //w.show();
    return a.exec();
}
