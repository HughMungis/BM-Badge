#include "mage_tileset.h"
#include "EngineROM.h"
#include "EnginePanic.h"

MageTileset::MageTileset(uint32_t address)
{
	uint32_t tileCount = 0;

	EngineROM_Read(
		address,
		16,
		(uint8_t *)name,
		"Failed to load MageTileset property 'name'"
	);

	name[16] = 0; // Null terminate
	address += 16;

	EngineROM_Read(
		address,
		sizeof(imageId),
		(uint8_t *)&imageId,
		"Failed to load MageTileset property 'imageId'"
	);
	imageId = ROM_ENDIAN_U2_VALUE(imageId);
	address += sizeof(imageId);

	EngineROM_Read(
		address,
		sizeof(imageWidth),
		(uint8_t *)&imageWidth,
		"Failed to load MageTileset property 'imageWidth'"
	);
	imageWidth = ROM_ENDIAN_U2_VALUE(imageWidth);
	address += sizeof(imageWidth);

	EngineROM_Read(
		address,
		sizeof(imageHeight),
		(uint8_t *)&imageHeight,
		"Failed to load MageTileset property 'imageHeight'"
	);
	imageHeight = ROM_ENDIAN_U2_VALUE(imageHeight);
	address += sizeof(imageHeight);

	EngineROM_Read(
		address,
		sizeof(tileWidth),
		(uint8_t *)&tileWidth,
		"Failed to load MageTileset property 'tileWidth'"
	);
	tileWidth = ROM_ENDIAN_U2_VALUE(tileWidth);
	address += sizeof(tileWidth);

	EngineROM_Read(
		address,
		sizeof(tileHeight),
		(uint8_t *)&tileHeight,
		"Failed to load MageTileset property 'tileHeight'"
	);
	tileHeight = ROM_ENDIAN_U2_VALUE(tileHeight);
	address += sizeof(tileHeight);

	EngineROM_Read(
		address,
		sizeof(cols),
		(uint8_t *)&cols,
		"Failed to load MageTileset property 'cols'"
	);
	cols = ROM_ENDIAN_U2_VALUE(cols);
	address += sizeof(cols);

	EngineROM_Read(
		address,
		sizeof(rows),
		(uint8_t *)&rows,
		"Failed to load MageTileset property 'rows'"
	);
	rows = ROM_ENDIAN_U2_VALUE(rows);
	address += sizeof(rows);

	address += sizeof(padding);

	tileCount = rows * cols;
	globalGeometryIds = std::make_unique<uint16_t[]>(tileCount);

	EngineROM_Read(
		address,
		tileCount * sizeof(uint16_t),
		(uint8_t *)globalGeometryIds.get(),
		"Failed to load MageTileset property 'globalGeometryIds'"
	);

	return;
}

std::string MageTileset::Name() const
{
	return std::string(name);
}

uint16_t MageTileset::ImageId() const
{
	return imageId;
}

uint16_t MageTileset::ImageWidth() const
{
	return imageWidth;
}

uint16_t MageTileset::ImageHeight() const
{
	return imageHeight;
}

uint16_t MageTileset::TileWidth() const
{
	return tileWidth;
}

uint16_t MageTileset::TileHeight() const
{
	return tileHeight;
}

uint16_t MageTileset::Cols() const
{
	return cols;
}

uint16_t MageTileset::Rows() const
{
	return rows;
}

uint16_t MageTileset::Count() const
{
	return rows*cols;
}

uint8_t MageTileset::Tileset(uint32_t index) const
{
	if (!globalGeometryIds) return 0;

	uint32_t tileCount = rows * cols;

	if (tileCount > index)
	{
		return globalGeometryIds[index];
	}

	return 0;
}

uint32_t MageTileset::Size() const
{
	return 16 + (sizeof(uint16_t) * 7) + (rows * cols);
}

bool MageTileset::Valid() const
{
	if (imageWidth < 1) return false;
	if (imageHeight < 1) return false;
	if (tileWidth < 1) return false;
	if (tileHeight < 1) return false;
	if (cols < 1) return false;
	if (rows < 1) return false;

	return true;
}
