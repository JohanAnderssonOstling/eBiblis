#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
#include <QStandardPaths>

namespace constant {

const int thumbnailWidths[] = {250,500,1000};

const QString appDir = QStandardPaths::writableLocation
						 (QStandardPaths::AppDataLocation) + "/eBiblis/";
const QString tempDir = appDir + "temp/";

const QString webDir = appDir + "web/";

const QString dataDir = appDir + "data/";
const QString libraryDir = dataDir + "library/";

const QString mediaDir = appDir + "media/";
const QString thumbnailDir = mediaDir + "thumbnail/";

const QString coverExtensions[] = {".png", ".jpg", ".jpeg"};

}
#endif // CONSTANTS_H
