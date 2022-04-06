#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR_LENGTH 255
#define MAX_FIELD_RATE 60

#define LINE_BLANK "                                        "
#define COLLISION_CONDITIONS (getPeek==CenterCollider||getPeek==VerticalCollider||getPeek==HorizontalCollider||getPeek==UpperHoziontalCollider||getPeek==LowerHorizontalCollider||getPeek==LeftVerticalCollider||getPeek==RightVerticalCollider)
#define ENTITY_COLLISION_CONDITIONS (getPeek == 0x40)
#define PLAYER_COLLISION_CONDITIONS (getPeek == '#')

/* Alterable color palette */
#define BGC1 0x0  // BLACK
#define BGC2 0x2  // RED
#define FGC1 0xA  // LIGHT RED
#define FGC2 0x2  // RED
#define FGC3 0x1  // WHITE
#define FGC4 0xB  // LIGHT GREY
#define FGC5 0xC  // GREY
#define FGC6 0xF  // DARK	GREY

#define TRUE 1
#define FALSE 0

typedef enum {false=FALSE, true=TRUE} bool;

const char CenterCollider   = 0xDB;
const char VerticalCollider   = 0x7D;
const char HorizontalCollider  = 0x60;
const char UpperHoziontalCollider  = 0xB2;
const char LowerHorizontalCollider  = 0xB1;
const char LeftVerticalCollider  = 0XAB;
const char RightVerticalCollider  = 0xB3;

#include "utilities.h"

char sx,sy=10;
char screendata[1000];
char scolordata[1000];

bool ssb;

int CollisionProcessX, CollisionProcessY;

#include "items.h"

#include "entities.h"

#define HP_RENDER_OFFSET 25

void DeathSequence()
{
	*(char*)0x00C6 = 0;                                                 // Clears the keyboard buffer
	clrscr();
	textcolor(FGC2);
	cputsxy(10,10," G A M E   O V E R !");
	cputsxy(10,11,"  Y O U   D I E D !");
	while (1) {}
}

void PlayerHealthUpdate()
{

	const int hLen = log10(PlayerEntity.hp);
	const int mLen = log10(PlayerEntity.maxHp);

	char *hstr = malloc(hLen);
	char *mstr = malloc(mLen);

	itoa(PlayerEntity.hp,    hstr, 10);
	itoa(PlayerEntity.maxHp, mstr, 10);

	hstr[hLen]            =  '\0';
	mstr[mLen]        =  '\0';

	if (PlayerEntity.hp == 0) DeathSequence();

	textcolor	(FGC3);
	cputsxy		(HP_RENDER_OFFSET,1,"             ");
	cputsxy		(HP_RENDER_OFFSET,1,"HP: ");
	cputsxy		(HP_RENDER_OFFSET+4,1,hstr);
	cputcxy		(HP_RENDER_OFFSET+5+hLen,1,'/');
	cputsxy		(HP_RENDER_OFFSET+7+hLen,1,mstr);
}

bool collisionDetectionHelper(char getPeek, bool isEntity)
{
	if ((isEntity&&ENTITY_COLLISION_CONDITIONS)||(!isEntity&&PLAYER_COLLISION_CONDITIONS))
	{
		--PlayerEntity.hp;
		PlayerHealthUpdate();                                                                                                // Placeholder
		return TRUE;
	}
	if (COLLISION_CONDITIONS) return TRUE;
	else return FALSE;
}

int wallCollisionDetection(int direction, bool isEntity)
{
	//
	// Wall collision detection
	// Returns: True if collision is found
	// 0 = up
	// 1 = down
	// 2 = left
	// 3 = right
	//
	switch(direction)
	{
	case 0:
		gotoxy(CollisionProcessX, CollisionProcessY-1);
		break;
	case 1:
		gotoxy(CollisionProcessX, CollisionProcessY+1);
		break;
	case 2:
		gotoxy(CollisionProcessX-1, CollisionProcessY);
		break;
	case 3:
		gotoxy(CollisionProcessX+1, CollisionProcessY);
		break;
	default:
		return FALSE;
		break;
	}
	return(collisionDetectionHelper(cpeekc(), isEntity));

}

#include "entityfuncs.h"

void SaveScreenBuffer()
{
	if (ssb==TRUE)
	{
	/* Scan and save the screen buffer */
	int loc=0;
	for (sy=0; sy < 24; sy++)
	{
		for (sx = 0; sx < 40; sx++)
		{

			++loc;
			gotoxy(sx, sy);
			scolordata[loc] = cpeekcolor();
			screendata[loc] = cpeekc();
		}
	}
}
}

void ReturnScreenBuffer()
{
	/* Redraw previously saved screen buffer */
	int loc=0;
	for (sy=0; sy < 24; sy++)
	{
		for (sx = 0; sx < 40; sx++)
		{
			++loc;
			textcolor(scolordata[loc]);
			cputcxy(sx, sy, screendata[loc]);
		}
	}
}

