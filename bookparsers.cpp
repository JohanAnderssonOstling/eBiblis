#include <bookparsers.h>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QXmlStreamReader>
#include <QStandardPaths>
#include <QImage>
#include <quazip.h>
#include <quazipfile.h>
#include <JlCompress.h>
#include "constants.h"


QString getOPFPath(QString archivePath) {
	QString containerPath = "META-INF/container.xml";
	JlCompress::extractFile(archivePath, containerPath, constant::tempDir + containerPath);
	QFile containerFile(constant::tempDir + containerPath);
	containerFile.open(QIODevice::ReadOnly);
	QXmlStreamReader reader(&containerFile);

	while(reader.readNextStartElement()) {
		if (reader.name() == QString("rootfile")) {
			QXmlStreamAttributes attributes = reader.attributes();
			QString opfPath = attributes.value("full-path").toString();
			if (opfPath != "")
				return opfPath;
		}
	}
	containerFile.close();
	return "";
}
void createThumbNails(QString archivePath, QString coverPath) {
	JlCompress::extractFile(archivePath, coverPath, constant::tempDir + coverPath);
	QString coverExtension = coverPath.split(".").last();
	QImage cover(constant::tempDir + coverPath);

	for (int width : constant::coverWidths) {
		double scaling = width / (double) cover.width();
		int height = (int) (scaling * cover.height());
		QImage thumbNail = cover.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		thumbNail.save(constant::tempDir + "thumbnail/" + QString::number(width) +"." + coverExtension);
	}
}

struc::Book parseEpub(QFileInfo file) {
	struc::Book book;
	book.name = file.fileName();

	QString archivePath = file.absoluteFilePath();
	QString opfPath = getOPFPath(file.absoluteFilePath());
	QStringList opfPathFiles = opfPath.split("/");
	QString opfDirPath = "";

	if (opfPathFiles.length() > 1) {
		for (int i = 0; i < opfPathFiles.length() - 1; i++) {
			opfDirPath = opfDirPath + opfPathFiles.at(i) + "/";
		}
	}
	JlCompress::extractFile(archivePath, opfPath, constant::tempDir + opfPath);
	QFile opfFile(constant::tempDir + opfPath);
	opfFile.open(QIODevice::ReadOnly);
	QXmlStreamReader reader(&opfFile);
	QString coverPath;
	while(!reader.atEnd()) {
		QString name = reader.name().toString();
		QXmlStreamAttributes attributes = reader.attributes();
		if (name == "title") book.title = reader.readElementText();
		else if (name == "creator") book.authors.append(reader.readElementText());
		else if (name == "description") book.description = reader.readElementText();
		else if (name == "publisher");
		else if (name == "identifier") book.isbn = reader.readElementText();
		else if (name == "item" && coverPath == "") {
			QString id = attributes.value("id").toString();
			QString hrefValue = attributes.value("href").toString();

			if (id.contains("cover-image") || id.contains("cover_image") || id.contains("cover-img"))
				coverPath = opfDirPath + hrefValue;
			else if (id == "cover") {

				for (QString coverExtension : constant::coverExtensions)
					if (hrefValue.contains(coverExtension)) {
						coverPath = opfDirPath + hrefValue;
						break;
					}
			}
		}
		reader.readNextStartElement();
	}
	opfFile.close();
	if (coverPath != "") {
		createThumbNails(archivePath, coverPath);
	}
	return book;
}


struc::Book bookparser::parseBook(QFileInfo file) {

	if (file.fileName().endsWith(".epub")) return parseEpub(file);
	return struc::Book();
}

