#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
#include <QStandardPaths>

namespace constant {
const QString appDir = QStandardPaths::writableLocation
						 (QStandardPaths::AppDataLocation) + "/BookManager/";

const QString webDir = appDir + "web/";

const QString dataDir = appDir + "data/";
const QString libraryDir = dataDir + "library/";

const QString mediaDir = appDir + "media/";
const QString thumbnailDir = mediaDir + "thumbnail/";
}
#endif // CONSTANTS_H
