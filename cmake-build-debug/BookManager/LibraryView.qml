import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
ColumnLayout{
	property bool showAddButton: false
	property bool showBackButton: true

	property string title: "Home"
	function backButtonPressed(){
		if (!LibraryModel.prevFolder())
			stackView.pop();
	}

	GridView{
		id: libraryGrid
		Layout.fillWidth: true
		Layout.fillHeight: true
		cellWidth: 210 + ((width % 210) / (width / 210))
		cellHeight: 330
		clip:true
		model: LibraryModel
		focus: true
		delegate:Column{
			Rectangle{
				x: (libraryGrid.cellWidth - 200)/ 2
				width: 200
				height: 300
				color: "cornflowerblue"
				MouseArea{
					anchors.fill: parent
					onClicked: {
						if (LibraryModel.isFolder(model.index)){
							LibraryModel.changeFolder(model.id);
						}
						else{
							var path = LibraryModel.getFullPath(model.index);
							epubReader.row = model.index;
							epubReader.setBookUrl(path, model.location);
							stackView.push(epubReader);
						}
					}
					Text{
						color: "white"
						anchors.fill: parent
						anchors.horizontalCenter: parent.horizontalCenter
						elide: Label.ElideRight
						wrapMode: Text.Wrap
						text: model.name
					}
				}
			}
		}
	}
}
