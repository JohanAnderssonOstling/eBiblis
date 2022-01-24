#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QDir>
#include <QSqlQuery>
#include <QStack>
#include <structs.h>
class LibraryModel : public QAbstractListModel {
	Q_OBJECT
private:
	QStack<int> navStack;
	int currentFolderID = 0;
	int containerType = FolderType;
	struc::Library library;
	QList<struc::Container> folders;
	QList<struc::Book> books;
	QSqlQuery query;

	void scanLibrary();
	int scanLibraryAux(QSqlQuery &query, QString path, int parentID);
	void updateLibrary();

public:
	enum Roles {
		IDRole = Qt::UserRole,
		NameRole,
		LocationRole
	};
	enum ContainerTypes {
		FolderType,
		AuthorType,
		SubjectType,
		CollectionType
	};

	explicit LibraryModel(QObject *parent = 0);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;
public slots:
	void setLibrary(struc::Library library);
	void setBookLocation(QString newLocation, int row);
	void changeFolder(int folderID);
	bool isFolder(int row);
	bool prevFolder();
	QString getFullPath(int row);
};

#endif // LIBRARYMODEL_H
