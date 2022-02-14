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
	Q_PROPERTY(int coverWidth READ getCoverWidth NOTIFY coverWidthChanged)
private:
	QStack<int> navStack;
	int coverWidthIndex = 0;
	int containerType = FolderType;
	struc::Library library;
	QList<struc::Container> folders;
	QList<struc::Book> books;
	QSqlQuery query;

	void scanLibrary();
	int scanLibraryAux (QString path, int parentID);
	void moveThumbNails(QString bookID);
	void updateLibrary();

public:
	enum Roles {
		IDRole = Qt::UserRole,
		NameRole,
		AuthorRole,
		LocationRole,
		HasCoverRole,
		CoverRole
	};
	enum ContainerTypes {
		FolderType,
		AuthorType,
		SubjectType,
		CollectionType
	};

	explicit LibraryModel(QObject *parent = 0);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int getCoverWidth() const;
	QVariant data(const QModelIndex &index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;
signals:
	void coverWidthChanged();
public slots:
	void setLibrary(struc::Library library);
	void setBookLocation(QString newLocation, int row);
	void changeFolder(int folderID);
	bool isFolder(int row) const;
	bool prevFolder();
	QString getFullPath(int row);
};

#endif // LIBRARYMODEL_H
