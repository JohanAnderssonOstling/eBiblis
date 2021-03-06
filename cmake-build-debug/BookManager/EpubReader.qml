import QtQuick
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard
import QtWebView 1.1
import QtQuick.Layouts 1.3
ColumnLayout{
	property bool showAddButton: false
	property bool showBackButton: true

	property int bookID;
	property int row;

	property string title
	function backButtonPressed(){
		epubWebView.runJavaScript("getEpubCfi();", function(epubCfi){
					LibraryModel.setBookLocation(epubCfi, row);
				});
		stackView.pop();
	}
	function setBookUrl(bookUrl, epubCfi){
		var functionCall = "setBook(\"" + bookUrl +"\", \""+ epubCfi +"\");";
		epubWebView.runJavaScript(functionCall);
	}

	WebView{
		id:epubWebView
		Layout.fillWidth: true
		Layout.fillHeight: true
		url: "file://" + webPath + "epubReader.html"
		Keys.onRightPressed: epubWebView.runJavaScript("nextPage();", function(location){
			LibraryModel.setBookLocation(location, row);
		});
		Keys.onLeftPressed: epubWebView.runJavaScript("prevPage()", function(location){
			LibraryModel.setBookLocation(location, row);
		});

	}
}
