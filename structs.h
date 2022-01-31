#ifndef STRUCTS_H
#define STRUCTS_H

#include <QVector>
#include <QString>
namespace struc {

struct Library {
	QString uuid;
	QString name;
	QString path;
};

struct Component {
	int id;
	QString name;
	int parentID;
};

struct Book : Component {
	QString location;
	int percentage;
	QString author;
	QString title;
	QString isbn;
	QString description;
};
struct Container : Component {

};
}
#endif // STRUCTS_H
