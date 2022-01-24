#include "librarymodel.h"
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QString>
#include <QUrl>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <bookparsers.h>
#include <libraryqueries.h>
#include <constants.h>
LibraryModel::LibraryModel(QObject *parent) : QAbstractListModel {parent} {

}
void LibraryModel::scanLibrary() {

	QSqlDatabase db = QSqlDatabase::database(library.uuid);
	db.transaction();
	scanLibraryAux(query, QUrl(library.path).toLocalFile(), 0);
	db.commit();
	changeFolder(0);
}
int LibraryModel::scanLibraryAux(QSqlQuery &query, QString path, int parentID) {
	QDirIterator iterator(path, QDir::NoDotAndDotDot | QDir::AllEntries);
	int currentFolderID = parentID;
	while (iterator.hasNext()) {
		QFileInfo file(iterator.next());

		if (file.isDir()) {
			currentFolderID++;
			struc::Container newFolder = {currentFolderID, file.fileName(), parentID};
			libraryquery::addFolder(query, newFolder);
			currentFolderID = scanLibraryAux(query, file.absoluteFilePath(), currentFolderID);

		} else if (file.fileName().endsWith(".epub")) {
			if (libraryquery::bookExists(query, file.fileName()))
				libraryquery::setBookFolderID(query, file.fileName(), parentID);

			else {
				struc::Book newBook = bookparser::parseBook(file);
				newBook.parentID = parentID;
				libraryquery::addBook(query, newBook);
			}
		}
	}
	return currentFolderID;
}
int LibraryModel::rowCount(const QModelIndex &parent) const {
	return folders.size() + books.size();
}

QVariant LibraryModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	if (row < folders.size()) {
		switch(role) {
			case IDRole: return folders.at(row).id;
			case NameRole: return folders.at(row).name;
		}
	} else {
		row -= folders.size();
		struc::Book book(books.at(row));
		switch(role) {
			case IDRole: return book.id;
			case NameRole: return (book.title != "title") ? book.title : book.name;
			case LocationRole: return book.location;
		}
	}
	return "";
}

QHash<int, QByteArray> LibraryModel::roleNames() const {
	static QHash<int, QByteArray> mapping {
		{IDRole, "id"},
		{NameRole, "name"},
		{LocationRole, "location"}
	};
	return mapping;
}
void LibraryModel::setLibrary(struc::Library library) {

	this->library = library;
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE",library.uuid);
	db.setDatabaseName(constant::libraryDir + library.uuid + ".db");
	db.open();
	query = QSqlQuery(db);
	scanLibrary();
}
void LibraryModel::setBookLocation(QString newLocation, int row) {
	row -= folders.size();
	books[row].location = newLocation;
	emit dataChanged(index(row), index(row));
	libraryquery::setBookLocation(query, newLocation, books.at(row).id);
}
void LibraryModel::changeFolder(int folderID) {
	beginResetModel();
	books = libraryquery::getBooks(query, folderID);
	folders = libraryquery::getFolders(query, folderID);
	endResetModel();
	navStack.push(folderID);
}
bool LibraryModel::isFolder(int row) {
	return row < folders.size();
}
bool LibraryModel::prevFolder() {

	if (navStack.size() == 1) return false;
	navStack.pop();
	changeFolder(navStack.pop());
	qInfo() << navStack.top() << navStack.size();
	return true;
}
QString LibraryModel::getFullPath(int row) {

	int parentID = (isFolder(row)) ? folders.at(row).parentID : books.at(row - folders.size()).parentID;
	QString name = (isFolder(row)) ? folders.at(row).name : books.at(row - folders.size()).name;
	if (parentID == 0) return library.path + "/" + name;
	return library.path + "/" + libraryquery::getFolderPath(query, parentID) + name;
}
