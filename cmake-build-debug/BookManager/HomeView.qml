import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1

ColumnLayout {
	FolderDialog{
		id: addLibraryFolderDialog
		options: FolderDialog.ShowDirsOnly
		currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
		onAccepted: HomeModel.addLibrary(addLibraryFolderDialog.folder)
	}
	property bool showAddButton: true
	property bool showBackButton: false

	property string title: "Home"
	function addButtonPressed(){
		addLibraryFolderDialog.open();
		homeGrid.focus = true
	}
	GridView {
		id: homeGrid
		Layout.fillWidth: true
		Layout.fillHeight: true
		cellWidth: 260
		cellHeight: 330
		focus: true
		activeFocusOnTab: true
		model: HomeModel
		highlight: Rectangle { color: "lightblue" }
		delegate:
				Column{
			Rectangle{
				anchors.horizontalCenter: parent.horizontalCenter
				width: 200
				height: 300
				color: "lightblue"
				MouseArea{
					anchors.fill: parent
					acceptedButtons: Qt.LeftButton | Qt.RightButton
					onClicked: {
						if (mouse.button & Qt.LeftButton){
							var library = HomeModel.getLibrary(model.index);
							LibraryModel.setLibrary(library)
							stackView.push(libraryView)
						}
						else if (mouse.button & Qt.RightButton){
							HomeModel.deleteLibrary(model.index);
						}

					}

				}
			}
			Label{
				anchors.horizontalCenter: parent.horizontalCenter
				elide: Text.ElideRight
				text: model.name
			}
		}
		Keys.onDeletePressed:{
			HomeModel.deleteLibrary(homeGrid.currentIndex)
		}
		Keys.onReturnPressed: {
			LibraryModel.setLibrary(HomeModel.getLibrary(homeGrid.currentIndex))
			stackView.push(libraryView)
		}

	}
	Text{
		text: homeGrid.focus ? "focus" : "not focus"
	}

}


