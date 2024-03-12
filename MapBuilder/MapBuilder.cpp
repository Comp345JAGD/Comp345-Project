#include "MapBuilder.h"
#include <sstream>
#include <fstream>
#include <iostream>

MapBuilder& EditorMapBuilder::setMapId(string mapId) {
	this->mapId = mapId;
	return *this;
}

MapBuilder& EditorMapBuilder::setRowsColumns(int rows, int columns) {
	numRows = rows;
	numColumns = columns;
	return *this;
}

MapBuilder& EditorMapBuilder::setStartCell(int row, int column) {
	startRow = row;
	startColumn = column;
	return *this;
}

MapBuilder& EditorMapBuilder::setEndCell(int row, int column) {
	endRow = row;
	endColumn = column;
	return *this;
}

MapBuilder& EditorMapBuilder::setLevel(int level) {
	this->level = level;
	return *this;
}

GameMap& EditorMapBuilder::build() {

	if (mapId != "") {

		// fetch map from file

		ifstream inputFile("../data/" + mapId + ".txt");

		if (!inputFile.fail()) {
			string line;
			while (inputFile >> line) {
				cout << line << endl;
			}

		}


		
	}


	return GameMap(
		numRows,
		numColumns,
		startRow,
		startColumn,
		endRow,
		endColumn
	);

}

GameMap& LevelMapBuilder::build() {

	GameMap& gameMap = EditorMapBuilder::build();

	// apply level

	return gameMap;

}