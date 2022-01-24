#include <bookparsers.h>
#include <QString>
#include <QStringList>
struc::Book parseEpub(QFileInfo file) {
	struc::Book book;
	book.name = file.fileName();
	book.title = "title";
	book.isbn = "isbn";
	book.description = "desc";
	return book;
}

struc::Book bookparser::parseBook(QFileInfo file) {
	if (file.fileName().endsWith(".epub")) return parseEpub(file);
	return struc::Book();
}
