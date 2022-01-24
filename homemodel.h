#ifndef HOMEMODEL_H
#define HOMEMODEL_H

#include <QAbstractListModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <structs.h>
#include <homequeries.h>
#include <libraryqueries.h>
#include <constants.h>
class HomeModel : public QAbstractListModel {
	Q_OBJECT
private:
	QList<struc::Library> libraryList;
	QSqlQuery query;
public:
	enum Roles {
		UuidRole = Qt::UserRole,
		NameRole,
	};
	explicit HomeModel(QObject *parent = 0);

	void updateLibraryList();
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QHash<int, QByteArray> roleNames() const override;
public slots:
	void addLibrary(QString path);
	struc::Library getLibrary(int row);
	void deleteLibrary(int row);

};

#endif // HOMEMODEL_H