int scroll;
int hcounter;
char hscan[40];

int fieldcounter = 0;
int movementSpeed = 40;

int key;

char wallx1[40];
char wallx2[40];
char wally1[25];
char wally2[25];

char xcoordstr[5];
char ycoordstr[5];

void drawCoords()
{
	itoa(PlayerEntity.PositionX, xcoordstr, 10);
	itoa(PlayerEntity.PositionY, ycoordstr, 10);
	cputsxy(25, 24, xcoordstr);
	cputsxy(30, 24, ycoordstr);

}

void drawbox(int x1, int y1, int x2, int y2)
{
	int x, y;
	for(x=x1; x<x2; x++)
	{
		wallx1[x1] = y1;
		wallx2[x1] = y2;
		cputcxy(x,y1,HorizontalCollider);
		cputcxy(x,y2,HorizontalCollider);
	}
	for(y=y1; y<y2; y++)
	{
		wally1[y1] = x1;
		wally2[y2] = x2;
		cputcxy(x1,y,VerticalCollider);
		cputcxy(x2,y,VerticalCollider);
	}
	cputcxy(x1,y1,CenterCollider);
	cputcxy(x1,y2,CenterCollider);
	cputcxy(x2,y1,CenterCollider);
	cputcxy(x2,y2,CenterCollider);
}


void drawVerticalLine(int x1, int x2, int y1)
{
	int a;
	for (a = x1; a < x2; a++)
	{
		cputcxy(y1, a, VerticalCollider);
	}
	cputcxy(y1, x1, 242);
	cputcxy(y1, x2, 241);
}

void drawHorizontalLine(int y1, int y2, int x1)
{
	int a;
	for (a = y1; a < y2; a++) cputcxy(a, x1, HorizontalCollider);
	cputcxy(y1, x1, LeftVerticalCollider);
	cputcxy(y2, x1, RightVerticalCollider);
}

void InventoryChangeColor(bool u)
{
	for (hcounter = 0; hcounter < 40; hcounter++)
	{
		if (u)
		{
			gotoxy(hcounter, 4+scroll);
			textcolor(FGC3);
			cputc(cpeekc());
		}
		else
		{
			gotoxy(hcounter, 2+scroll);
			textcolor(FGC3);
			cputc(cpeekc());
		}
		gotoxy(hcounter, 3+scroll);
		textcolor(FGC1);
		cputc(cpeekc());
		textcolor(FGC3);
	}
}

bool DisplayInventory;

void showInventory()
{

	struct item *CurrentItems[10] = { NULL };

	int displayQuant = 0;
	int tmp;
	int inventoryPosition = 0;
	char istr[3];

	bool StartEquipmentPrinting = FALSE;

	istr[3] = '\0';
	scroll = 0;

	// Save screen buffer and clear screen
	SaveScreenBuffer();
	clrscr();

	DisplayInventory = FALSE;
	// Start displaying inventory
	cputsxy(1,1, "--- Player's Inventory --- ");
	PlayerHealthUpdate();
	cputsxy(1,2, "- Miscellaneous items:");
	for (tmp=0; tmp < 10; tmp++)
	{
		if (ItemIterator[tmp]->ItemQuantity != 0)
		{
			if (ItemIterator[tmp]->ItemType == EQUIP&&!StartEquipmentPrinting)
			{
				StartEquipmentPrinting = TRUE;
				cputsxy(1,3+inventoryPosition, "- Equipment Items:");
				++displayQuant;
			}
			CurrentItems[displayQuant] = ItemIterator[tmp];
			cputsxy(5,3+inventoryPosition+StartEquipmentPrinting, ItemIterator[tmp]->ItemName);
			itoa(ItemIterator[tmp]->ItemQuantity, istr, 10);
			if (ItemIterator[tmp]->ItemType == EQUIP&&ItemIterator[tmp]->IsEquipped == TRUE)
				cputsxy(22,3+inventoryPosition+StartEquipmentPrinting,"Equipped");
			else cputsxy(22,3+inventoryPosition+StartEquipmentPrinting,istr);
			++displayQuant;
			++inventoryPosition;
		}
	}

	InventoryChangeColor(FALSE);
	textcolor(0xE);
	cputsxy(0, 22, CurrentItems[0]->ItemDescription);

	*(char*)0x00C6 = 0;                                                 // Clears the keyboard buffer


	// Bound keys for inventory controls
	// E = consume, W = up, S = down Q = quit
	while ((key = cgetc())!='q')
	{
		switch(key)
		{
		case 'e':
			if (CurrentItems[scroll]->ItemType == MISC && CurrentItems[scroll]->ItemQuantity>0)
			{
				CurrentItems[scroll]->ItemQuantity--;
				PlayerEntity.hp += CurrentItems[scroll]->hp;
				if (PlayerEntity.hp > PlayerEntity.maxHp) PlayerEntity.hp = PlayerEntity.maxHp;
				PlayerHealthUpdate();
				DisplayInventory = TRUE;
				ssb = FALSE;
				showInventory();
				return;
		}
		break;
		case 'w':
			if (scroll!=0)
			{
				scroll--;
				cputsxy(0,22, LINE_BLANK);
				cputsxy(0,23, LINE_BLANK);
				cputcxy(40, 22, ' ');
				textcolor(0xE);
				cputsxy(0, 22, CurrentItems[scroll]->ItemDescription);
			}
			InventoryChangeColor(TRUE);
			break;
		case 's':
			if (scroll!=displayQuant-1)
			{
				scroll++;
				cputsxy(0,22, LINE_BLANK);
				cputsxy(0,23, LINE_BLANK);
				cputcxy(40, 22, ' ');
				textcolor(0xE);
				cputsxy(0, 22, CurrentItems[scroll]->ItemDescription);
			}
			InventoryChangeColor(FALSE);
			break;
		default:
			break;
		}
	}

	ReturnScreenBuffer();
	PlayerHealthUpdate();
}

