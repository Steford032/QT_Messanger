#include <QCoreApplication>
#include"server.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server S;
    return a.exec();
}
