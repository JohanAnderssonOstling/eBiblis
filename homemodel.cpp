#include "homemodel.h"
#include <QDebug>
#include <QUuid>
#include <QString>
#include <QSqlError>
#include <QFile>
#include <homequeries.h>
#include <libraryqueries.h>

HomeModel::HomeModel(QObject *parent) : QAbstractListModel {parent} {
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "home");
	db.setDatabaseName(constant::dataDir + "home.db");
	db.open();
	query = QSqlQuery(db);
	homequery::createDB(query);
	updateLibraryList();
}
void HomeModel::addLibrary(QString path) {
	qDebug() << path;
	QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
	QString name = path.split("/").last();
	struc::Library library {uuid, name, path};
	homequery::addLibrary(query, library);

	//Put database object and query in outer scope so that they are destroyed when
	//database is removed
	{
		QSqlDatabase libraryDB = QSqlDatabase::addDatabase("QSQLITE", uuid);
		libraryDB.setDatabaseName(constant::libraryDir + uuid + ".db");
		qInfo() << libraryDB.databaseName();
		libraryDB.open();
		QSqlQuery libraryQuery(libraryDB);
		libraryquery::createDB(libraryQuery);
		libraryDB.close();
	}
	QSqlDatabase::removeDatabase(uuid);

	beginInsertRows(QModelIndex(), libraryList.size(), libraryList.size());
	libraryList.append(library);
	endInsertRows();
}
struc::Library HomeModel::getLibrary(int row) {
	qInfo() << "Select:" << row;
	return libraryList.at(row);
}
void HomeModel::deleteLibrary(int row) {
	homequery::deleteLibrary(query, libraryList.at(row).uuid);
	QFile libraryDBFile(constant::libraryDir  + libraryList.at(row).uuid + ".db");
	if (libraryDBFile.exists()) libraryDBFile.remove();

	beginRemoveRows(QModelIndex(), row, row);
	libraryList.removeAt(row);
	endRemoveRows();
}
void HomeModel::updateLibraryList() {
	beginInsertRows(QModelIndex(), 0, 0);
	libraryList = homequery::getLibraries(query);
	endInsertRows();
}
int HomeModel::rowCount(const QModelIndex &parent) const {
	if (parent.isValid()) return 0;
	return libraryList.size();
}
QVariant HomeModel::data(const QModelIndex &index, int role) const {
	switch(role) {
		case UuidRole: return libraryList.at(index.row()).uuid;
		case NameRole: return libraryList.at(index.row()).name;
	}
	return "";
}
QHash<int, QByteArray> HomeModel::roleNames() const {
	static QHash<int, QByteArray> mapping {
		{UuidRole, "uuid"},
		{NameRole, "name"},
	};
	return mapping;
}
