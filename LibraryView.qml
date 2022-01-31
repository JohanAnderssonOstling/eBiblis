import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1


ColumnLayout{
	property bool showAddButton: false
	property bool showBackButton: true

	property string title: "Library"
	function backButtonPressed(){
		if (!LibraryModel.prevFolder())
			stackView.pop();
	}
	function componentClicked(model){
		if (LibraryModel.isFolder(model.index)){
			LibraryModel.changeFolder(model.id);
		}
		else{
			var path = LibraryModel.getFullPath(model.index);
			epubReader.row = model.index;
			epubReader.title = model.name
			epubReader.setBookUrl(path, model.location);
			stackView.push(epubReader);
		}
	}

	GridView{
		id: libraryGrid
		Layout.fillWidth: true
		Layout.fillHeight: true
		property int elementsPerRow: (width / 500)
		cellWidth: 500 + ((width % 500.0) / (elementsPerRow))
		cellHeight: 840
		clip:true
		model: LibraryModel
		focus: true
		ScrollBar.vertical: ScrollBar{}
		delegate:Item{

			Column{
			x: (libraryGrid.cellWidth - 500)/ 2
			width: 500
			height: 840

			Rectangle{
				id: coverPlaceHolder
				visible: !model.hasCover

				width: 500
				height: 660
				color: "cornflowerblue"
				MouseArea{
					anchors.fill: parent
					onClicked: componentClicked(model)
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
			Image{

				id: cover
				visible: model.hasCover
				source: "file://" + model.cover
				asynchronous: true
				Rectangle{
					anchors.fill: parent
					color:"transparent"
					border.width: 1
					border.color: "lightgray"
				}
				MouseArea{
					anchors.fill: parent
					onClicked: componentClicked(model)
				}
			}


			Text{
				width: 500
				visible: model.hasCover
				text:model.name
				horizontalAlignment: Text.AlignHCenter

				elide: Text.ElideRight
			}
			Text{
				width: 500
				visible: model.hasCover
				text: "author"
				horizontalAlignment: Text.AlignHCenter
			}
		}
	}}
}
