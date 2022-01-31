#include "ioutil.h"
#include <QDir>

void ioutil::clearDir(QDir dir) {
	for(QString file : dir.entryList())
		dir.remove(file);
}
void ioutil::clearDir(QString dir) {
	clearDir(QDir(dir));
}
