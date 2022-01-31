#ifndef LIBRARYQUERIES_H
#define LIBRARYQUERIES_H

#include <QSqlQuery>
#include <QVector>
#include <structs.h>

namespace libraryquery {
void createDB(QSqlQuery &query);
void addFolder(QSqlQuery &query, struc::Component folder);
int addBook(QSqlQuery &query, struc::Book book);
void addAuthor(QSqlQuery &query);

void setBookFolderID(QSqlQuery &query, QString name, int parentID);
void setBookLocation(QSqlQuery &query, QString location, int bookID);

bool bookExists(QSqlQuery &query, QString name);

QList<struc::Book> getBooks(QSqlQuery &query, int parentID);
QList<struc::Container> getFolders(QSqlQuery &query, int parentID);


QString getFolderPath(QSqlQuery &query, int parentFolderID);


}
#endif // LIBRARYQUERIES_H
