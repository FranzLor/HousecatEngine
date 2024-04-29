#pragma once

#include <glm/glm.hpp>


//-----------------------------------------------------//
//                  TileAttributes                     //
//  Stores attributes related to tiles in the editor.  //
//  This includes dimensions, scaling, layering, and   //
//  texture coordinates for each tile.                 //
//-----------------------------------------------------//

struct TileAttributes {
	int tileWidth;
	int tileHeight;

	int scaleX;
	int scaleY;

	int layer;
	int offsetX;
	int offsetY;

	int srcRectX;
	int srcRectY;
	int mouseRectX;
	int mouseRectY;

	TileAttributes(int tileWidth = 32, int tileHeight = 32, int scaleX = 1, int scaleY = 1,
		int layer = 0, int offsetX = 0, int offsetY = 0, int srcRectX = 0, int srcRectY = 0,
		int mouseRectX = 32, int mouseRectY = 32) {

		this->tileWidth = tileWidth;
		this->tileHeight = tileHeight;
		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->layer = layer;
		this->offsetX = offsetX;
		this->offsetY = offsetY;
		this->srcRectX = srcRectX;
		this->srcRectY = srcRectY;
		this->mouseRectX = mouseRectX;
		this->mouseRectY = mouseRectY;
	}

	~TileAttributes() = default;
};



/**
 * @file TileAttributes.h
 * @brief Stores and manages attributes for tiles in the Housecat game editor.
 *
 * The TileAttributes struct is designed to hold all necessary properties that define
 * a tile's appearance and placement within the game editor's canvas. It simplifies
 * tile management by encapsulating tile-related attributes in one structure, which
 * can be easily passed around and manipulated within the editor's systems.
 *
 * Key Attributes:
 * - Tile dimensions (width and height)
 * - Scaling factors (X and Y)
 * - Layering information for rendering
 * - Texture coordinates for defining the visible part of the tile
 * - Offset for placement adjustments
 */