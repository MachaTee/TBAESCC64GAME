/* COPSP C64 TEXT RPG GAME ITEM HEADER FILE */

struct item
{
	int ItemID, ItemType, ItemQuantity;
	int hp, atk, def, critchance;
	float ItemRarityMultiplier;
	char ItemName[50], ItemDescription[50];
	bool IsConsumable;
	bool IsEquippable;
	bool IsEquipped;
}
GenericItem, apple, french_fries, cake_slice, cheese_round, strange_stew, bronze_shortsword,
    leather_jerkin, leather_pants, leather_boots, kitten_major_annoy;

enum Item
{
	APPLE                   = 0,
	/* Consumables */
	FRENCH_FRIES            = 1,
	CAKE_SLICE              = 2,
	CHEESE_ROUND            = 3,
	STRANGE_STEW            = 4,
	/* Unconsumable */
	BRONZE_SHORTSWORD       = 30,
	LEATHER_JERKIN          = 31,
	LEATHER_PANTS           = 32,
	LEATHER_BOOTS           = 33,
	KITTEN_MAJOR_ANNOY      = 34,
	PLACEHOLDER_ENTITY      = 35
};

enum ItemType
{
	MISC            = 0,
	EQUIP           = 1
};

enum Effect
{
	/* Negative */
	POISON          = 0,
	WEAKNESS        = 1,
	SLOWNESS        = 2,
	HORROR          = 3,
	DECAY           = 4,
	CRYSTALLIZED    = 5,
	/* Positive */
	REGENERATION    = 6,
	STRENGTH        = 7,
	SPEED           = 8,
	SANCTIFICATION  = 9,
	HARDENED        = 10
};

struct item *ItemIterator[10];

