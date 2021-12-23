// Should I write AIs as being properties of structs?
// Or should structs be parameters to pass towards AIs
struct entity Slime2, BlueSlime2;

void InitializeEntities()
{
	// EMPTY
	{
		GenericEntity.EntityType = ENEMY;
		GenericEntity.EntityID = 0;
		GenericEntity.EntityRepresentation = ' ';
		GenericEntity.ForegroundColor = FGC1;
		GenericEntity.BackgroundColor = BGC1;
		GenericEntity.EntityRarityMultiplier = 0;
		GenericEntity.hp = 0;
		GenericEntity.def = 0;
		GenericEntity.atk = 0;
		GenericEntity.critchance = 0;
		GenericEntity.MovementSpeed = 0;
		GenericEntity.PositionX = 10;
		GenericEntity.PositionY = 10;
	}

	// PLAYER ENTITY
	{

		PlayerEntity.EntityType = PLAYER;
		PlayerEntity.EntityID = PLAYER;
		PlayerEntity.EntityRepresentation = '@';
		PlayerEntity.ForegroundColor = FGC3;
		PlayerEntity.BackgroundColor = BGC1;
		PlayerEntity.EntityRarityMultiplier = 0;
		PlayerEntity.hp = 20;
		PlayerEntity.def = 0;
		PlayerEntity.atk = 1;
		PlayerEntity.critchance = 1;
		PlayerEntity.MovementSpeed = 37;
		PlayerEntity.PositionX = 10;
		PlayerEntity.PositionY = 10;

    // Non-standard attributes;
    PlayerEntity.maxHp = 20;
    PlayerEntity.TrailRepresentation  = '.';
    PlayerEntity.TrailForegroundColor = FGC5;
    PlayerEntity.TrailBackgroundColor = BGC1;
	}
	// Slime
	{
		Slime.EntityType = ENEMY;
		Slime.EntityID = SLIME;
		Slime.EntityRepresentation = '#';
		Slime.ForegroundColor = 0x5;
		Slime.BackgroundColor = BGC1;
		Slime.EntityRarityMultiplier = 5;
		Slime.hp = 10;
		Slime.def = 2;
		Slime.atk = 2;
		Slime.critchance = 1;
		Slime.MovementSpeed = 30;
		Slime.PositionX = 27;
		Slime.PositionY = 20;
	}
	// Blue slime
	{
		BlueSlime.EntityType = ENEMY;
		BlueSlime.EntityID = BLUE_SLIME;
		BlueSlime.EntityRepresentation = '#';
		BlueSlime.ForegroundColor = 0x6;
		BlueSlime.BackgroundColor = BGC1;
		BlueSlime.EntityRarityMultiplier = 5;
		BlueSlime.hp = 15;
		BlueSlime.def = 4;
		BlueSlime.atk = 3;
		BlueSlime.critchance = 2;
		BlueSlime.MovementSpeed = 35;
		BlueSlime.PositionX = 15;
		BlueSlime.PositionY = 21;
	}

	/* MULTIPLE INSTANCES OF SAME ENTITY HERE */
	{

		Slime2 = Slime;
		Slime2.PositionX = 35;
		Slime2.PositionY = 10;

		BlueSlime2 = BlueSlime;
		BlueSlime2.PositionX = 26;
		BlueSlime2.PositionY = 7;
	}
}

void SlimeAI(struct entity *sEntity)
{
	cputcxy(sEntity->PositionX, sEntity->PositionY, ' ');
	textcolor(sEntity->ForegroundColor);
	//wait(Slime.MovementSpeed);
	switch(rand()%0x5)
	{
	case 0:
		CollisionProcessX = sEntity->PositionX;
		CollisionProcessY = sEntity->PositionY;
		if (wallCollisionDetection(0, TRUE) == FALSE) sEntity->PositionY--;
		break;
	case 1:
		CollisionProcessX = sEntity->PositionX;
		CollisionProcessY = sEntity->PositionY;
		if (wallCollisionDetection(1, TRUE) == FALSE) sEntity->PositionY++;
		break;
	case 2:
		CollisionProcessX = sEntity->PositionX;
		CollisionProcessY = sEntity->PositionY;
		if (wallCollisionDetection(2, TRUE) == FALSE) sEntity->PositionX--;
		break;
	case 3:
		CollisionProcessX = sEntity->PositionX;
		CollisionProcessY = sEntity->PositionY;
		if (wallCollisionDetection(3, TRUE) == FALSE) sEntity->PositionX++;
		break;
	case 4:
		goto _doNothing;
		break;
	default:
_doNothing:
		break;
	}
	cputcxy(sEntity->PositionX, sEntity->PositionY, '#');
}

int SlimeMovementCounter = 0;
int BlueSlimeMovementCounter = 0;
int Slime2MovementCounter = 0;
int BlueSlime2MovementCounter = 0;
void EntityUpdate()
{
	SlimeMovementCounter++;
	Slime2MovementCounter++;
	BlueSlimeMovementCounter++;
	BlueSlime2MovementCounter++;
	if (SlimeMovementCounter==(40-Slime.MovementSpeed))
	{
		SlimeMovementCounter = 0;
		Slime2MovementCounter = 0;
		SlimeAI(&Slime);
		SlimeAI(&Slime2);
	}
	if (BlueSlimeMovementCounter==(40-BlueSlime.MovementSpeed))
	{
		BlueSlimeMovementCounter = 0;
		BlueSlime2MovementCounter = 0;
		SlimeAI(&BlueSlime);
		SlimeAI(&BlueSlime2);
	}
}
