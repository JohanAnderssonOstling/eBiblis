#ifndef HOMEQUERIES_H
#define HOMEQUERIES_H
#include <QSqlQuery>
#include <QList>

#include <structs.h>

namespace homequery {
void createDB(QSqlQuery &query);
void addLibrary(QSqlQuery &query, struc::Library &library);
void deleteLibrary(QSqlQuery &query, QString uuid);
QList<struc::Library> getLibraries (QSqlQuery &query);
}
#endif // HOMEQUERIES_H