void InitializeItems()
{

	// EMPTY
	{
		GenericItem.ItemID = 0;
		GenericItem.ItemType = 0;
		GenericItem.ItemQuantity = 0;
		GenericItem.IsConsumable = FALSE;
		GenericItem.IsEquippable = FALSE;
		GenericItem.IsEquipped   = FALSE;

		GenericItem.hp = 0;
		GenericItem.def = 0;
		GenericItem.atk = 0;
		GenericItem.critchance = 0;

		strcpy(GenericItem.ItemName, "Empty item");
		strcpy(GenericItem.ItemDescription, "Generic item");
	}

	// Generic item attribution initialization
	{
		french_fries            = GenericItem;
		cake_slice              = GenericItem;
		cheese_round            = GenericItem;
		strange_stew            = GenericItem;
		bronze_shortsword       = GenericItem;
		leather_jerkin          = GenericItem;
		leather_pants           = GenericItem;
		leather_boots           = GenericItem;
		kitten_major_annoy      = GenericItem;
	}

	// APPLE
	{
		apple.ItemID    = APPLE;
		apple.ItemType  = MISC;
		apple.ItemQuantity = 3;
		apple.IsConsumable = TRUE;
		apple.IsEquippable = FALSE;

		apple.hp = 5;
		apple.def = 0;
		apple.atk = 0;
		apple.critchance = 0;

		strcpy(apple.ItemName, "Apple");
		strcpy(apple.ItemDescription, "A delicious, crunchy apple.");
	}
	// FRENCH FRIES
	{
		french_fries.ItemID = FRENCH_FRIES;
		french_fries.ItemType = MISC;
		french_fries.ItemQuantity = 5;
		french_fries.IsConsumable = TRUE;
		french_fries.IsEquippable = FALSE;

		french_fries.hp = 3;
		french_fries.def = 0;
		french_fries.atk = 0;
		french_fries.critchance = 0;

		strcpy(french_fries.ItemName, "French Fries");
		strcpy(french_fries.ItemDescription, "A seagull's favorite food!");
	}
	// CAKE SLICE
	{
		cake_slice.ItemID = CAKE_SLICE;
		cake_slice.ItemType = MISC;
		cake_slice.ItemQuantity = 1;
		cake_slice.IsConsumable = TRUE;
		cake_slice.IsEquippable = FALSE;

		cake_slice.hp = 10;
		cake_slice.def = 0;
		cake_slice.atk = 0;
		cake_slice.critchance = 0;

		strcpy(cake_slice.ItemName, "Slice of Cake");
		strcpy(cake_slice.ItemDescription, "A hearty slice of cake!");
	}
	// CHEESE ROUND
	{
		cheese_round.ItemID = CHEESE_ROUND;
		cheese_round.ItemType = MISC;
		cheese_round.ItemQuantity = 2;
		cheese_round.IsConsumable = TRUE;
		cheese_round.IsEquippable = FALSE;

		cheese_round.hp = 5;
		cheese_round.def = 0;
		cheese_round.atk = 0;
		cheese_round.critchance = 0;

		strcpy(cheese_round.ItemName, "Cheese round");
		strcpy(cheese_round.ItemDescription, "It smells strong, but it probably tastes great!");
	}
	// STRANGE STEW
	{
		strange_stew.ItemID = STRANGE_STEW;
		strange_stew.ItemType = MISC;
		strange_stew.ItemQuantity = 0;
		strange_stew.IsConsumable = TRUE;
		strange_stew.IsEquippable = FALSE;

		strange_stew.hp = 0;
		strange_stew.def = 2;
		strange_stew.atk = 2;
		strange_stew.critchance = 2;

		strcpy(strange_stew.ItemName, "Strange-looking stew");
		strcpy(strange_stew.ItemDescription, "The stew smells rather odd ... But it seems edible!");
	}
	// BRONZE SHORTSWORD
	{
		bronze_shortsword.ItemID = BRONZE_SHORTSWORD;
		bronze_shortsword.ItemType = EQUIP;
		bronze_shortsword.ItemQuantity = 1;
		bronze_shortsword.IsConsumable = FALSE;
		bronze_shortsword.IsEquippable = TRUE;
		bronze_shortsword.IsEquipped = TRUE;

		bronze_shortsword.hp = 0;
		bronze_shortsword.def = 4;
		bronze_shortsword.atk = 10;
		bronze_shortsword.critchance = 4;

		strcpy(bronze_shortsword.ItemName, "Bronze Shortsword");
		strcpy(bronze_shortsword.ItemDescription, "A weak but durable bronzen shortsword.");
	}
	// LEATHER JERKIN
	{
		leather_jerkin.ItemID = LEATHER_JERKIN;
		leather_jerkin.ItemType = EQUIP;
		leather_jerkin.ItemQuantity = 1;
		leather_jerkin.IsConsumable = FALSE;
		leather_jerkin.IsEquippable = TRUE;
		leather_jerkin.IsEquipped = TRUE;

		leather_jerkin.hp = 0;
		leather_jerkin.def = 10;
		leather_jerkin.atk = 0;
		leather_jerkin.critchance = 0;

		strcpy(leather_jerkin.ItemName, "Leather Jerkin");
		strcpy(leather_jerkin.ItemDescription, "A flimsy leathern jerkin.");
	}
	// LEATHER PANTS
	{
		leather_pants.ItemID = LEATHER_PANTS;
		leather_pants.ItemType = EQUIP;
		leather_pants.ItemQuantity = 1;
		leather_pants.IsConsumable = FALSE;
		leather_pants.IsEquippable = TRUE;
		leather_pants.IsEquipped = TRUE;

		leather_pants.hp = 0;
		leather_pants.def = 7;
		leather_pants.atk = 0;
		leather_pants.critchance = 0;

		strcpy(leather_pants.ItemName, "Leather Pants");
		strcpy(leather_pants.ItemDescription, "A pair of comfortable leathern pants.");
	}
	// LEATHER BOOTS
	{
		leather_boots.ItemID = LEATHER_BOOTS;
		leather_boots.ItemType = EQUIP;
		leather_boots.ItemQuantity = 1;
		leather_boots.IsConsumable = FALSE;
		leather_boots.IsEquippable = TRUE;
		leather_boots.IsEquipped = TRUE;

		leather_boots.hp = 0;
		leather_boots.def = 5;
		leather_boots.atk = 0;
		leather_boots.critchance = 0;

		strcpy(leather_boots.ItemName, "Leather Boots");
		strcpy(leather_boots.ItemDescription, "A pair of worn out leathern boots.");
	}
	// KITTEN OF MAJOR ANNOYANCE

	ItemIterator[0]         = &apple;
	ItemIterator[1]         = &french_fries;
	ItemIterator[2]         = &cake_slice;
	ItemIterator[3]         = &cheese_round;
	ItemIterator[4]         = &strange_stew;
	ItemIterator[5]         = &bronze_shortsword;
	ItemIterator[6]         = &leather_jerkin;
	ItemIterator[7]         = &leather_pants;
	ItemIterator[8]         = &leather_boots;
	ItemIterator[9]         = &kitten_major_annoy;
	ItemIterator[10]        = &GenericItem;

}