void drawMap(int mapID)
{
	switch (mapID)
	{
	case 1:
		goto fallback;
		break;
	default:
fallback:
		bgcolor(0);
		bordercolor(0);
		textcolor(FGC2);
		drawbox(2,3,37,23);
		drawVerticalLine(3, 10, 5);
		drawVerticalLine(16, 23, 5);
		drawHorizontalLine(5, 22, 7);
		drawVerticalLine(3, 5, 14);
		drawHorizontalLine(8, 22, 16);
		drawVerticalLine(16, 23, 22);
		drawHorizontalLine(8, 22, 20);
		drawVerticalLine(3, 16, 31);
		drawHorizontalLine(22, 31, 12);
		break;
	}
	cputcxy(PlayerEntity.PositionX,PlayerEntity.PositionY,PlayerEntity.EntityRepresentation);

}

int actualSpeed;
bool CanMove;
bool ssb;

int main()
{
	srand(0x80);
	InitializeItems();
	InitializeEntities();
	cursor(0);
	clrscr();
	actualSpeed = MAX_FIELD_RATE-PlayerEntity.MovementSpeed;
	cputsxy(1, 1,"Player Name");
	PlayerHealthUpdate();
	drawMap(1);


	// Program Loop
	while (1)
	{
		EntityUpdate();

		textcolor(PlayerEntity.TrailForegroundColor);
		cputcxy(PlayerEntity.PositionX,PlayerEntity.PositionY,PlayerEntity.TrailRepresentation);
		textcolor(PlayerEntity.ForegroundColor);
	
		if (*(unsigned char*)0x00A2%actualSpeed == actualSpeed-1) CanMove = TRUE;

		
		switch(*(char*)0x00C5)
		{
		case 9:
			if (CanMove)
			{
				CollisionProcessX = PlayerEntity.PositionX;
				CollisionProcessY = PlayerEntity.PositionY;
				if (wallCollisionDetection(0, FALSE) == FALSE) PlayerEntity.PositionY--;
				*(unsigned char*)0x00A2 = 0;
				CanMove = FALSE;
			}
			break;
		case 13:
			if (CanMove)
			{
				CollisionProcessX = PlayerEntity.PositionX;
				CollisionProcessY = PlayerEntity.PositionY;
				if (wallCollisionDetection(1, FALSE) == FALSE) PlayerEntity.PositionY++;
				*(unsigned char*)0x00A2 = 0;
				CanMove = FALSE;
			}
			break;
		case 10:
			if (CanMove)
			{
				CollisionProcessX = PlayerEntity.PositionX;
				CollisionProcessY = PlayerEntity.PositionY;
				if (wallCollisionDetection(2, FALSE) == FALSE) PlayerEntity.PositionX--;
				*(unsigned char*)0x00A2 = 0;
				CanMove = FALSE;
			}
			break;
		case 18:
			if (CanMove)
			{
				CollisionProcessX = PlayerEntity.PositionX;
				CollisionProcessY = PlayerEntity.PositionY;
				if (wallCollisionDetection(3, FALSE) == FALSE) PlayerEntity.PositionX++;
				*(unsigned char*)0x00A2 = 0;
				CanMove = FALSE;
			}
			break;
		case 14:
			ssb = TRUE;
			showInventory();
			break;
		case 'f':
			++apple.ItemQuantity;
			break;
		default:
			break;
		}
		cputcxy(PlayerEntity.PositionX,PlayerEntity.PositionY,PlayerEntity.EntityRepresentation);
		drawCoords();
	}
	cursor(1);
	return(0);
}
