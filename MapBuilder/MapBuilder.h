#include "../Map/gameMap.h"
#include <string>
using namespace std;

#ifndef MAPBUILDER_H
#define MAPBUILDER_H

class MapBuilder
{
public:
	virtual MapBuilder& setMapId(string mapId) = 0;
	virtual MapBuilder& setRowsColumns(int rows, int columns) = 0;
	virtual MapBuilder& setStartCell(int row, int column) = 0;
	virtual MapBuilder& setEndCell(int row, int column) = 0;
	virtual MapBuilder& setLevel(int level) = 0;
	virtual GameMap& build() = 0;
};

class EditorMapBuilder : public MapBuilder
{
private:
	string mapId = "";
	int level = 10;
	int numRows = 2;
	int numColumns = 2;
	int startRow = 0;
	int startColumn = 0;
	int endRow = 1;
	int endColumn = 1;
public:
	MapBuilder& setMapId(string mapId) override;
	MapBuilder& setRowsColumns(int rows, int columns) override;
	MapBuilder& setStartCell(int row, int column) override;
	MapBuilder& setEndCell(int row, int column) override;
	MapBuilder& setLevel(int level) override;
	GameMap& build() override;
};

class LevelMapBuilder : public EditorMapBuilder
{
public:
	GameMap& build() override;
};

#endif