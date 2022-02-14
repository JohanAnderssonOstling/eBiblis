#ifndef LIBRARYQUERIES_H
#define LIBRARYQUERIES_H

#include <QSqlQuery>
#include <QVector>
#include <structs.h>

namespace libraryquery {
void createDB(QSqlQuery &query);

int addAuthor(QSqlQuery &query, QString name);
void addBookAuthor(QSqlQuery &query, int bookID, int authorID);
int addBook(QSqlQuery &query, struc::Book book);
void addFolder(QSqlQuery &query, struc::Component folder);



void setBookFolderID(QSqlQuery &query, QString name, int parentID);
void setBookLocation(QSqlQuery &query, QString location, int bookID);

int getAuthorID(QSqlQuery &query, QString name);
QStringList getAuthorNames(QSqlQuery &query, int bookID);

bool authorExists(QSqlQuery &query, QString name);
bool bookExists(QSqlQuery &query, QString name);

QList<struc::Book> getBooks(QSqlQuery &query, int parentID);
QList<struc::Container> getFolders(QSqlQuery &query, int parentID);


QString getFolderPath(QSqlQuery &query, int parentFolderID);


}
#endif // LIBRARYQUERIES_H
