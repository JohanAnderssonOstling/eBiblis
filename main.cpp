#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebView/QtWebView>
#include <QQuickWindow>
#include <QDebug>
#include <iostream>
#include <QQmlContext>
#include "fileIO.h"
#include <QtSql>
#include <QSqlDriver>
#include <QApplication>
#include <homemodel.h>
#include <librarymodel.h>
#include <constants.h>
void testarchive() {


}


void createDirs() {
	QDir(constant::appDir).mkpath(".");
	QDir(constant::webDir).mkpath(".");
	QDir(constant::dataDir).mkpath(".");
	QDir(constant::libraryDir).mkpath(".");
	QDir(constant::mediaDir).mkpath(".");
	QDir(constant::thumbnailDir).mkpath(".");
}
void setContextProperties(QQmlContext context) {
	context.setContextProperty("webDir", constant::webDir);
}

int main(int argc, char *argv[]) {
	//qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

	//Qml boilerplate
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
	QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);
	//QGuiApplication app(argc, argv);
	QApplication app(argc, argv);
	QtWebView::initialize();

	QQmlApplicationEngine engine;
	const QUrl url(u"qrc:/BookManager/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
	&app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	createDirs();
	setContextProperties(engine.rootContext());
	qInfo() << constant::appDir;
	HomeModel homeModel(0);
	LibraryModel libraryModel(0);
	engine.rootContext()->setContextProperty("HomeModel", &homeModel);
	engine.rootContext()->setContextProperty("LibraryModel", &libraryModel);
	engine.rootContext()->setContextProperty("webPath", constant::webDir);
	testarchive();

	return app.exec();
}


