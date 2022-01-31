#include <libraryqueries.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <structs.h>
void libraryquery::createDB(QSqlQuery &query) {
	query.exec("CREATE TABLE folder("
				 "folder_id  INTEGER PRIMARY KEY NOT NULL,"
				 "name    TEXT    NOT NULL,"
				 "parent_folder_id INTEGER REFERENCES folder);");

	query.exec("CREATE TABLE book("
				 "book_id  INTEGER PRIMARY KEY,"
				 "name    TEXT    NOT NULL,"
				 "read_location	TEXT	DEFAULT \"0\"	,"
				 "read_percentage INTEGER DEFAULT 0 ,"
				 "title   TEXT,"
				 "isbn    TEXT,"
				 "description TEXT,"
				 "folder_id INTEGER REFERENCES folder);");

	query.exec("CREATE TABLE author("
				 "author_id  INTEGER PRIMARY KEY NOT NULL,"
				 "name    TEXT    NOT NULL);");

	query.exec("CREATE TABLE book_author("
				 "book_uuid INTEGER NOT NULL REFERENCES book,"
				 "author_uuid INTEGER NOT NULL REFERENCES author,"
				 "PRIMARY KEY (book_uuid, author_uuid));");

	query.exec("INSERT INTO folder VALUES (0,\"root\",0);");
	query.exec("INSERT INTO author VALUES (0,\"root\");");
	//query.exec("INSERT INTO folder VALUES (0,\"root\",0);");
}

void libraryquery::addFolder(QSqlQuery &query, struc::Component folder) {
	query.prepare("INSERT INTO folder VALUES (?,?,?);");
	query.addBindValue(folder.id);
	query.addBindValue(folder.name);
	query.addBindValue(folder.parentID);
	query.exec();
}

int libraryquery::addBook(QSqlQuery &query, struc::Book book) {
	query.prepare("INSERT INTO book (name, title, isbn, description, folder_id) "
					"VALUES (:name, :title, :isbn, :description, :folder_id)");
	query.bindValue(":name",book.name);
	query.bindValue(":title",book.title);
	query.bindValue(":isbn",book.isbn);
	query.bindValue(":description",book.description);
	query.bindValue(":folder_id",book.parentID);
	if (!query.exec())
		qWarning() << "addBook query failed:" << query.lastError().text()
					 << query.lastQuery();
	query.exec("SELECT last_insert_rowid()");
	query.next();
	int rowID = query.value(0).toInt();
	return rowID;
}

void libraryquery::addAuthor(QSqlQuery &query) {

}
void libraryquery::setBookFolderID(QSqlQuery &query, QString name, int parentID) {
	query.prepare("UPDATE book SET folder_id = ? "
					"WHERE name = ? AND folder_id = NULL LIMIT 1;");
	query.addBindValue(parentID);
	query.addBindValue(name);
	query.exec();
}
void libraryquery::setBookLocation(QSqlQuery &query, QString location, int bookID) {
	query.prepare("UPDATE book SET read_location = ? WHERE book_id = ?");
	query.addBindValue(location);
	query.addBindValue(bookID);
	query.exec();
}
bool libraryquery::bookExists(QSqlQuery &query, QString name) {
	query.prepare("SELECT COUNT(*) FROM book WHERE name=?;");
	query.addBindValue(name);

	if (!query.exec())
		qWarning() << "bookExists query failed:" << query.lastError().text();
	query.next();
	return query.value(0).toInt() > 0;
}
QList<struc::Book> libraryquery::getBooks(QSqlQuery &query, int parentID) {
	query.prepare("SELECT COUNT(*) FROM book WHERE folder_id = ?;");
	query.addBindValue(parentID);
	query.exec();
	query.next();
	QList<struc::Book> books(query.value(0).toInt()); //Get number of books

	query.prepare("SELECT * FROM book WHERE folder_id = ?;");
	query.addBindValue(parentID);
	if (!query.exec())
		qWarning() << "getBooks query failed: " << query.lastError().text();

	for (int i = 0; i < books.size(); i++) {
		query.next();
		books[i] = struc::Book();
		books[i].id = query.value(0).toInt();
		books[i].name = query.value(1).toString();
		books[i].location = query.value(2).toString();
		books[i].percentage = query.value(3).toInt();
		books[i].title = query.value(4).toString();
		books[i].isbn = query.value(5).toString();
		books[i].description = query.value(6).toString();
		books[i].parentID = query.value(7).toInt();
	}
	return books;
}
QList<struc::Container> libraryquery::getFolders(QSqlQuery &query, int parentID) {
	query.prepare("SELECT COUNT(*) FROM folder WHERE parent_folder_id= ? AND NOT folder_id = 0");
	query.addBindValue(parentID);
	query.exec();
	query.next();
	QList<struc::Container> folders(query.value(0).toInt());

	query.prepare("SELECT * FROM folder WHERE parent_folder_id= ? AND NOT folder_id = 0;");
	query.addBindValue(parentID);
	if (!query.exec())
		qWarning() << "getFolders query failed: " << query.lastError().text();

	for (int i = 0; i < folders.size(); i++) {
		query.next();
		folders[i] = struc::Container();
		folders[i].id = query.value(0).toInt();
		folders[i].name = query.value(1).toString();
		folders[i].parentID = query.value(2).toInt();
	}
	return folders;
}
QString libraryquery::getFolderPath(QSqlQuery &query, int folderID) {
	query.prepare("SELECT name, parent_folder_id FROM folder WHERE folder_id = ?");
	query.addBindValue(folderID);
	query.exec();
	query.next();
	QString name = query.value(0).toString();
	int parentFolderID = query.value(1).toInt();

	if (parentFolderID == 0) return name + "/";
	return getFolderPath(query, parentFolderID) + "/" + name + "/";
}

