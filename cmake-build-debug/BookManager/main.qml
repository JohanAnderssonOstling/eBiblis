import QtQuick
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard
import QtWebView 1.1
import QtQuick.Layouts 1.3
Window {
	id: window
	width: 640
	height: 480
	visible: true
	title: qsTr("Hello World")

	ColumnLayout{
		anchors.fill:parent
		ToolBar{
			Layout.alignment: Qt.AlignTop
			Layout.fillWidth: true
			RowLayout{
				anchors.fill: parent
				ToolButton{
					visible: stackView.currentItem.showBackButton
					text: "<"
					onClicked: stackView.currentItem.backButtonPressed();
				}
				Label{
					Layout.alignment: Qt.AlignCenter
					text: stackView.currentItem.title
					elide: Label.ElideRight
					anchors.verticalCenter: parent.verticalCenter
					anchors.horizontalCenter: parent.horizontalCenter
				}
				ToolButton{
					visible: stackView.currentItem.showAddButton;
					text: "+"
					Layout.alignment: Qt.AlignRight
					onClicked:{
						stackView.currentItem.addButtonPressed();
					}
				}
			}
		}
		StackView{

			id: stackView
			Layout.fillWidth: true
			Layout.fillHeight: true
			initialItem: homeView
			focus: false
			LibraryView{
				id: libraryView
			}

			HomeView{
				id: homeView
			}
			EpubReader{
				id: epubReader
			}


		}

	}


}


