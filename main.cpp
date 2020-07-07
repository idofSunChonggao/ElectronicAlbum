#include <QtGui/QApplication>
#include "formphoto.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FormPhoto w;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    w.showFullScreen();
    //w.show();
    
    return a.exec();
}
