#ifndef BOOKPARSERS_H
#define BOOKPARSERS_H
#include <QString>
#include <QFileInfo>
#include <structs.h>

namespace bookparser {
struc::Book parseBook(QFileInfo file);

}

#endif // BOOKPARSERS_H
