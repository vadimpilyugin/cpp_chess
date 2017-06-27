#pragma once

struct Tile
{
	int x;
	int y;
	Tile (int x_ = 0, int y_ = 0): x (x_), y (y_) {}
    bool operator==(const Tile& tile)const{
        return x==tile.x && y==tile.y;
    }
};
