#include <homequeries.h>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
void homequery::createDB(QSqlQuery &query) {
	query.exec("CREATE TABLE IF NOT EXISTS library("
				 "library_uuid TEXT PRIMARY KEY NOT NULL,"
				 "name TEXT NOT NULL,"
				 "path TEXT NOT NULL);");
}
void homequery::addLibrary(QSqlQuery &query, struc::Library &library) {
	query.prepare("INSERT INTO library VALUES (?,?,?);");
	query.addBindValue(library.uuid);
	query.addBindValue(library.name);
	query.addBindValue(library.path);
	if (!query.exec())
		qWarning() << "addLibrary query failed: " << query.lastError().text();
}
void homequery::deleteLibrary(QSqlQuery &query, QString uuid) {
	query.prepare("DELETE FROM library WHERE library_uuid=?");
	query.addBindValue(uuid);
	if (!query.exec())
		qWarning() << "deleteLibrary query failed:" << query.lastError().text();
}
QList<struc::Library> homequery::getLibraries(QSqlQuery &query) {
	query.exec("SELECT * FROM library;");
	QList<struc::Library> list;
	while (query.next()) {
		QString uuid = query.value(0).toString();
		QString name = query.value(1).toString();
		QString path = query.value(2).toString();
		list.append({uuid, name, path});
	}
	return list;
}


