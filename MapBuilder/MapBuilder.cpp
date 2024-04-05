#include "MapBuilder.h"
#include <sstream>
#include <fstream>
#include <iostream>

MapBuilder* EditorMapBuilder::setMapAsString(string mapAsString) {
	this->mapAsString = mapAsString;
	return this;
}

MapBuilder* EditorMapBuilder::setRowsColumns(int rows, int columns) {
	numRows = rows;
	numColumns = columns;
	return this;
}

MapBuilder* EditorMapBuilder::setStartCell(int row, int column) {
	startRow = row;
	startColumn = column;
	return this;
}

MapBuilder* EditorMapBuilder::setEndCell(int row, int column) {
	endRow = row;
	endColumn = column;
	return this;
}

MapBuilder* EditorMapBuilder::setLevel(int level) {
	this->level = level;
	return this;
}

GameMap* EditorMapBuilder::build() {

	GameMap* gameMap;

	if (mapAsString != "") {

		// fetch map from file

		//cout << mapAsString << endl;
		string line = "";

		stringstream lineStream(mapAsString);

		int numRows = 0;
		int numColumns = 0;

		while (getline(lineStream, line, '$')) {
			numColumns = line.length() / 2;
			numRows++;
		}

		//cout << numRows << endl;
		//cout << numColumns << endl;


		gameMap = new GameMap(
			numRows,
			numColumns,
			0,
			0,
			numRows - 1,
			numColumns - 1
		);



		string lineX = "";

		stringstream lineXStream(mapAsString);

		int row = 0;
		int column = 0;

		while (getline(lineXStream, lineX, '$')) {
			string cell = "";
			stringstream cellStream(lineX);

			column = 0;
			while (getline(cellStream, cell, ',')) {

				//cout << cell << endl;

				if (cell == "S") {
					gameMap->setStartRow(row);
					gameMap->setStartColumn(column);
				}
				else if (cell == "E") {
					gameMap->setEndRow(row);
					gameMap->setEndColumn(column);

				}
				else if (cell == "W") {
					gameMap->setCell(row, column, new WallCell());
				}
				else if (cell == "A") {
					gameMap->setCell(row, column, new Monster("Insect"));
				}
				else if (cell == "F") {
					gameMap->setCell(row, column, new Monster("Goblin"));
				}
				column++;
			}
			row++;
		}
		
	}
	else {
		gameMap = new GameMap(
			numRows,
			numColumns,
			startRow,
			startColumn,
			endRow,
			endColumn);
	}


	return gameMap;

}

GameMap* LevelMapBuilder::build() {

	GameMap* gameMap = EditorMapBuilder::build();

	// apply level

	return gameMap;

}