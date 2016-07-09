#ifndef STOY_H
#define STOY_H

#include <QtCore>
#include <iostream>
#include <QTextStream>

class MyWork : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("author", "Timotej")


public:
    MyWork(QObject *parent = 0) : QObject(parent)
    {

    }

    ~MyWork() {}

public slots:
    void run() {
        QTextStream out(stdout);
        QString s = tr("Hello World!");
        out << s << "\n";

        s.replace(s.length() - 1, 1, ", ");
        s.append("and another hello!");
        out << s << "\n";

        emit finished();
    }
signals:
    void finished();
};

#endif // STOY_H
