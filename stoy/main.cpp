#include <QCoreApplication>
#include <QTimer>
#include <stoy.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    int ret, i;

    QCoreApplication a(argc, argv);

    a.setApplicationVersion(QCoreApplication::translate("main", "V1"));

    MyWork *work = new MyWork(&a);

    const QMetaObject *mo = work->metaObject();

    QCommandLineParser p;


    p.setApplicationDescription("The purpose of this app is to play around with Qt.");
    p.addHelpOption();
    p.addVersionOption();

    p.addOptions({
      { "a1", QCoreApplication::translate("main", "Argument one") },
      { { "a2", "arg2" }, QCoreApplication::translate("main", "Argument two"), "a2value" },
    });
    p.process(a);


    if ( p.isSet("a1") ) {
        printf("A1 is set!\n");
    }

    if ( p.isSet("a2") ) {
        printf("A2 is set: %s\n", p.value("a2").toLocal8Bit().constData() );
    }


    printf("Class name: %s\n", mo->className());
    printf("Property count: %d\n", mo->propertyCount());
    for ( i=0; i<mo->propertyCount(); i++ ) {
        QMetaProperty prop = mo->property(i);
        QString val = prop.read(&a).toString();
        printf("  - %s = %s\n", prop.name(), val.toLocal8Bit().constData());
    }

    printf("Class info count: %d\n", mo->classInfoCount());
    for ( i=0; i<mo->classInfoCount(); i++ ) {
        QMetaClassInfo ci = mo->classInfo(i);
        printf("  - %s = %s\n", ci.name(), ci.value());
    }

    QObject::connect(work, SIGNAL(finished()), &a, SLOT(quit()));

    QTimer::singleShot(0, work, SLOT(run()));

    return ret;
}

