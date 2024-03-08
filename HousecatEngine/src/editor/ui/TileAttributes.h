#pragma once

#include <glm/glm.hpp>

struct TileAttributes {
	int tileWidth;
	int tileHeight;
	int scaleX;
	int scaleY;
	int layer;
	glm::vec2 tileOffset;
	int srcRectX;
	int srcRectY;

	//TODO
	//animated tiles

	TileAttributes(int tileWidth = 16, int tileHeight = 16, int scaleX = 1, int scaleY = 1, int layer = 0, glm::vec2 tileOffset = { 0, 0 }, int srcRectX = 0, int srcRectY = 0) {
		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->layer = layer;
		this->tileOffset = tileOffset;
		this->srcRectX = srcRectX;
		this->srcRectY = srcRectY;
	}

	~TileAttributes() = default;
};