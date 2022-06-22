#include "librarymodel.h"
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QString>
#include <QUrl>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <bookparsers.h>
#include "libraryqueries.h"
#include "constants.h"
#include "ioutil.h"
LibraryModel::LibraryModel(QObject *parent) : QAbstractListModel {parent} {

}
void LibraryModel::scanLibrary() {

	QSqlDatabase db = QSqlDatabase::database(library.uuid);
	db.transaction();
	scanLibraryAux(QUrl(library.path).toLocalFile(), 0);
	db.commit();
	navStack.clear();
	changeFolder(0);
}
int LibraryModel::scanLibraryAux(QString path, int parentID) {
	QDirIterator iterator(path, QDir::NoDotAndDotDot | QDir::AllEntries);
	int currentFolderID = parentID;
	while (iterator.hasNext()) {
		QFileInfo file(iterator.next());
		if (file.isDir()) {
			currentFolderID++;
			struc::Container newFolder = {currentFolderID, file.fileName(), parentID};
			libraryquery::addFolder(query, newFolder);
			currentFolderID = scanLibraryAux(file.absoluteFilePath(), currentFolderID);
		} else if (file.fileName().endsWith(".epub")) {
			if (libraryquery::bookExists(query, file.fileName())) {
				libraryquery::setBookFolderID(query, file.fileName(), parentID);
			} else {
				struc::Book newBook = bookparser::parseBook(file);
				newBook.parentID = parentID;
				QString bookID = QString::number(libraryquery::addBook(query, newBook));
				moveThumbNails(bookID);
			}
		}
	}
	return currentFolderID;
}
void LibraryModel::moveThumbNails(QString bookID) {
	QDir thumbDir(constant::thumbnailDir + library.uuid + "/" + bookID);
	thumbDir.mkpath(".");
	ioutil::clearDir(thumbDir);

	for (int width : constant::coverWidths) {
		QString sourcePath = constant::tempDir + "thumbnail/" + QString::number(width);
		QString destPath = thumbDir.absolutePath() + "/" +QString::number(width);
		for (QString coverExtension : constant::coverExtensions) {
			if (QFile::exists(sourcePath + coverExtension)) {
				QFile::copy(sourcePath + coverExtension, destPath + coverExtension);
			}
		}
	}
	ioutil::clearDir(constant::tempDir + "thumbnail/");
}
int LibraryModel::rowCount(const QModelIndex &parent) const {
	return folders.size() + books.size();
}
int LibraryModel::getCoverWidth() const {
	return constant::coverWidths[coverWidthIndex];
}
QVariant LibraryModel::data(const QModelIndex &index, int role) const {

	int row = index.row();
	if (isFolder(row)) {
		struc::Container folder(folders.at(row));
		switch(role) {
			case IDRole: return folder.id;
			case NameRole: return folder.name;
			case HasCoverRole: return false;
		}
	} else {
		row -= folders.size();
		struc::Book book(books.at(row));
		QString thumbnailPath = constant::thumbnailDir + library.uuid + "/" +
								QString::number(book.id) + "/" +
								QString::number(constant::coverWidths[coverWidthIndex]);
		switch(role) {
			case IDRole: return book.id;
			case NameRole: return (book.title != "title") ? book.title : book.name;
			case AuthorRole: return book.authors.join("\n");
			case LocationRole: return book.location;
			case HasCoverRole:
				for (QString coverExtension : constant::coverExtensions)
					if (QFile::exists(thumbnailPath + coverExtension)) return true;
				return false;
			case CoverRole:
				for (QString coverExtension : constant::coverExtensions)
					if (QFile::exists(thumbnailPath + coverExtension))
						return thumbnailPath + coverExtension;
		}
	}
	return "";
}

QHash<int, QByteArray> LibraryModel::roleNames() const {
	static QHash<int, QByteArray> mapping {
		{IDRole, "id"},
		{NameRole, "name"},
		{LocationRole, "location"},
		{HasCoverRole, "hasCover"},
		{CoverRole, "cover"},
		{AuthorRole, "author"}
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
	libraryquery::setBookLocation(query, newLocation, books.at(row).id);
}
void LibraryModel::changeFolder(int folderID) {
	beginResetModel();
	books = libraryquery::getBooks(query, folderID);
	folders = libraryquery::getFolders(query, folderID);
	endResetModel();
	navStack.push(folderID);
}
bool LibraryModel::isFolder(int row) const {
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
	int bookRow = row - folders.size();
	int parentID = (isFolder(row)) ? folders.at(row).parentID : books.at(bookRow).parentID;
	QString name = (isFolder(row)) ? folders.at(row).name : books.at(bookRow).name;
	if (parentID == 0) return library.path + "/" + name;
	return library.path + "/" + libraryquery::getFolderPath(query, parentID) + name;
}
