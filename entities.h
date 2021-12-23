#include <stdlib.h>

struct entity
{
	int EntityType;
	int EntityID;
	char EntityRepresentation;
	char ForegroundColor, BackgroundColor;
	int EntityRarityMultiplier;
	int hp, atk, def, critchance;
	int MovementSpeed;
	int PositionX, PositionY;
  // Optional (/special) attributes
  int maxHp;
  char TrailRepresentation;
  char TrailForegroundColor, TrailBackgroundColor;
  char StatusEffect;

} GenericEntity, Slime, BlueSlime, Chest, Door, Skeleton, ItemEntity, PlayerEntity;

enum EntityID
{
	SLIME        = 0,
	BLUE_SLIME   = 1
};

enum EntityType
{
	ENEMY        = 0,
	ITEM         = 1,
	CHEST        = 2,
	TRANSPORTER  = 3,
	NPC          = 4,
	GENERIC      = 5
};

enum EntityConsts
{
	PLAYER = 255
};
