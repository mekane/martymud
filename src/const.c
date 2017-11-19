/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

/***************************************************************************
*	ROM 2.4 is copyright 1993-1998 Russ Taylor			   *
*	ROM has been brought to you by the ROM consortium		   *
*	    Russ Taylor (rtaylor@hypercube.org)				   *
*	    Gabrielle Taylor (gtaylor@hypercube.org)			   *
*	    Brian Moore (zump@rom.org)					   *
*	By using this code, you have agreed to follow the terms of the	   *
*	ROM license, in the file Rom24/doc/rom.license			   *
***************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <time.h>
#include "merc.h"
#include "magic.h"
#include "interp.h"


/* item type list */
const struct item_type		item_table	[]	=
{
    {	ITEM_LIGHT,	  "light"	},
    {	ITEM_SCROLL,	  "scroll"	},
    {	ITEM_WAND,	  "wand"	},
    {   ITEM_STAFF,	  "staff"	},
    {   ITEM_WEAPON,	  "weapon"	},
    {   ITEM_TREASURE,	  "treasure"	}, 
    {   ITEM_ARMOR,	  "armor"	},
    {	ITEM_POTION,	  "potion"	}, 
    {	ITEM_CLOTHING,	  "clothing"	},
    {   ITEM_FURNITURE,	  "furniture"	},
    {	ITEM_TRASH,	  "trash"	},
    {	ITEM_CONTAINER,	  "container"	},
    {	ITEM_DRINK_CON,   "drink"	},
    {	ITEM_KEY,	  "key"		},
    {	ITEM_FOOD,	  "food"	},
    {	ITEM_MONEY,	  "money"	},
    {	ITEM_BOAT,	  "boat"	},
    {	ITEM_CORPSE_NPC,  "npc_corpse"	},
    {	ITEM_CORPSE_PC,	  "pc_corpse"	},
    {   ITEM_FOUNTAIN,	  "fountain"	},
    {	ITEM_PILL,	  "pill"	},
    {	ITEM_PROTECT,	  "protect"	},
    {	ITEM_MAP,	  "map"		},
    {	ITEM_PORTAL,	  "portal"	},
    {	ITEM_WARP_STONE,  "warp_stone"	},
    {	ITEM_ROOM_KEY,	  "room_key"	},
    {	ITEM_GEM,	  "gem"		},
    {	ITEM_JEWELRY,	  "jewelry"	},
    {   ITEM_JUKEBOX,	  "jukebox"	},
    {   ITEM_HOLY,	  "holy item"	},
    {   ITEM_SPELLBOOK,	  "spellbook"	},
    {   ITEM_COMP,        "component"	}, /* spell or device */
    {   0,		NULL		}
};


/* weapon selection table */
const	struct	weapon_type	weapon_table	[]	=
{
   { "sword",	OBJ_VNUM_SCHOOL_SWORD,	WEAPON_SWORD,	&gsn_sword	},
   { "mace",	OBJ_VNUM_SCHOOL_MACE,	WEAPON_MACE,	&gsn_mace 	},
   { "dagger",	OBJ_VNUM_SCHOOL_DAGGER,	WEAPON_DAGGER,	&gsn_dagger	},
   { "axe",	OBJ_VNUM_SCHOOL_AXE,	WEAPON_AXE,	&gsn_axe	},
   { "spear",	OBJ_VNUM_SCHOOL_STAFF,	WEAPON_SPEAR,	&gsn_spear	},
   { "flail",	OBJ_VNUM_SCHOOL_FLAIL,	WEAPON_FLAIL,	&gsn_flail	},
   { "whip",	OBJ_VNUM_SCHOOL_WHIP,	WEAPON_WHIP,	&gsn_whip	},
   { "polearm",	OBJ_VNUM_SCHOOL_POLEARM,WEAPON_POLEARM,	&gsn_polearm	},
   { "staff",	OBJ_VNUM_SCHOOL_STAFF,	WEAPON_STAFF,	&gsn_staff	},
   { NULL,	0,				0,	NULL		}
};


 
/* wiznet table and prototype for future flag setting */
const   struct wiznet_type      wiznet_table    []              =
{
   {    "on",           WIZ_ON,         IM },
   {    "prefix",	WIZ_PREFIX,	IM },
   {    "ticks",        WIZ_TICKS,      IM },
   {    "logins",       WIZ_LOGINS,     IM },
   {    "sites",        WIZ_SITES,      L4 },
   {    "links",        WIZ_LINKS,      L5 },
   {	"newbies",	WIZ_NEWBIE,	IM },
   {	"spam",		WIZ_SPAM,	L5 },
   {    "deaths",       WIZ_DEATHS,     IM },
   {    "resets",       WIZ_RESETS,     L4 },
   {    "mobdeaths",    WIZ_MOBDEATHS,  L4 },
   {    "flags",	WIZ_FLAGS,	L5 },
   {	"penalties",	WIZ_PENALTIES,	L5 },
   {	"saccing",	WIZ_SACCING,	L5 },
   {	"levels",	WIZ_LEVELS,	IM },
   {	"load",		WIZ_LOAD,	L2 },
   {	"restore",	WIZ_RESTORE,	L2 },
   {	"snoops",	WIZ_SNOOPS,	L2 },
   {	"switches",	WIZ_SWITCHES,	L2 },
   {	"secure",	WIZ_SECURE,	L1 },
   {	NULL,		0,		0  }
};

/* attack table  -- not very organized :( */
const 	struct attack_type	attack_table	[MAX_DAMAGE_MESSAGE]	=
{
    { 	"none",		"hit",		-1		},  /*  0 */
    {	"slice",	"slice", 	DAM_SLASH	},	
    {   "stab",		"stab",		DAM_PIERCE	},
    {	"slash",	"slash",	DAM_SLASH	},
    {	"whip",		"whip",		DAM_SLASH	},
    {   "claw",		"claw",		DAM_SLASH	},  /*  5 */
    {	"blast",	"blast",	DAM_BASH	},
    {   "pound",	"pound",	DAM_BASH	},
    {	"crush",	"crush",	DAM_BASH	},
    {   "grep",		"grep",		DAM_SLASH	},
    {	"bite",		"bite",		DAM_PIERCE	},  /* 10 */
    {   "pierce",	"pierce",	DAM_PIERCE	},
    {   "suction",	"suction",	DAM_BASH	},
    {	"beating",	"beating",	DAM_BASH	},
    {   "digestion",	"digestion",	DAM_ACID	},
    {	"charge",	"charge",	DAM_BASH	},  /* 15 */
    { 	"slap",		"slap",		DAM_BASH	},
    {	"punch",	"punch",	DAM_BASH	},
    {	"wrath",	"wrath",	DAM_ENERGY	},
    {	"magic",	"magic",	DAM_ENERGY	},
    {   "divine",	"divine power",	DAM_HOLY	},  /* 20 */
    {	"cleave",	"cleave",	DAM_SLASH	},
    {	"scratch",	"scratch",	DAM_PIERCE	},
    {   "peck",		"peck",		DAM_PIERCE	},
    {   "peckb",	"peck",		DAM_BASH	},
    {   "chop",		"chop",		DAM_SLASH	},  /* 25 */
    {   "sting",	"sting",	DAM_PIERCE	},
    {   "smash",	 "smash",	DAM_BASH	},
    {   "shbite",	"shocking bite",DAM_LIGHTNING	},
    {	"flbite",	"flaming bite", DAM_FIRE	},
    {	"frbite",	"freezing bite",DAM_COLD	},  /* 30 */
    {	"acbite",	"acidic bite", 	DAM_ACID	},
    {	"chomp",	"chomp",	DAM_PIERCE	},
    {  	"drain",	"life drain",	DAM_NEGATIVE	},
    {   "thrust",	"thrust",	DAM_PIERCE	},
    {   "slime",	"slime",	DAM_ACID	},
    {	"shock",	"shock",	DAM_LIGHTNING	},
    {   "thwack",	"thwack",	DAM_BASH	},
    {   "flame",	"flame",	DAM_FIRE	},
    {   "chill",	"chill",	DAM_COLD	},
    {   NULL,		NULL,		0		}
};

/* race table */
const 	struct	race_type	race_table	[]		=
{
/*
    {
	name,		pc_race?,
	act bits,	aff_by bits,	off bits,
	imm,		res,		vuln,
	form,		parts,          remort-only race? 
    },
*/
    { "unique",		FALSE, 0, 0, 0, 0, 0, 0, 0, 0, FALSE },

    { 
	"human",		TRUE, 
	0,		0, 		0,
	0, 		0,		0,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, FALSE
    },

    {
	"elf",			TRUE,
	0,		AFF_INFRARED,	0,
	0,		RES_CHARM,	VULN_IRON,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, FALSE
    },

    {
	"dwarf",		TRUE,
	0,		AFF_INFRARED,	0,
	0,		RES_POISON|RES_DISEASE, VULN_DROWNING,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, FALSE
    },

    {
	"giant",		TRUE,
	0,		0,		0,
	0,		RES_FIRE|RES_COLD,	VULN_MENTAL|VULN_LIGHTNING,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, FALSE
    },
    /*
     * MEK 3-11-2004
     *
     * 4 New Races: halfling, angel, titan, demon
     * 
     */
    { 
	"halfling",	TRUE, 
	0,		0, 		0,
	0, 		RES_POISON,	0,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, FALSE
    },

    { 
	"angel",	TRUE, 
	0,		AFF_FLYING|AFF_DETECT_EVIL, 	0,
	IMM_HOLY, 	0,		VULN_NEGATIVE,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K|P, TRUE
    },

    { 
	"titan",	TRUE, 
	0,		0, 		0,
	0, 		RES_POISON|RES_DISEASE,		0,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, TRUE
    },

    { 
	"demon",	TRUE, 
	0,		AFF_FLYING|AFF_DETECT_GOOD, 	0,
	IMM_NEGATIVE, 	0,		VULN_HOLY,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K|P, TRUE
    },
    
    {
	"bat",			FALSE,
	0,		AFF_FLYING|AFF_DARK_VISION,	OFF_DODGE|OFF_FAST,
	0,		0,		VULN_LIGHT,
	A|G|V,		A|C|D|E|F|H|J|K|P, FALSE
    },

    {
	"bear",			FALSE,
	0,		0,		OFF_CRUSH|OFF_DISARM|OFF_BERSERK,
	0,		RES_BASH|RES_COLD,	0,
	A|G|V,		A|B|C|D|E|F|H|J|K|U|V, FALSE
    },

    {
	"cat",			FALSE,
	0,		AFF_DARK_VISION,	OFF_FAST|OFF_DODGE,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K|Q|U|V, FALSE
    },

    {
	"centipede",		FALSE,
	0,		AFF_DARK_VISION,	0,
	0,		RES_PIERCE|RES_COLD,	VULN_BASH,
 	A|B|G|O,		A|C|K, FALSE	
    },

    {
	"dog",			FALSE,
	0,		0,		OFF_FAST,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K|U|V, FALSE
    },
    /*
     * MEK 3-11-2004
     *
     * I don't think this is necessary
     *
    {
	"doll",			FALSE,
	0,		0,		0,
	IMM_COLD|IMM_POISON|IMM_HOLY|IMM_NEGATIVE|IMM_MENTAL|IMM_DISEASE
	|IMM_DROWNING,	RES_BASH|RES_LIGHT,
	VULN_SLASH|VULN_FIRE|VULN_ACID|VULN_LIGHTNING|VULN_ENERGY,
	E|J|M|cc,	A|B|C|G|H|K, FALSE
    },
    */

    /*
     * MEK 3-11-2004
     *
     * Made changes to Dragon race to make it more generic. Specific 
     * IMM/RES/VULN's should be set in the MOB definition
     *
     */
    { 	"dragon", 		FALSE, 
	0, 			AFF_INFRARED|AFF_FLYING,	0,
	0,			RES_BASH,                       0,
	A|H|Z,		A|C|D|E|F|G|H|I|J|K|P|Q|U|V|X, FALSE
    },
    /*
     * MEK 3-11-2004
     *
     * I don't think this is necessary
     *
    {
	"fido",			FALSE,
	0,		0,		OFF_DODGE|ASSIST_RACE,
	0,		0,			VULN_MAGIC,
	A|B|G|V,	A|C|D|E|F|H|J|K|Q|V, FALSE
    },		
    */  
    {
	"fox",			FALSE,
	0,		AFF_DARK_VISION,	OFF_FAST|OFF_DODGE,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K|Q|V, FALSE
    },

    {
	"goblin",		FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_DISEASE,	VULN_MAGIC,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, FALSE
    },

    {
	"hobgoblin",		FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_DISEASE|RES_POISON,	0,
	A|H|M|V,        A|B|C|D|E|F|G|H|I|J|K|Y, FALSE
    },

    {
	"kobold",		FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_POISON,	VULN_MAGIC,
	A|B|H|M|V,	A|B|C|D|E|F|G|H|I|J|K|Q, FALSE
    },

    {
	"lizard",		FALSE,
	0,		0,		0,
	0,		RES_POISON,	VULN_COLD,
	A|G|X|cc,	A|C|D|E|F|H|K|Q|V, FALSE
    },
    /*
     * MEK 3-11-2004
     *
     * I don't think this is necessary
     *
    {
	"modron",		FALSE,
	0,		AFF_INFRARED,		ASSIST_RACE|ASSIST_ALIGN,
	IMM_CHARM|IMM_DISEASE|IMM_MENTAL|IMM_HOLY|IMM_NEGATIVE,
			RES_FIRE|RES_COLD|RES_ACID,	0,
	H,		A|B|C|G|H|J|K, FALSE
    },
    */
    {
	"orc",			FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_DISEASE,	VULN_LIGHT,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K, FALSE
    },

    {
	"pig",			FALSE,
	0,		0,		0,
	0,		0,		0,
	A|G|V,	 	A|C|D|E|F|H|J|K, FALSE
    },	

    {
	"rabbit",		FALSE,
	0,		0,		OFF_DODGE|OFF_FAST,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K, FALSE
    },
    /*
     * MEK 3-11-2004
     *
     * I don't think this is necessary
     *
     {
        "school monster",	FALSE,
	ACT_NOALIGN,		0,		0,
	IMM_CHARM|IMM_SUMMON,	0,		VULN_MAGIC,
	A|M|V,		A|B|C|D|E|F|H|J|K|Q|U, FALSE
    },	
    */

    {
	"skeleton",		FALSE,
	0,		0,		0,
	IMM_POISON|IMM_NEGATIVE|IMM_MENTAL|IMM_DISEASE,	RES_PIERCE|RES_COLD,
	VULN_BASH|VULN_HOLY,
	I|M|cc,	        A|B|C|G|H|U,    FALSE
    },

    {
	"snake",		FALSE,
	0,		0,		0,
	0,		RES_POISON,	VULN_COLD,
	A|G|X|Y|cc,	A|D|E|F|K|L|Q|V|X, FALSE
    },
 
    {
	"song bird",		FALSE,
	0,		AFF_FLYING,		OFF_FAST|OFF_DODGE,
	0,		0,		0,
	A|G|W,		A|C|D|E|F|H|K|P, FALSE
    },

    {
	"troll",		FALSE,
	0,		AFF_REGENERATION|AFF_INFRARED|AFF_DETECT_HIDDEN,
	OFF_BERSERK,
 	0,	RES_CHARM|RES_BASH,	VULN_FIRE|VULN_ACID,
	A|B|H|M|V,		A|B|C|D|E|F|G|H|I|J|K|U|V, FALSE
    },

    {
	"water fowl",		FALSE,
	0,		AFF_SWIM|AFF_FLYING,	0,
	0,		RES_DROWNING,		0,
	A|G|W,		A|C|D|E|F|H|K|P, FALSE
    },		
  
    {
	"wolf",			FALSE,
	0,		AFF_DARK_VISION,	OFF_FAST|OFF_DODGE,
	0,		0,		0,	
	A|G|V,		A|C|D|E|F|J|K|Q|V, FALSE
    },

    {
	"wyvern",		FALSE,
	0,		AFF_FLYING|AFF_DETECT_INVIS|AFF_DETECT_HIDDEN,
	OFF_BASH|OFF_FAST|OFF_DODGE,
	IMM_POISON,	0,	VULN_LIGHT,
	A|B|G|Z,		A|C|D|E|F|H|J|K|Q|V|X, FALSE
    },

    {
	"zombie",		FALSE,
	0,		0,		0,
	IMM_POISON|IMM_NEGATIVE|IMM_MENTAL|IMM_DISEASE,	0, VULN_HOLY|VULN_FIRE,
	I|M|cc,         A|D|C|G|H|U,    FALSE
    },

    {
	"unique",		FALSE,
	0,		0,		0,
	0,		0,		0,		
	0,		0, FALSE
    },


    {
	NULL, 0, 0, 0, 0, 0, 0, FALSE
    }
};

const	struct	pc_race_type	pc_race_table	[]	=
{
    { 
        "null race",    "",             0,
	//mag, cle, thi, war, rag, wiz, pre, asi, kni, dru, ang, ttn, dem*/ 
        { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 },
        { "" }, 
        { 13, 13, 13, 13, 13 }, { 18, 18, 18, 18, 18 },  0 
    },
 
/*
    {
	"race name", 	short name, 	points,	
	{ class multipliers },
	{ bonus skills },
        { base stats },		{ max stats },		size 
    },
*/

    {
        "human",	"Human",	0,	
	//mag, cle, thi, war, rag, wiz, pre, asi, kni, dru, ang, ttn, dem*/ 
        { 100, 100, 100, 100, 100, 125, 125, 125, 125, 125,  -1,  -1,  -1 },
	{ "" },
	{ 13, 13, 13, 13, 13 },	{ 18, 18, 18, 18, 18 },	SIZE_MEDIUM
    },

    { 	
	"elf",		" Elf ",	5,	
	//mag, cle, thi, war, rag, wiz, pre, asi, kni, dru, ang, ttn, dem*/ 
	{ 100, 125, 100, 120, 110, 125, 150, 125, 145, 130,  -1,  -1,  -1 },
	{ "sneak", "hide" },
	{ 12, 14, 13, 15, 11 },	{ 16, 20, 18, 21, 15 }, SIZE_MEDIUM
    },

    {
	"dwarf",	"Dwarf",	8,	
	//mag, cle, thi, war, rag, wiz, pre, asi, kni, dru, ang, ttn, dem*/ 
	{  -1, 100, 125, 100, 115,  -1, 125, 150, 125, 140,  -1,  -1,  -1 },
	{ "berserk" },
	{ 14, 12, 14, 10, 15 },	{ 20, 16, 19, 14, 21 }, SIZE_SMALL
    },

    {
	"giant",	"Giant",	6,	
	//mag, cle, thi, war, rag, wiz, pre, asi, kni, dru, ang, ttn, dem*/ 
	{  -1, 150, 150, 105, 120,  -1, 175, 175, 130, 145,  -1,  -1,  -1 },
	{ "bash", "fast healing" },
	{ 16, 11, 13, 11, 14 },	{ 22, 15, 18, 15, 20 }, SIZE_LARGE
    },

    /*
     * MEK 3-11-2004 
     *
     * New PC Races - halfling is normal race
     * Angel, Titan, and Demon are 2nd remort-only
     */

    {
        "halfling",	"Half", 	4,	
	//mag, cle, thi, war, rag, wiz, pre, asi, kni, dru, ang, ttn, dem*/
	{ 120, 110, 100, 125, 115, 145, 135, 125, 150, 145,  -1,  -1,  -1 },
        { "sneak", "hide" },
        { 11, 13, 13, 15, 13 },	{ 16, 18, 18, 22, 17 },	SIZE_SMALL
    },
      
    //These are the second-remort races
    {
	"angel",	"Angel",	0,	
	{  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 150,  -1,  -1 },
	{ "" },
	{ 15, 15, 15, 15, 15 },	{ 22, 21, 24, 20, 21 },	SIZE_LARGE
    },

    {
	"titan",	"Titan",	0,
	{  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 150,  -1 },
	{ "" },
	{ 15, 15, 15, 15, 15 },	{ 22, 21, 21, 20, 24 },	SIZE_HUGE
    },

    {
	"demon",	"Demon",	0,	
	{  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 150 },
	{ "" },
	{ 15, 15, 15, 15, 15 },	{ 22, 24, 21, 20, 21 },	SIZE_LARGE
    },
   
};

	
      	

/*
 * Class table.
 */
const	struct	class_type	class_table	[MAX_CLASS]	=
{
  /*
    {
        "name", "Who", PTIME_ATTRIBUTE, DEFAULT_WEAPON,
	{ guild0, guild1 }, max_skill, thac0_1, thac0_32, hpMin, hpMax, Spells,
	  "base group", "default group", REMORT_CLASS
    }
    
   * note - guild0 is used for the starting location of new characters
   */

    {
	"mage", "Mag",  STAT_INT,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3018, 9618 },  75,  20, 6,  6,  8, TRUE,
	"mage basics", "mage default", FALSE
    },

    {
	"cleric", "Cle",  STAT_WIS,  OBJ_VNUM_SCHOOL_MACE,
	{ 3003, 9619 },  75,  20, 2,  7, 10, TRUE,
	"cleric basics", "cleric default", FALSE
    },

    {
	"thief", "Thi",  STAT_DEX,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3028, 9639 },  75,  20,  -4,  8, 13, FALSE,
	"thief basics", "thief default", FALSE
    },

    {
	"warrior", "War",  STAT_STR,  OBJ_VNUM_SCHOOL_SWORD,
	{ 3022, 9633 },  75,  20,  -10,  11, 15, FALSE,
	"warrior basics", "warrior default", FALSE
    },

    /*
     * MEK 11-3-2004
     *
     * Added new class - Ranger, 
     * Added remort classes - Knight, Wizard, Priest, Assasin, Druid
     * Added 2nd remort classes - Angel, Titan, Demon 
     *
     */
    {
	"ranger", "Rag",  STAT_STR,  OBJ_VNUM_SCHOOL_SWORD,
	{ 3022, 9633 },  75,  20,  -7,  10, 14, TRUE,
	"ranger basics", "ranger default", FALSE
    },

    //remort classes
    {
	"wizard", "Wiz",  STAT_INT,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3018, 9618 },  80,  19, 5,  7,  8, TRUE,
	"wizard basics", "wizard default", TRUE
    },

    {
	"priest", "Pre",  STAT_WIS,  OBJ_VNUM_SCHOOL_MACE,
	{ 3003, 9619 },  80,  19, 1,  8, 10, TRUE,
	"priest basics", "priest default", TRUE
    },

    {
	"assasin", "Asi",  STAT_DEX,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3028, 9639 },  80,  19,  -6,  9, 14, FALSE,
	"assasin basics", "assasin default", TRUE
    },

    {
	"knight", "Kni",  STAT_STR,  OBJ_VNUM_SCHOOL_SWORD,
	{ 3022, 9633 },  80,  19,  -12,  12, 16, FALSE,
	"knight basics", "knight default", TRUE
    },

    {
	"druid", "Dru",  STAT_WIS,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3003, 9619 },  80,  19,  -1,  10, 14, TRUE,
	"druid basics", "druid default", TRUE
    },
    
    //2nd remort classes
    {
	"angel", "Ang",  STAT_WIS,  OBJ_VNUM_SCHOOL_SWORD,
	{ 3022, 9633 },  83,  18,  -12,  12, 18, TRUE,
	"angel basics", "angel default", TRUE
    },

    {
	"titan", "Ttn",  STAT_STR,  OBJ_VNUM_SCHOOL_SWORD,
	{ 3022, 9633 },  83,  18,  -12,  12, 18, FALSE,
	"titan basics", "titan default", TRUE
    },

    {
	"demon", "Dem",  STAT_INT,  OBJ_VNUM_SCHOOL_SWORD,
	{ 3022, 9633 },  83,  18,  -12,  12, 18, TRUE,
	"demon basics", "demon default", TRUE
    },

};



/*
 * Titles.
 *
 * MEK 3-10-2004
 * Added extra titles for higher MAX_LEVEL and fewer immortal levels
 *
 */
char *	const			title_table	[MAX_CLASS][MAX_LEVEL+1][2] =
{
    {
      //mage - 0
	{ "Man",			"Woman"				},

	{ "Apprentice of Magic",	"Apprentice of Magic"		},
	{ "Spell Student",		"Spell Student"			},
	{ "Scholar of Magic",		"Scholar of Magic"		},
	{ "Delver in Spells",		"Delveress in Spells"		},
	{ "Medium of Magic",		"Medium of Magic"		},

	{ "Scribe of Magic",		"Scribess of Magic"		},
	{ "Seer",			"Seeress"			},
	{ "Sage",			"Sage"				},
	{ "Illusionist",		"Illusionist"			},
	{ "Abjurer",			"Abjuress"			},
	/*10*/
	{ "Invoker",			"Invoker"			},
	{ "Enchanter",			"Enchantress"			},
	{ "Conjurer",			"Conjuress"			},
	{ "Magician",			"Witch"				},
	{ "Creator",			"Creator"			},

	{ "Savant",			"Savant"			},
	{ "Magus",			"Craftess"			},
	{ "Wizard",			"Wizard"			},
	{ "Warlock",			"War Witch"			},
	{ "Sorcerer",			"Sorceress"			},
	/*20*/
	{ "Elder Sorcerer",		"Elder Sorceress"		},
	{ "Grand Sorcerer",		"Grand Sorceress"		},
	{ "Great Sorcerer",		"Great Sorceress"		},
	{ "Golem Maker",		"Golem Maker"			},
	{ "Greater Golem Maker",	"Greater Golem Maker"		},

	{ "Maker of Stones",		"Maker of Stones",		},
	{ "Maker of Potions",		"Maker of Potions",		},
	{ "Maker of Scrolls",		"Maker of Scrolls",		},
	{ "Maker of Wands",		"Maker of Wands",		},
	{ "Maker of Staves",		"Maker of Staves",		},
	/*30*/
	{ "Demon Summoner",		"Demon Summoner"		},
	{ "Greater Demon Summoner",	"Greater Demon Summoner"	},
	{ "Dragon Charmer",		"Dragon Charmer"		},
	{ "Greater Dragon Charmer",	"Greater Dragon Charmer"	},
	{ "Master of all Magic",	"Master of all Magic"		},

 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
	/*40*/
 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
	/*50*/
 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
	/*60*/
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
	/*70*/
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
	{ "Mage Hero",			"Mage Heroine"			},
	/*74*/
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supremity of Magic",		"Supremity of Magic"		},
	{ "Creator",			"Creator"			},
	{ "Implementor",		"Implementress"			}
    },
    //cleric 1
    {
	{ "Man",			"Woman"				},

	{ "Believer",			"Believer"			},
	{ "Attendant",			"Attendant"			},
	{ "Acolyte",			"Acolyte"			},
	{ "Novice",			"Novice"			},
	{ "Missionary",			"Missionary"			},

	{ "Adept",			"Adept"				},
	{ "Deacon",			"Deaconess"			},
	{ "Vicar",			"Vicaress"			},
	{ "Priest",			"Priestess"			},
	{ "Minister",			"Lady Minister"			},
	/*10*/
	{ "Canon",			"Canon"				},
	{ "Levite",			"Levitess"			},
	{ "Curate",			"Curess"			},
	{ "Monk",			"Nun"				},
	{ "Healer",			"Healess"			},

	{ "Chaplain",			"Chaplain"			},
	{ "Expositor",			"Expositress"			},
	{ "Bishop",			"Bishop"			},
	{ "Arch Bishop",		"Arch Lady of the Church"	},
	{ "Patriarch",			"Matriarch"			},
	/*20*/
	{ "Elder Patriarch",		"Elder Matriarch"		},
	{ "Grand Patriarch",		"Grand Matriarch"		},
	{ "Great Patriarch",		"Great Matriarch"		},
	{ "Demon Killer",		"Demon Killer"			},
	{ "Greater Demon Killer",	"Greater Demon Killer"		},

	{ "Cardinal of the Sea",	"Cardinal of the Sea"		},
	{ "Cardinal of the Earth",	"Cardinal of the Earth"		},
	{ "Cardinal of the Air",	"Cardinal of the Air"		},
	{ "Cardinal of the Ether",	"Cardinal of the Ether"		},
	{ "Cardinal of the Heavens",	"Cardinal of the Heavens"	},
	/*30*/
	{ "Avatar of an Immortal",	"Avatar of an Immortal"		},
	{ "Avatar of a Deity",		"Avatar of a Deity"		},
	{ "Avatar of a Supremity",	"Avatar of a Supremity"		},
	{ "Avatar of an Implementor",	"Avatar of an Implementor"	},
	{ "Master of all Divinity",	"Mistress of all Divinity"	},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	/*40*/
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	/*50*/
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	/*60*/
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	/*70*/
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Holy Hero",			"Holy Heroine"			},
	/*74*/
	{ "Holy Avatar",		"Holy Avatar"			},
	{ "Demigod",			"Demigoddess",			},
	{ "Deity",			"Deity"				},
	{ "Supreme Master",		"Supreme Mistress"		},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },
    //thief - 2
    {
	{ "Man",			"Woman"				},

	{ "Pilferer",			"Pilferess"			},
	{ "Footpad",			"Footpad"			},
	{ "Filcher",			"Filcheress"			},
	{ "Pick-Pocket",		"Pick-Pocket"			},
	{ "Sneak",			"Sneak"				},

	{ "Pincher",			"Pincheress"			},
	{ "Cut-Purse",			"Cut-Purse"			},
	{ "Snatcher",			"Snatcheress"			},
	{ "Sharper",			"Sharpress"			},
	{ "Rogue",			"Rogue"				},
	/*10*/
	{ "Robber",			"Robber"			},
	{ "Magsman",			"Magswoman"			},
	{ "Highwayman",			"Highwaywoman"			},
	{ "Burglar",			"Burglaress"			},
	{ "Thief",			"Thief"				},

	{ "Knifer",			"Knifer"			},
	{ "Quick-Blade",		"Quick-Blade"			},
	{ "Killer",			"Murderess"			},
	{ "Brigand",			"Brigand"			},
	{ "Cut-Throat",			"Cut-Throat"			},
	/*20*/
	{ "Spy",			"Spy"				},
	{ "Grand Spy",			"Grand Spy"			},
	{ "Master Spy",			"Master Spy"			},
	{ "Assassin",			"Assassin"			},
	{ "Greater Assassin",		"Greater Assassin"		},

	{ "Master of Vision",		"Mistress of Vision"		},
	{ "Master of Hearing",		"Mistress of Hearing"		},
	{ "Master of Smell",		"Mistress of Smell"		},
	{ "Master of Taste",		"Mistress of Taste"		},
	{ "Master of Touch",		"Mistress of Touch"		},
	/*30*/
	{ "Crime Lord",			"Crime Mistress"		},
	{ "Infamous Crime Lord",	"Infamous Crime Mistress"	},
	{ "Greater Crime Lord",		"Greater Crime Mistress"	},
	{ "Master Crime Lord",		"Master Crime Mistress"		},
	{ "Godfather",			"Godmother"			},

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
	/*40*/
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
	/*50*/
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
	/*60*/
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
	/*70*/
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
	{ "Assassin Hero",		"Assassin Heroine"		},
	/*74*/
	{ "Avatar of Death",		"Avatar of Death",		},
	{ "Demigod of Assassins",	"Demigoddess of Assassins"	},
	{ "Deity of Assassins",		"Deity of Assassins"		},
	{ "Supreme Master",		"Supreme Mistress"		},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },
    //warrior - 3
    {
	{ "Man",			"Woman"				},

	{ "Swordpupil",			"Swordpupil"			},
	{ "Recruit",			"Recruit"			},
	{ "Sentry",			"Sentress"			},
	{ "Fighter",			"Fighter"			},
	{ "Soldier",			"Soldier"			},

	{ "Warrior",			"Warrior"			},
	{ "Veteran",			"Veteran"			},
	{ "Swordsman",			"Swordswoman"			},
	{ "Fencer",			"Fenceress"			},
	{ "Combatant",			"Combatess"			},
	/*10*/
	{ "Hero",			"Heroine"			},
	{ "Myrmidon",			"Myrmidon"			},
	{ "Swashbuckler",		"Swashbuckleress"		},
	{ "Mercenary",			"Mercenaress"			},
	{ "Swordmaster",		"Swordmistress"			},

	{ "Lieutenant",			"Lieutenant"			},
	{ "Champion",			"Lady Champion"			},
	{ "Dragoon",			"Lady Dragoon"			},
	{ "Cavalier",			"Lady Cavalier"			},
	{ "Knight",			"Lady Knight"			},
	/*20*/
	{ "Grand Knight",		"Grand Knight"			},
	{ "Master Knight",		"Master Knight"			},
	{ "Paladin",			"Paladin"			},
	{ "Grand Paladin",		"Grand Paladin"			},
	{ "Demon Slayer",		"Demon Slayer"			},

	{ "Greater Demon Slayer",	"Greater Demon Slayer"		},
	{ "Dragon Slayer",		"Dragon Slayer"			},
	{ "Greater Dragon Slayer",	"Greater Dragon Slayer"		},
	{ "Underlord",			"Underlord"			},
	{ "Overlord",			"Overlord"			},
	/*30*/
	{ "Baron of Thunder",		"Baroness of Thunder"		},
	{ "Baron of Storms",		"Baroness of Storms"		},
	{ "Baron of Tornadoes",		"Baroness of Tornadoes"		},
	{ "Baron of Hurricanes",	"Baroness of Hurricanes"	},
	{ "Baron of Meteors",		"Baroness of Meteors"		},

	{ "Master Warrior",		"Master Warrior"		},
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
	/*40*/
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
	/*50*/
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
	/*60*/
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
	/*70*/
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
	{ "Warrior Hero",		"Warrior Heroine"		},
	/*74*/
	{ "Avatar of War",		"Avatar of War"			},
	{ "Demigod of War",		"Demigoddess of War"		},
	{ "Deity of War",		"Deity of War"			},
	{ "Supreme Master of War",	"Supreme Mistress of War"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },
    
    /*
     * MEK 3-11-2004
     *
     * Added titles for new classes
     * @@@needs more work
     *
     */
    //ranger - 4
    {
	{ "Man",			"Woman"				},

	{ "Swordpupil",			"Swordpupil"			},
	{ "Recruit",			"Recruit"			},
	{ "Sentry",			"Sentress"			},
	{ "Fighter",			"Fighter"			},
	{ "Soldier",			"Soldier"			},

	{ "Ranger",			"Ranger"			},
	{ "Veteran",			"Veteran"			},
	{ "Swordsman",			"Swordswoman"			},
	{ "Fencer",			"Fenceress"			},
	{ "Combatant",			"Combatess"			},
	/*10*/
	{ "Hero",			"Heroine"			},
	{ "Myrmidon",			"Myrmidon"			},
	{ "Swashbuckler",		"Swashbuckleress"		},
	{ "Mercenary",			"Mercenaress"			},
	{ "Swordmaster",		"Swordmistress"			},

	{ "Lieutenant",			"Lieutenant"			},
	{ "Champion",			"Lady Champion"			},
	{ "Dragoon",			"Lady Dragoon"			},
	{ "Cavalier",			"Lady Cavalier"			},
	{ "Knight",			"Lady Knight"			},
	/*20*/
	{ "Grand Knight",		"Grand Knight"			},
	{ "Master Knight",		"Master Knight"			},
	{ "Paladin",			"Paladin"			},
	{ "Grand Paladin",		"Grand Paladin"			},
	{ "Demon Slayer",		"Demon Slayer"			},

	{ "Greater Demon Slayer",	"Greater Demon Slayer"		},
	{ "Dragon Slayer",		"Dragon Slayer"			},
	{ "Greater Dragon Slayer",	"Greater Dragon Slayer"		},
	{ "Underlord",			"Underlord"			},
	{ "Overlord",			"Overlord"			},
	/*30*/
	{ "Baron of Thunder",		"Baroness of Thunder"		},
	{ "Baron of Storms",		"Baroness of Storms"		},
	{ "Baron of Tornadoes",		"Baroness of Tornadoes"		},
	{ "Baron of Hurricanes",	"Baroness of Hurricanes"	},
	{ "Baron of Meteors",		"Baroness of Meteors"		},

	{ "Master Ranger",		"Master Ranger"		},
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
	/*40*/ 
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },

        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
	/*50*/
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
 
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
	/*60*/
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },

        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
	/*70*/
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
        { "Master Ranger",              "Master Ranger"                },
	{ "Ranger Hero",		"Ranger Heroine"	       },
	/*74*/
	{ "Avatar of War",		"Avatar of War"			},
	{ "Demigod of War",		"Demigoddess of War"		},
	{ "Deity of War",		"Deity of War"			},
	{ "Supreme Master of War",	"Supreme Mistress of War"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    //wizard - 5
    {
	{ "Man",			"Woman"				},

	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},

	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	//10
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},

	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	{ "Apprentice Wizard",		"Apprentice Wizardess"		},
	//20   
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},

	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	//30
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},

	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	{ "Novice Wizard",		"Novice Wizardess"		},
	//40
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},

	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	//50
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},

	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	{ "Adept Wizard",		"Adept Wizardess"		},
	//60
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},

	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	{ "Journeyman Wizard",		"Journeyman Wizardess"		},
	//70
        { "Master Wizard",              "Master Wizardess"              },
        { "Master Wizard",              "Master Wizardess"              },
        { "Master Wizard",              "Master Wizardess"              },
	{ "Wizard Hero",		"Wizard Heroine"   	        },
	/*74*/
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supreme Master of Magic",	"Supreme Mistress of Magic"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    //priest - 6
    {
	{ "Man",			"Woman"				},

	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},

	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	//10
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},

	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	{ "Apprentice Priest",		"Apprentice Priestess"		},
	//20   
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},

	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	//30
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},

	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	{ "Novice Priest",		"Novice Priestess"		},
	//40
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},

	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	//50
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},

	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	{ "Adept Priest",		"Adept Priestess"		},
	//60
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},

	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	{ "Journeyman Priest",		"Journeyman Priestess"		},
	//70
        { "Master Priest",              "Master Priestess"              },
        { "Master Priest",              "Master Priestess"              },
        { "Master Priest",              "Master Priestess"              },
	{ "Priest Hero",		"Priest Heroine"   	        },
	/*74*/
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supreme Master of Magic",	"Supreme Mistress of Magic"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    //assasin - 7
    {
	{ "Man",			"Woman"				},

	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},

	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	//10
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},

	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	{ "Apprentice Assasin",		"Apprentice Assasin"		},
	//20   
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},

	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	//30
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},

	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	{ "Novice Assasin",		"Novice Assasin"		},
	//40
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},

	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	//50
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},

	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	{ "Adept Assasin",		"Adept Assasin"		},
	//60
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},

	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	{ "Journeyman Assasin",		"Journeyman Assasin"		},
	//70
        { "Master Assasin",              "Master Assasin"              },
        { "Master Assasin",              "Master Assasin"              },
        { "Master Assasin",              "Master Assasin"              },
	{ "Assasin Hero",		"Assasin Heroine"   	        },
	/*74*/
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supreme Master of Magic",	"Supreme Mistress of Magic"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    //knight - 8
    {
	{ "Man",			"Woman"				},

	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},

	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	//10
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},

	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	{ "Apprentice Knight",		"Apprentice Knight"		},
	//20   
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},

	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	//30
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},

	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	{ "Novice Knight",		"Novice Knight"		},
	//40
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},

	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	//50
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},

	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	{ "Adept Knight",		"Adept Knight"		},
	//60
	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},

	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},
	{ "Journeyman Knight",		"Journeyman Knight"		},
	//70
        { "Master Knight",              "Master Knight"              },
        { "Master Knight",              "Master Knight"              },
        { "Master Knight",              "Master Knight"              },
	{ "Knight Hero",		"Knight Heroine"   	        },
	/*74*/
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supreme Master of Magic",	"Supreme Mistress of Magic"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    //druid 9
    {
	{ "Man",			"Woman"				},

	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},

	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	//10
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},

	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	{ "Apprentice Druid",		"Apprentice Druid"		},
	//20   
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},

	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	//30
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},

	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	{ "Novice Druid",		"Novice Druid"		},
	//40
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},

	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	//50
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},

	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	{ "Adept Druid",		"Adept Druid"		},
	//60
	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},

	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},
	{ "Journeyman Druid",		"Journeyman Druid"		},
	//70
        { "Master Druid",              "Master Druid"              },
        { "Master Druid",              "Master Druid"              },
        { "Master Druid",              "Master Druid"              },
	{ "Druid Hero",		       "Knight Heroine"   	        },
	/*74*/
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supreme Master of Magic",	"Supreme Mistress of Magic"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    //angel - 10 
    {
	{ "Man",			"Woman"				},

	{ "Cherub",                     "Cherub"              },
	{ "Cherub",                     "Cherub"              },
	{ "Cherub",                     "Cherub"              },
	{ "Cherub",                     "Cherub"              },
	{ "Cherub",                     "Cherub"              },

	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	//10
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },

	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	//20
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },

	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	//30
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },

	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	{ "Angel",                     "Angel"              },
	//40
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },

	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	//50
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },

	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	{ "Seraph",                    "Seraph"              },
	//60
	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },

	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },
	{ "ArchAngel",                 "ArchAngel"              },
	//70
        { "Master ArchAngel",          "Master ArchAngel"              },
        { "Master ArchAngel",          "Master ArchAngel"              },
        { "Master ArchAngel",          "Master ArchAngel"              },
	{ "Angel Hero",		       "Angel Heroine"   	        },
	/*74*/
	{ "Angelic Avatar ",	       "Angelic Avatar"		},
	{ "Angelic Demigod ",	       "Anglelic Demigoddess"	},
	{ "Angelic Deity ",	       "Anglelic Deity"		},
	{ "Anglic Supremity ",	       "Anglelic Supremity"	},
        { "Creator",                   "Creator"                },
	{ "Implementor",	       "Implementress"          }
    },
    //titan - 11
    {
	{ "Man",			"Woman"				},

	{ "Minor Titan",               "Minor Titan"              },
	{ "Minor Titan",               "Minor Titan"              },
	{ "Minor Titan",               "Minor Titan"              },
	{ "Minor Titan",               "Minor Titan"              },
	{ "Minor Titan",               "Minor Titan"              },

	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	//10
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },

	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	//20
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },

	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	//30
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },

	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	{ "Titan",                     "Titan"              },
	//40
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },

	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	//50
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },

	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	{ "Titan",                    "Titan"              },
	//60
	{ "Titan Major",              "Titan Major"              },
	{ "Titan Major",              "Titan Major"              },
	{ "Titan Major",              "Titan Major"              },
	{ "Titan Major",              "Titan Major"              },
	{ "Titan Major",              "Titan Major"              },

	{ "Titan Major",                 "Titan Major"              },
	{ "Titan Major",                 "Titan Major"              },
	{ "Titan Major",                 "Titan Major"              },
	{ "Titan Major",                 "Titan Major"              },
	{ "Titan Major",                 "Titan Major"              },
	//70
        { "Master Titan",          "Master Titan"              },
        { "Master Titan",          "Master Titan"              },
        { "Master Titan",          "Master Titan"              },
	{ "Titan Hero",		       "Titan Heroine"   	        },
	/*74*/
	{ "Titanic Avatar ",	       "Titanic Avatar"		},
	{ "Titanic Demigod ",	       "Anglelic Demigoddess"	},
	{ "Titanic Deity ",	       "Anglelic Deity"		},
	{ "Anglic Supremity ",	       "Anglelic Supremity"	},
        { "Creator",                   "Creator"                },
	{ "Implementor",	       "Implementress"          }
    },
    //demon - 12
    {
	{ "Man",			"Woman"				},

	{ "Imp",                     "Imp"              },
	{ "Imp",                     "Imp"              },
	{ "Imp",                     "Imp"              },
	{ "Imp",                     "Imp"              },
	{ "Imp",                     "Imp"              },

	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	//10
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },

	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	//20
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },

	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	//30
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },

	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	{ "Demon",                     "Demon"              },
	//40
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },

	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	//50
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },

	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	{ "Greater Demon",             "Greater Demon"              },
	//60
	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },

	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },
	{ "ArchDemon",                 "ArchDemon"              },
	//70
        { "Master ArchDemon",          "Master ArchDemon"              },
        { "Master ArchDemon",          "Master ArchDemon"              },
        { "Master ArchDemon",          "Master ArchDemon"              },
	{ "Demon Hero",		       "Demon Heroine"   	        },
	/*74*/
	{ "Demonic Avatar ",	       "Demonic Avatar"		},
	{ "Demonic Demigod ",	       "Anglelic Demigoddess"	},
	{ "Demonic Deity ",	       "Anglelic Deity"		},
	{ "Anglic Supremity ",	       "Anglelic Supremity"	},
        { "Creator",                   "Creator"                },
	{ "Implementor",	       "Implementress"          }
    },


};



/*
 * Attribute bonus tables.
 */
const	struct	str_app_type	str_app		[26]		=
{
    { -5, -4,   0,  0 },  /* 0  */
    { -5, -4,   3,  1 },  /* 1  */
    { -3, -2,   3,  2 },
    { -3, -1,  10,  3 },  /* 3  */
    { -2, -1,  25,  4 },
    { -2, -1,  55,  5 },  /* 5  */
    { -1,  0,  80,  6 },
    { -1,  0,  90,  7 },
    {  0,  0, 100,  8 },
    {  0,  0, 100,  9 },
    {  0,  0, 115, 10 }, /* 10  */
    {  0,  0, 115, 11 },
    {  0,  0, 130, 12 },
    {  0,  0, 130, 13 }, /* 13  */
    {  0,  1, 140, 14 },
    {  1,  1, 150, 15 }, /* 15  */
    {  1,  2, 165, 16 },
    {  2,  3, 180, 22 },
    {  2,  3, 200, 25 }, /* 18  */
    {  3,  4, 225, 30 },
    {  3,  5, 250, 35 }, /* 20  */
    {  4,  6, 300, 40 },
    {  4,  6, 350, 45 },
    {  5,  7, 400, 50 },
    {  5,  8, 450, 55 },
    {  6,  9, 500, 60 }  /* 25   */
};



const	struct	int_app_type	int_app		[26]		=
{
    {  3 },	/*  0 */
    {  5 },	/*  1 */
    {  7 },
    {  8 },	/*  3 */
    {  9 },
    { 10 },	/*  5 */
    { 11 },
    { 12 },
    { 13 },
    { 15 },
    { 17 },	/* 10 */
    { 19 },
    { 22 },
    { 25 },
    { 28 },
    { 31 },	/* 15 */
    { 34 },
    { 37 },
    { 40 },	/* 18 */
    { 44 },
    { 49 },	/* 20 */
    { 55 },
    { 60 },
    { 70 },
    { 80 },
    { 85 }	/* 25 */
};



const	struct	wis_app_type	wis_app		[26]		=
{
    { 0 },	/*  0 */
    { 0 },	/*  1 */
    { 0 },
    { 0 },	/*  3 */
    { 0 },
    { 1 },	/*  5 */
    { 1 },
    { 1 },
    { 1 },
    { 1 },
    { 1 },	/* 10 */
    { 1 },
    { 1 },
    { 1 },
    { 1 },
    { 2 },	/* 15 */
    { 2 },
    { 2 },
    { 3 },	/* 18 */
    { 3 },
    { 3 },	/* 20 */
    { 3 },
    { 4 },
    { 4 },
    { 4 },
    { 5 }	/* 25 */
};



const	struct	dex_app_type	dex_app		[26]		=
{
    {   60 },   /* 0 */
    {   50 },   /* 1 */
    {   50 },
    {   40 },
    {   30 },
    {   20 },   /* 5 */
    {   10 },
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 10 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    { - 10 },   /* 15 */
    { - 15 },
    { - 20 },
    { - 30 },
    { - 40 },
    { - 50 },   /* 20 */
    { - 60 },
    { - 75 },
    { - 90 },
    { -105 },
    { -120 }    /* 25 */
};


const	struct	con_app_type	con_app		[26]		=
{
    { -4, 20 },   /*  0 */
    { -3, 25 },   /*  1 */
    { -2, 30 },
    { -2, 35 },	  /*  3 */
    { -1, 40 },
    { -1, 45 },   /*  5 */
    { -1, 50 },
    {  0, 55 },
    {  0, 60 },
    {  0, 65 },
    {  0, 70 },   /* 10 */
    {  0, 75 },
    {  0, 80 },
    {  0, 85 },
    {  0, 88 },
    {  1, 90 },   /* 15 */
    {  2, 95 },
    {  2, 97 },
    {  3, 99 },   /* 18 */
    {  3, 99 },
    {  4, 99 },   /* 20 */
    {  4, 99 },
    {  5, 99 },
    {  6, 99 },
    {  7, 99 },
    {  8, 99 }    /* 25 */
};



/*
 * Liquid properties.
 * Used in world.obj.
 */
const	struct	liq_type	liq_table	[]	=
{
/*    name		   color	proof, full, thirst, food, ssize */
    { "water",		   "clear",	{   0,  1,   10,     0,    16 }},
    { "beer",		   "amber",	{  12,  1,   8,      1,    12 }},
    { "red wine",	   "burgundy",	{  30,  1,   8,      1,     5 }},
    { "ale",		   "brown",	{  15,  1,   8,      1,    12 }},
    { "dark ale",	   "dark",	{  16,  1,   8,      1,    12 }},

    { "whisky",		   "golden",	{ 120,  1,   5,      0,     2 }},
    { "lemonade",	   "pink",	{   0,  1,   9,      2,    12 }},
    { "firebreather",	   "boiling",	{ 190,  0,   4,      0,     2 }},
    { "local specialty",   "clear",	{ 151,  1,   3,      0,     2 }},
    { "slime mold juice",  "green",	{   0,  2,  -8,      1,     2 }},
    { "milk",		   "white",	{   0,  2,   9,      3,    12 }},
    { "tea",		   "tan",	{   0,  1,   8,      0,     6 }},
    { "coffee",		   "black",	{   0,  1,   8,      0,     6 }},
    { "blood",		   "red",	{   0,  2,  -1,      2,     6 }},
    { "salt water",	   "clear",	{   0,  1,  -2,      0,     1 }},

    { "coke",		   "brown",	{   0,  2,   9,      2,    12 }}, 
    { "root beer",	   "brown",	{   0,  2,   9,      2,    12 }},
    { "elvish wine",	   "green",	{  35,  2,   8,      1,     5 }},
    { "white wine",	   "golden",	{  28,  1,   8,      1,     5 }},
    { "champagne",	   "golden",	{  32,  1,   8,      1,     5 }},

    { "mead",		   "golden",    {  34,  2,   8,      2,    12 }},
    { "rose wine",	   "pink",	{  26,  1,   8,      1,     5 }},
    { "benedictine wine",  "burgundy",	{  40,  1,   8,      1,     5 }},
    { "vodka",		   "clear",	{ 130,  1,   5,      0,     2 }},
    { "cranberry juice",   "red",	{   0,  1,   9,      2,    12 }},

    { "orange juice",	   "orange",	{   0,  2,   9,      3,    12 }}, 
    { "absinthe",	   "green",	{ 200,  1,   4,      0,     2 }},
    { "brandy",		   "golden",	{  80,  1,   5,      0,     4 }},
    { "aquavit",	   "clear",	{ 140,  1,   5,      0,     2 }},
    { "schnapps",	   "clear",	{  90,  1,   5,      0,     2 }},

    { "icewine",	   "purple",	{  50,  2,   6,      1,     5 }},
    { "amontillado",	   "burgundy",	{  35,  2,   8,      1,     5 }},
    { "sherry",		   "red",	{  38,  2,   7,      1,     5 }},
    { "framboise",	   "red",	{  50,  1,   7,      1,     5 }},
    { "rum",		   "amber",	{ 151,  1,   4,      0,     2 }},

    { "cordial",	   "clear",	{ 100,  1,   5,      0,     2 }},
    { NULL,		    NULL,	{   0,  0,   0,      0,     0 }}
};



/** -- SKILLS & SPELLS -- **/


/*
 * The skill and spell table.
 * Slot numbers must never be changed as they appear in #OBJECTS sections.
 */
#define SLOT(n)	n

const	struct	skill_type	skill_table	[MAX_SKILL]	=
{

/*
 * Magic spells.
 */

  {
    "reserved",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 99, 99, 99, 99, 99,  99, 99, 99, 99, 99,  99, 99, 99 },	
    { 99, 99, 99, 99, 99,  99, 99, 99, 99, 99,  99, 99, 99 },
    0,			TAR_IGNORE,		POS_STANDING,
    NULL,		SLOT( 0),	 0,	 0,
    "",			"",		""
  },
  
  {
    "acid blast",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 40, -1, -1, -1, -1,  39, -1, -1, -1, -1,  -1, -1, -1 },  	
    {  1,  2,  2,  2,  2,   1,  2,  2,  2,  2,   1,  2,  1 },
    spell_acid_blast,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(70),	20,	12,
    "acid blast",	"!Acid Blast!"
  },
  
  {
    "armor",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  7, -1, -1, -1, -1,   6, -1, -1, -1, -1,  -1, -1, -1 },  	     
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_armor,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT( 1),	 5,	12,
    "",			"You feel less armored.",	""
  },
  
  {
    "bless",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  7, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_bless,	TAR_OBJ_CHAR_DEF,	POS_STANDING,
    NULL,		SLOT( 3),	 5,	12,
    "",			"You feel less righteous.", "$p's holy aura fades."
  },
  
  {
    "blindness",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 12,  8, -1, -1, -1,  11,  7, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_blindness,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    &gsn_blindness,	SLOT( 4),	 5,	12,
    "",			"You can see again.",	""
  },
  
  {
    "burning hands",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 10, -1, -1, -1, -1,   9, -1, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_burning_hands,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT( 5),	15,	12,
    "burning hands",	"!Burning Hands!", 	""
  },
  
  {
    "call lightning",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 18, -1, -1, -1,  -1, 17, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_call_lightning,	TAR_IGNORE,		POS_FIGHTING,
    NULL,			SLOT( 6),	15,	12,
    "lightning bolt",	"!Call Lightning!",	""
  },
  
  {   
    "calm",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 48, 16, -1, -1, -1,  47, 15, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_calm,		TAR_IGNORE,		POS_FIGHTING,
    NULL,		SLOT(509),	30,	12,
    "",			"You have lost your peace of mind.",	""
  },
  
  {
    "cancellation",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 18, 26, -1, -1, -1,  17, 25, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cancellation,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(507),	20,	12,
    ""			"!cancellation!",	""
  },
  
  {
    "cause critical",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 13, -1, -1, -1,  -1, 12, -1, -1, -1,  -1, -1, 11 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cause_critical,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(63),	20,	12,
    "spell",		"!Cause Critical!",	""
  },
  
  {
    "cause light",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  1, -1, -1, -1,  -1,  1, -1, -1, -1,  -1, -1,  1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cause_light,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(62),	15,	12,
    "spell",		"!Cause Light!",	""
  },
  
  {
    "cause serious",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  7, -1, -1, -1,  -1,  6, -1, -1, -1,  -1, -1,  5 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cause_serious,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(64),	17,	12,
    "spell",		"!Cause Serious!",	""
  },
  
  {   
    "chain lightning",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 35, -1, -1, -1, -1,  34, -1, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_chain_lightning,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(500),	25,	12,
    "lightning",		"!Chain Lightning!",	""
  }, 
  
  {
    "change sex",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_change_sex,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(82),	15,	12,
    "",			"Your body feels familiar again.",	""
  },
  
  {
    "charm person",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 20, -1, -1, -1, -1,  19, -1, -1, -1, -1,  -1, 18, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_charm_person,	TAR_CHAR_OFFENSIVE,	POS_STANDING,
    &gsn_charm_person,	SLOT( 7),	 5,	12,
    "",			"You feel more self-confident.",	""
  },
  
  {
    "chill touch",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  5, -1, -1, -1, -1,   4, -1, -1, -1, -1,  -1, -1,  3 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_chill_touch,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT( 8),	10,	12,
    "chilling touch",	"You feel less cold.",	""
  },
  
  {
    "color spray",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 25, -1, -1, -1, -1,  19, -1, -1, -1, -1,  -1, 18, -1 },      
    {  1,  2,  2,  2,  2,   1,  2,  2,  2,  2,   1,  2,  1 },
    spell_colour_spray,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(10),	15,	12,
    "color spray",		"!Color Spray!",	""
  },
  
  {
    "continual light",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  6,  4, -1, -1, -1,   5,  3, -1, -1, -1,   2,  2,  2 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_continual_light,	TAR_IGNORE,		POS_STANDING,
    NULL,			SLOT(57),	 7,	12,
    "",			"!Continual Light!",	""
  },
  
  {
    "control weather",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 19, -1, -1, -1,  -1, 18, -1, -1, -1,  -1, 17, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_control_weather,	TAR_IGNORE,		POS_STANDING,
    NULL,			SLOT(11),	25,	12,
    "",			"!Control Weather!",	""
  },
  
  {
    "create food",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  5, -1, -1, -1,  -1,  4, -1, -1, -1,   4,  4,  4 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_create_food,	TAR_IGNORE,		POS_STANDING,
    NULL,			SLOT(12),	 5,	12,
    "",			"!Create Food!",	""
  },
  
  {
    "create rose",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 11, -1, -1, -1,  -1, 10, -1, -1, -1,   9,  9,  9 },  	
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_create_rose,	TAR_IGNORE,		POS_STANDING,
    NULL,		SLOT(511),	30, 	12,
    "",			"!Create Rose!",	""
  },  
  
  {
    "create spring",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 17, -1, -1, 27,  -1, 16, -1, -1, 21,  15, 15, 15 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_create_spring,	TAR_IGNORE,		POS_STANDING,
    NULL,			SLOT(80),	20,	12,
    "",			"!Create Spring!",	""
  },
  
  {
    "create water",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  3, -1, -1, 13,  -1,  2, -1, -1,  7,   1, -1,  1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_create_water,	TAR_OBJ_INV,		POS_STANDING,
    NULL,		SLOT(13),	 5,	12,
    "",			"!Create Water!",	""
  },
  
  {
    "cure blindness",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  6, -1, -1, -1,  -1,  5, -1, -1, -1,   4, -1, -1 },     
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cure_blindness,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(14),	 5,	12,
    "",			"!Cure Blindness!",	""
  },
  
  {
    "cure critical",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 13, -1, -1, -1,  -1, 12, -1, -1, -1,  11, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cure_critical,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(15),	20,	12,
    "",			"!Cure Critical!",	""
  },
  
  {
    "cure disease",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 13, -1, -1, -1,  -1, 12, -1, -1, 17,  11, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cure_disease,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT(501),	20,	12,
    "",			"!Cure Disease!",	""
  },
  
  {
    "cure light",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  1, -1, -1, -1,  -1,  1, -1, -1, -1,   1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cure_light,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(16),	10,	12,
    "",			"!Cure Light!",		""
  },
  
  {
    "cure poison",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 14, -1, -1, -1,  -1, 13, -1, -1, -1,  12, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cure_poison,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT(43),	 5,	12,
	"",			"!Cure Poison!",	""
  },
  
  {
    "cure serious",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  7, -1, -1, -1,  -1,  6, -1, -1, -1,   5, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_cure_serious,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(61),	15,	12,
    "",			"!Cure Serious!",	""
  },
  
  {
    "curse",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 18, 18, -1, -1, -1,  17, 17, -1, -1, -1,  -1, -1, 16 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_curse,	TAR_OBJ_CHAR_OFF,	POS_FIGHTING,
    &gsn_curse,		SLOT(17),	20,	12,
    "curse",		"The curse wears off.", 
    "$p is no longer impure."
  },
  
  {
    "demonfire",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 34, -1, -1, -1,  -1, 33, -1, -1, -1,  -1, -1, 32 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_demonfire,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(505),	20,	12,
    "torments",		"!Demonfire!",		""
  },	
  
  {
    "detect evil",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  4, -1, -1, -1,  -1,  3, -1, -1,  8,   2, -1,  2 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_detect_evil,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,		SLOT(18),	 5,	12,
    "",			"The red in your vision disappears.",	""
  },
  
  {
    "detect good",  
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  4, -1, -1, -1,  -1,  3, -1, -1,  8,   2, -1,  2 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_detect_good,      TAR_CHAR_SELF,          POS_STANDING,
    NULL,                   SLOT(513),        5,     12,
    "",                     "The gold in your vision disappears.",	""
  },
  
  {
    "detect hidden",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 15, -1, -1, -1, -1,  14, -1, -1, -1, -1,  -1, 13, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_detect_hidden,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,			SLOT(44),	 5,	12,
    "",			"You feel less aware of your surroundings.",	
    ""
  },
  
  {
    "detect invis",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  3, -1, -1, -1, -1,   2, -1, -1, -1, -1,  -1,  1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_detect_invis,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,		SLOT(19),	 5,	12,
    "",			"You no longer see invisible objects.",
    ""
  },
  
  {
    "detect magic",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  2, -1, -1, -1, -1,   1, -1, -1, -1, -1,  -1,  1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_detect_magic,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,		SLOT(20),	 5,	12,
    "",			"The detect magic wears off.",	""
  },
  
  {
    "detect poison",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  7, -1, -1, -1,  -1,  6, -1, -1, -1,   5,  5,  5 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_detect_poison,	TAR_OBJ_INV,		POS_STANDING,
    NULL,			SLOT(21),	 5,	12,
    "",			"!Detect Poison!",	""
  },
  
  {
    "dispel evil",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 15, -1, -1, -1,  -1, 14, -1, -1, -1,  14, -1, 14 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_dispel_evil,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(22),	15,	12,
    "dispel evil",	"!Dispel Evil!",	""
  },
  
  {
    "dispel good",    
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 15, -1, -1, -1,  -1, 14, -1, -1, -1,  14, -1, 14 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_dispel_good,      TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
    NULL,                   SLOT(512),      15,     12,
    "dispel good",          "!Dispel Good!",	""
  },
  
  {
    "dispel magic",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 16, 24, -1, -1, -1,  15, 23, -1, -1, -1,  22, 21, 22 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_dispel_magic,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(59),	15,	12,
    "",			"!Dispel Magic!",	""
  },
  
  {
    "earthquake",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 10, -1, -1, -1,  -1,  9, -1, -1, -1,   8, -1,  8 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_earthquake,	TAR_IGNORE,		POS_FIGHTING,
    NULL,		SLOT(23),	15,	12,
    "earthquake",	"!Earthquake!",		""
  },
  
  {
    "enchant armor",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 16, -1, -1, -1, -1,  15, -1, -1, -1, -1,  -1, 14, -1 }, 	
    {  2,  2,  4,  4,  4,   1,  1,  4,  4,  2,   1,  3,  1 },
    spell_enchant_armor,	TAR_OBJ_INV,		POS_STANDING,
    NULL,			SLOT(510),	100,	24,
    "",			        "!Enchant Armor!",	""
  },
  
  {
    "enchant weapon",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 17, -1, -1, -1, -1,  16, -1, -1, -1, -1,  -1, 15, -1 },      
    {  2,  2,  4,  4,  2,   1,  1,  4,  4,  2,   1,  3,  1 },
    spell_enchant_weapon,	TAR_OBJ_INV,		POS_STANDING,
    NULL,			SLOT(24),	100,	24,
    "",			"!Enchant Weapon!",	""
  },
  
  {
    "energy drain",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 46, -1, -1, -1, -1,  45, -1, -1, -1, -1,  -1, -1, 44 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_energy_drain,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(25),	35,	12,
    "energy drain",		"!Energy Drain!",	""
  },
  
  {
    "faerie fire",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  6,  3, -1, -1, -1,   5,  4, -1, -1, -1,   3,  3,  3 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_faerie_fire,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(72),	 5,	12,
    "faerie fire",		"The pink aura around you fades away.",
    ""
  },
  
  {
    "faerie fog",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 21, -1, -1, -1,  -1, 20, -1, -1, -1,  19, -1, 19 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_faerie_fog,	TAR_IGNORE,		POS_STANDING,
    NULL,		SLOT(73),	12,	12,
    "faerie fog",	"!Faerie Fog!",		""
  },
  
  {
    "farsight",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 14, 16, -1, -1, -1,  13, 15, -1, -1, -1,  12, 12, 12 }, 	
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_farsight,	TAR_IGNORE,		POS_STANDING,
    NULL,		SLOT(521),	36,	20,
    "farsight",		"!Farsight!",		""
  },	
  
  {
    "fireball",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 30, -1, -1, -1, -1,  29, -1, -1, -1, -1,  -1, -1, -1 },      
    {  1,  2,  2,  2,  2,   1,  2,  2,  2,  1,   1,  2,  1 },
    spell_fireball,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(26),	15,	12,
    "fireball",		"!Fireball!",		""
  },
  
  {
    "fireproof",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 13, 12, -1, -1, -1,  12, 11, -1, -1, -1,  11, 11, 11 }, 	
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_fireproof,	TAR_OBJ_INV,		POS_STANDING,
    NULL,		SLOT(523),	10,	12,
    "",			"",	"$p's protective aura fades."
  },
  
  {
    "flamestrike",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 20, -1, -1, -1,  -1, 19, -1, -1, -1,  18, -1, 18 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_flamestrike,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(65),	20,	12,
    "flamestrike",	"!Flamestrike!",		""
  },
  
  {
    "fly",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 10, 18, -1, -1, -1,   9, 17, -1, -1, -1,  16,  9, 16 },      
    { 1 ,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_fly,		TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT(56),	10,	18,
    "",			"You slowly float to the ground.",	""
  },

  {
    "floating disc",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  4, -1, -1, -1, -1,   3, -1, -1, -1, -1,  -1,  2, -1 }, 	
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_floating_disc,	TAR_IGNORE,		POS_STANDING,
    NULL,			SLOT(522),	40,	24,
    "",			"!Floating disc!",	""
  },
  
  {
    "frenzy",  
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 24, -1, -1, -1,  -1, 23, -1, -1, -1,  22, -1, 22 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_frenzy,           TAR_CHAR_DEFENSIVE,     POS_STANDING,
    NULL,                   SLOT(504),      30,     24,
    "",                     "Your rage ebbs.",	""
  },
  
  {
    "gate",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 17, -1, -1, -1,  -1, 16, -1, -1, -1,  15, -1, 15 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_gate,		TAR_IGNORE,		POS_FIGHTING,
    NULL,		SLOT(83),	80,	12,
    "",			"!Gate!",		""
  },
  
  {
    "giant strength",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 11, -1, -1, -1, -1,  10, -1, -1, -1, -1,  -1,  9, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_giant_strength,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,			SLOT(39),	20,	12,
    "",			"You feel weaker.",	""
  },
  
  {
    "harm",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 23, -1, -1, -1,  -1, 22, -1, -1, -1,  -1, -1, 21 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_harm,		TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(27),	35,	12,
    "harm spell",	"!Harm!,		"""
  },
  
  {
    "haste",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 21, -1, -1, -1, -1,  20, -1, -1, -1, -1,  -1, 19, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_haste,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(502),	30,	12,
    "",			"You feel yourself slow down.",	""
  },
  
  {
    "heal",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 21, -1, -1, -1,  -1, 20, -1, -1, -1,  19, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_heal,		TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(28),	50,	12,
    "",			"!Heal!",		""
    },
  
  {
    "heat metal",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 16, -1, -1, -1,  -1, 15, -1, -1, -1,  14, -1, 14 }, 	
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_heat_metal,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(516), 	25,	18,
    "spell",		"!Heat Metal!",		""
  },
  
  {
    "holy word",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 36, -1, -1, -1,  -1, 35, -1, -1, -1,  34, -1, -1 },
    {  2,  2,  4,  4,  4,   1,  1,  4,  4,  2,   1,  3,  1 }, 
    spell_holy_word,	TAR_IGNORE,	POS_FIGHTING,
    NULL,		SLOT(506), 	200,	24,
    "divine wrath",	"!Holy Word!",		""
  },

  {
    "identify",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 15, 16, -1, -1, -1,  14, 15, -1, -1, -1,  -1, 13, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_identify,		TAR_OBJ_INV,		POS_STANDING,
    NULL,			SLOT(53),	12,	24,
    "",			"!Identify!",		""
  },
  
  {
    "infravision",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  9, 13, -1, -1, -1,   8, 12, -1, -1, -1,  11,  7, 11 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_infravision,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT(77),	 5,	18,
    "",			"You no longer see in the dark.",	""
  },
  
  {
    "invisibility",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  5, -1, -1, -1, -1,   4, -1, -1, -1, -1,  -1,  3, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_invis,	TAR_OBJ_CHAR_DEF,	POS_STANDING,
    &gsn_invis,		SLOT(29),	 5,	12,
    "",			"You are no longer invisible.",		
    "$p fades into view."
  },
  
  {
    "know alignment",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 12,  9, -1, -1, -1,  11,  8, -1, -1, -1,  10,  9, 10 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_know_alignment,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(58),	 9,	12,
    "",			"!Know Alignment!",	""
  },
  
  {
    "lightning bolt",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 20, -1, -1, -1, -1,  19, -1, -1, -1, -1,  -1, 22, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_lightning_bolt,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(30),	15,	12,
    "lightning bolt",	"!Lightning Bolt!",	""
  },
  
  {
    "locate object",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  9, 15, -1, -1, -1,   8, 14, -1, -1, -1,  13,  8, 13 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_locate_object,	TAR_IGNORE,		POS_STANDING,
    NULL,			SLOT(31),	20,	18,
    "",			"!Locate Object!",	""
  },
  
  {
    "magic missile",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1, -1, -1, -1, -1,   1, -1, -1, -1, -1,  -1,  1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_magic_missile,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(32),	15,	12,
    "magic missile",	"!Magic Missile!",	""
  },

  {
    "mass healing",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 38, -1, -1, -1,  -1, 37, -1, -1, -1,  36, -1, -1 },
    {  2,  2,  4,  4,  4,   1,  1,  4,  4,  2,   1,  3,  1 }, 
    spell_mass_healing,	TAR_IGNORE,		POS_STANDING,
    NULL,		SLOT(508),	100,	36,
    "",			"!Mass Healing!",	""
  },
  
  {
    "mass invis",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 22, -1, -1, -1, -1,  21, -1, -1, -1, -1,  -1, 20, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_mass_invis,	TAR_IGNORE,		POS_STANDING,
    &gsn_mass_invis,	SLOT(69),	20,	24,
    "",			"You are no longer invisible.",		""
  },
  
  {
    "nexus",    
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 40, -1, -1, -1, -1,  39, -1, -1, -1, -1,  -1, 38, -1 },
    {  2,  2,  4,  4,  4,   1,  1,  4,  4,  2,   1,  3,  1 },  
    spell_nexus,            TAR_IGNORE,             POS_STANDING,
    NULL,                   SLOT(520),       150,   36,
    "",                     "!Nexus!",		""
  },
  
  {
    "pass door",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 24, 32, -1, -1, -1,  23, 31, -1, -1, -1,  23, 30, 23 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_pass_door,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,		SLOT(74),	20,	12,
    "",			"You feel solid again.",	""
  },
  
  {
    "plague",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 23, 17, -1, -1, -1,  22, 16, -1, -1, -1,  -1, -1, 15 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_plague,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    &gsn_plague,	SLOT(503),	20,	12,
    "sickness",		"Your sores vanish.",	""
  },
  
  {
    "poison",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 17, 12, -1, -1, -1,  16, 11, -1, -1, -1,  -1, -1, 10 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_poison,	TAR_OBJ_CHAR_OFF,	POS_FIGHTING,
    &gsn_poison,	SLOT(33),	10,	12,
    "poison",		"You feel less sick.",	
    "The poison on $p dries up."
  },
  
  {
    "portal",     
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 35, -1, -1, -1, -1,  34, -1, -1, -1, -1,  -1, 33, -1 }, 
    {  2,  2,  4,  4,  4,   1,  1,  4,  4,  2,   1,  3,  1 },  
    spell_portal,           TAR_IGNORE,             POS_STANDING,
    NULL,                   SLOT(519),       100,     24,
    "",                     "!Portal!",		""
  },
  
  {
    "protection evil",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  9, -1, -1, -1,  -1,  8, -1, -1, -1,   7, -1,  7 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_protection_evil,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,			SLOT(34), 	5,	12,
    "",			"You feel less protected.",	""
  },
  
  {
    "protection good", 
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  9, -1, -1, -1,  -1,  8, -1, -1, -1,   7, -1,  7 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_protection_good,  TAR_CHAR_SELF,          POS_STANDING,
    NULL,                   SLOT(514),       5,     12,
    "",                     "You feel less protected.",	""
  },
   
  {
    "ray of truth", 
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 35, -1, -1, -1,  -1, 34, -1, -1, -1,  33, -1, 33 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_ray_of_truth,     TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
    NULL,                   SLOT(518),      20,     12,
    "ray of truth",         "!Ray of Truth!",	""
  },

  {
    "recharge",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  9, -1, -1, -1, -1,   8, -1, -1, -1, -1,  -1,  7, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_recharge,	TAR_OBJ_INV,		POS_STANDING,
    NULL,		SLOT(517),	60,	24,
    "",			"!Recharge!",		""
  },

  {
    "refresh",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  8,  5, -1, -1, -1,   7,  4, -1, -1, -1,   3, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_refresh,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT(81),	12,	18,
    "refresh",		"!Refresh!",		""
  },

  {
    "remove curse",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 18, -1, -1, -1,  -1, 17, -1, -1, -1,  16, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_remove_curse,	TAR_OBJ_CHAR_DEF,	POS_STANDING,
    NULL,		SLOT(35),	 5,	12,
    "",			"!Remove Curse!",	""
  },

  {
    "sanctuary",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 20, -1, -1, -1,  -1, 19, -1, -1, -1,  18, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_sanctuary,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    &gsn_sanctuary,	SLOT(36),	75,	12,
    "",			"The white aura around your body fades.",
    ""
  },

  {
    "shield",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 20, -1, -1, -1, -1,  19, -1, -1, -1, -1,  -1, 18, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_shield,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT(67),	12,	18,
    "",			"Your force shield shimmers then fades away.",
    ""
  },

  {
    "shocking grasp",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 15, -1, -1, -1, -1,  14, -1, -1, -1, -1,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_shocking_grasp,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(53),	15,	12,
    "shocking grasp",	"!Shocking Grasp!",	""
  },

  {
    "sleep",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 10, -1, -1, -1, -1,   9, -1, -1, -1, -1,  -1,  8, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_sleep,	TAR_CHAR_OFFENSIVE,	POS_STANDING,
    &gsn_sleep,		SLOT(38),	15,	12,
    "",			"You feel less tired.",	""
  },

  {
    "slow",    
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 23, 30, -1, -1, -1,  22, 29, -1, -1, -1,  -1, 21, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_slow,             TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
    NULL,                   SLOT(515),      30,     12,
    "",                     "You feel yourself speed up.",	""
  },

  {
    "stone skin",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 25, -1, -1, -1, -1,  24, -1, -1, -1, -1,  -1, 23, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_stone_skin,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,		SLOT(66),	12,	18,
    "",			"Your skin feels soft again.",	""
  },

  {
    "summon",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 24, -1, -1, -1, -1,  23, -1, -1, -1, -1,  -1, 22, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_summon,	TAR_IGNORE,		POS_STANDING,
    NULL,		SLOT(40),	50,	12,
    "",			"!Summon!",		""
  },

  {
    "teleport",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 13, -1, -1, -1, -1,  12, -1, -1, -1, -1,  -1, 11, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_teleport,	TAR_CHAR_SELF,		POS_FIGHTING,
    NULL,	 	SLOT( 2),	35,	12,
    "",			"!Teleport!",		""
  },

  {
    "ventriloquate",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1, -1, -1, -1, -1,   1, -1, -1, -1, -1,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_ventriloquate,	TAR_IGNORE,		POS_STANDING,
    NULL,			SLOT(41),	 5,	12,
    "",			"!Ventriloquate!",	""
  },

  {
    "weaken",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 11, 14, -1, -1, -1,  10, 13, -1, -1, -1,  -1, 12, 12 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_weaken,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(68),	20,	12,
    "spell",		"You feel stronger.",	""
  },

  {
    "word of recall",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 32, 28, -1, -1, -1,  21, 27, -1, -1, -1,  26, 26, 26 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_word_of_recall,	TAR_CHAR_SELF,		POS_RESTING,
    NULL,			SLOT(42),	 5,	12,
    "",			"!Word of Recall!",	""
  },

  /*
   * Dragon breath
   */
  {
    "acid breath",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 31, -1, -1, -1, -1,  30, -1, -1, -1, -1,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_acid_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(200),	100,	24,
    "blast of acid",	"!Acid Breath!",	""
  },

  {
    "fire breath",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 40, -1, -1, -1, -1,  39, -1, -1, -1, -1,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_fire_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(201),	200,	24,
    "blast of flame",	"The smoke leaves your eyes.",	""
  },

  {
    "frost breath",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 34, -1, -1, -1, -1,  33, -1, -1, -1, -1,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_frost_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(202),	125,	24,
    "blast of frost",	"!Frost Breath!",	""
  },

  {
    "gas breath",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 39, -1, -1, -1, -1,  38, -1, -1, -1, -1,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_gas_breath,	TAR_IGNORE,		POS_FIGHTING,
    NULL,		SLOT(203),	175,	24,
    "blast of gas",	"!Gas Breath!",		""
  },

  {
    "lightning breath",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 37, -1, -1, -1, -1,  36, -1, -1, -1, -1,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_lightning_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(204),	150,	24,
    "blast of lightning",	"!Lightning Breath!",	""
  },

  
  /* MEK 
   * 
   * New Spells here
   */
  {
    "rejuvenate",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  8, -1, -1, -1,  -1,  7, -1, -1, -1,   6, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_refresh,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,		SLOT(501),	25,	30,
    "rejuvenate",	"!Rejuvenate!",		""
  },
  
  {
    "barkskin",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  0, 35, -1, -1, 30,  -1, 34, -1, -1, 20,  -1, -1, -1 }, 
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_bark_skin,	TAR_CHAR_SELF,		POS_STANDING,
    NULL,		SLOT(502),	12,	20,
    "",			"Your layer of bark disappears.",	""
  },

  {
    "goodberry",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 25, -1, -1, 35,  -1, 24, -1, -1, 23,  -1, -1, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_create_berry,	TAR_IGNORE,		POS_STANDING,
    NULL,		SLOT(503),	7,	16,
    "",			"!Goodberry!",	""
  },

  /*
   * new Evocation spells
   */
  {
    "shockwave",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 45, -1, -1, -1, -1,  44, -1, -1, -1, -1,  -1, -1, -1 },  	
    {  1,  2,  2,  2,  2,   1,  1,  2,  2,  2,   1,  2,  1 },
    spell_shockwave,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(504),	25,	12,
    "shockwave",	"!Shockwave!"
  },

  {
    "cone of cold",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 50, -1, -1, -1, -1,  49, -1, -1, -1, -1,  -1, -1, -1 },  	
    {  1,  2,  2,  2,  2,   1,  1,  2,  2,  2,   1,  2,  1 },
    spell_cone_of_cold,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(505),	30,	12,
    "cone of cold",	"!Cone of Cold!"
  },

  {
    "force bolt",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 55, -1, -1, -1, -1,  54, -1, -1, -1, -1,  -1, -1, -1 },  	
    {  1,  2,  2,  2,  2,   1,  1,  2,  2,  2,   1,  2,  1 },
    spell_force_bolt,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,		SLOT(506),	35,	12,
    "force bolt",	"!Force Bolt!"
  },

  {
    "meteor swarm",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1, -1, -1,  60, -1, -1, -1, -1,  -1, -1, -1 },  	
    {  1,  2,  2,  2,  2,   1,  1,  2,  2,  2,   1,  2,  1 },
    spell_meteor_swarm,	TAR_IGNORE,	POS_FIGHTING,
    NULL,		SLOT(507),	40,	14,
    "meteor swarm",	"!Meteor Swarm!"
  },

  /*
   * New Necromantic spells
   */
  {
    "animate dead",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 37, -1, -1, -1, -1,  34, -1, -1, -1, -1,  -1, 27, -1 },      
    {  2,  2,  4,  4,  4,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_animate_dead,	TAR_IGNORE,	POS_STANDING,
    NULL,	SLOT(508),	90,	16,
    "",		"!Animate Dead!",	""
  },

  {
    "vampiric touch",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 27, -1, -1, -1, -1,  26, -1, -1, -1, -1,  -1, 25, -1 },      
    {  1,  1,  2,  2,  2,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_vampiric_touch,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
    NULL,			SLOT(509),	20,	12,
    "vampiric touch",		"!Vampiric Touch!",	""
  },

  {
    "morph",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1, -1, -1,  -1, -1, -1, -1, 30,  -1, -1, -1 },      
    {  2,  2,  4,  4,  3,   1,  1,  2,  2,  1,   1,  2,  1 },
    spell_morph, 	TAR_CHAR_DEFENSIVE,	POS_STANDING,
    NULL,			SLOT(510),	90,	12,
    "vampiric touch",		"You return to your normal form.",	""
  },
  

  

  /* combat and weapons skills */

  {
    "axe",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1,  1,  1,  -1, -1, -1,  1, -1,   1,  1,  1 }, 
    {  0,  0,  5,  4,  0,   0,  0,  2,  2,  0,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_axe,               SLOT( 0),       0,      0,
    "",                     "!Axe!",		""
  },

  {
    "dagger",  
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1, -1,  1,  1,  1,   1, -1,  1,  1,  1,   1,  1,  1 }, 
    {  2,  0,  2,  2,  2,   2,  0,  1,  1,  2,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_dagger,            SLOT( 0),       0,      0,
    "",                     "!Dagger!",		""
  },
 
  {
    "flail",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  1,  1,  1,  1,  -1,  1,  1,  1,  1,   1,  1,  1 }, 
    {  0,  3,  6,  4,  2,   0,  1,  2,  2,  1,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_flail,             SLOT( 0),       0,      0,
    "",                     "!Flail!",		""
  },

  {
    "mace",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  1,  1,  1,  1,  -1,  1,  1,  1,  1,   1,  1,  1 }, 
    {  0,  2,  3,  3,  2,   0,  1,  2,  2,  1,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_mace,              SLOT( 0),       0,      0,
    "",                     "!Mace!",		""
  },

  {
    "polearm",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1,  1, -1,  -1, -1,  1,  1, -1,   1,  1,  1 }, 
    {  0,  0,  6,  4,  0,   0,  0,  5,  2,  0,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_polearm,           SLOT( 0),       0,      0,
    "",                     "!Polearm!",		""
  },
    
  {
    "spear",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1,  1,  1,  -1, -1,  1,  1, -1,   1,  1,  1 }, 
    {  0,  0,  4,  3,  3,   0,  0,  3,  2,  0,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_spear,             SLOT( 0),       0,      0,
    "",                     "!Spear!",		""
  },

  {
    "sword",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1,  1,  1,  -1, -1,  1,  1, -1,   1,  1,  1 }, 
    {  0,  0,  3,  2,  2,   0,  0,  2,  2,  0,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_sword,             SLOT( 0),       0,      0,
    "",                     "!sword!",		""
  },

  {
    "whip",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1 }, 
    {  5,  4,  5,  3,  3,   5,  4,  4,  2,  3,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_whip,              SLOT( 0),       0,      0,
    "",                     "!Whip!",	""
  },

  {
    "staff",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1 }, 
    {  3,  3,  3,  2,  2,   2,  2,  2,  2,  2,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_staff,             SLOT( 0),       0,      0,
    "",                     "!Staff!",		""
  },

  {
    "shield block",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1,  1,  1,  1,  1,  -1,  1,  1,  1, -1,   1,  1,  1 }, 
    {  0,  4,  6,  2,  3,   0,  3,  2,  2,  0,   1,  1,  1 },
    spell_null,		TAR_IGNORE,		POS_FIGHTING,
    &gsn_shield_block,	SLOT(0),	0,	0,
    "",			"!Shield!",		""
  },
 
  {
    "backstab",  
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1, -1, -1,  -1, -1,  1, -1, -1,  -1, -1,  3 }, 
    {  0,  0,  5,  0,  0,   0,  0,  4,  0,  0,   0,  0,  3 },
    spell_null,             TAR_IGNORE,             POS_STANDING,
    &gsn_backstab,          SLOT( 0),        0,     24,
    "backstab",             "!Backstab!",		""
  },

  {
    "bash",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1,  1,  4,  -1, -1, -1,  1, -1,   1,  1,  1 }, 
    {  0,  0,  0,  4,  4,   0,  0,  0,  3,  0,   1,  1,  1 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_bash,              SLOT( 0),       0,      24,
    "bash",                 "!Bash!",		    ""
  },

  {
    "berserk",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1, 18, 21,  -1, -1, -1, 17, -1,  16, 15, 16 }, 
    {  0,  0,  0,  5,  5,   0,  0,  0,  4,  0,   3,  2,  3 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_berserk,           SLOT( 0),       0,      24,
    "",                     "You feel your pulse slow down.",	""
  },

  {
    "dirt kicking",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  3,  3,  3,  -1, -1,  2,  2,  7,   1,  1,  1 }, 
    {  0,  0,  4,  4,  4,   0,  0,  3,  3,  4,   1,  2,  1 }, 
    spell_null,		TAR_IGNORE,		POS_FIGHTING,
    &gsn_dirt,		SLOT( 0),	0,	24,
    "kicked dirt",	"You rub the dirt out of your eyes.",	""
  },

  {
    "disarm", 
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, 12, 11, -1,  -1, -1, 11, 10, -1,  -1,  1, -1 }, 
    {  0,  0,  6,  4,  0,   0,  0,  5,  3,  0,   0,  2,  0 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_disarm,            SLOT( 0),        0,     24,
    "",                     "!Disarm!",		    ""
  },
 
  {
    "dodge",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 20, 22,  1, 13, 12,  30, 33,  1, 12, 19,   2,  2,  2 }, 
    {  7,  7,  4,  6,  5,   8,  8,  3,  5,  3,   4,  4,  4 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_dodge,             SLOT( 0),        0,     0,
    "",                     "!Dodge!",		    ""
  },
 
  {
    "enhanced damage", 
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 30, 25,  1,  9,  -1, -1, 20,  1, -1,   7,  6,  7 }, 
    {  0,  9,  5,  3,  4,   0,  0,  4,  2,  0,   3,  2,  3 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_enhanced_damage,   SLOT( 0),        0,     0,
    "",                     "!Enhanced Damage!",    ""
  },

  {
    "envenom",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, 10, -1, -1,  -1, -1,  1, -1, -1,  -1,  1,  1 }, 
    {  0,  0,  4,  0,  0,   0,  0,  3,  0,  0,   0,  2,  1 },
    spell_null,		TAR_IGNORE,	  	POS_RESTING,
    &gsn_envenom,	SLOT(0),	0,	36,
    "",			"!Envenom!",		""
  },

  {
    "hand to hand",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 25, 10, 15,  7,  8,  -1, -1, 14,  5, -1,   1,  1,  1 }, 
    {  8,  5,  6,  4,  3,   0,  0,  5,  3,  0,   1,  2,  1 },
    spell_null,		TAR_IGNORE,		POS_FIGHTING,
    &gsn_hand_to_hand,	SLOT( 0),	0,	0,
    "",			"!Hand to Hand!",	""
  },

  {
    "kick",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 12, 14,  8, 10,  -1, -1, 13,  1, -1,  -1, -1, -1 }, 
    {  0,  4,  6,  3,  4,   0,  0,  5,  2,  0,   0,  0,  0 },
    spell_null,             TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
    &gsn_kick,              SLOT( 0),        0,     12,
    "kick",                 "!Kick!",		    ""
  },

  {
    "parry",   
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 20, 13,  1,  1,  -1, -1, 12,  1, -1,   1,  1,  1 }, 
    {  0,  8,  6,  4,  4,   0,  0,  5,  2,  0,   3,  3,  3 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_parry,             SLOT( 0),        0,     0,
    "",                     "!Parry!",		    ""
  },

  {
    "rescue", 
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1,  1,  1,  -1, -1, -1,  1, -1,   3,  3,  3 }, 
    {  0,  0,  0,  4,  4,   0,  0,  0,  2,  0,   2,  2,  2 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_rescue,            SLOT( 0),        0,     12,
    "",                     "!Rescue!",		    ""
  },

  {
    "trip",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1, 15, -1,  -1, -1,  1, 14, -1,  -1,  1, -1 }, 
    {  0,  0,  4,  8,  0,   0,  0,  3,  6,  0,   0,  2,  0 },
    spell_null,		TAR_IGNORE,		POS_FIGHTING,
    &gsn_trip,		SLOT( 0),	0,	24,
    "trip",		"!Trip!",		""
  },

  {
    "second attack",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, 34, 12,  5,  6,  -1, -1, 11,  4, -1,   4,  4,  4 }, 
    {  0,  8,  5,  3,  3,   0,  0,  5,  2,  0,   2,  2,  2 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_second_attack,     SLOT( 0),        0,     0,
    "",                     "!Second Attack!",	""
  },

  {
    "third attack", 
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, 24, 12, 14,  -1, -1, 23, 11, -1,  10, 10, 10 }, 
    {  0,  0, 10,  4,  5,   0,  0,  8,  3,  0,   3,  3,  3 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_third_attack,      SLOT( 0),        0,     0,
    "",                     "!Third Attack!",	    ""
  },

  /* MEK 3-20-2004
   * New Combat Skills 
   */
  {
    "fourth attack", 
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1, 19, -1,  -1, -1, 36, 18, -1,  16, 16, 16 }, 
    {  0,  0,  0,  5,  0,   0,  0,  8,  4,  0,   4,  4,  4 },
    spell_null,             TAR_IGNORE,             POS_FIGHTING,
    &gsn_fourth_attack,     SLOT( 0),        0,     0,
    "",                     "!Fourth Attack!",	    ""
  },
  
  {
    "dual wield",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, 36, 20,  1,  -1, -1,  3, 10, -1,  14, 14, 14 }, 
    {  0,  0,  5,  4,  1,   0,  0,  4,  3,  0,   3,  3,  3 },
    spell_null,		TAR_IGNORE,	  	POS_STANDING,
    &gsn_dual_wield,	SLOT(0),	0,	8,
    "",			"!Dual Wield!",		""
  },
  
  
  /* non-combat skills */

  { 
    "fast healing",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 25, 19, 16,  6,  7,  24, 18, 15,  5,  8,  11, 11, 11 }, 
    {  8,  5,  6,  4,  4,   8,  6,  5,  3,  5,   3,  3,  3 },
    spell_null,		TAR_IGNORE,		POS_SLEEPING,
    &gsn_fast_healing,	SLOT( 0),	0,	0,
    "",			"!Fast Healing!",	""
  },

  /* new, improved fast healing */
  { 
    "body control",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1, -1, -1,  -1, -1, 30, 10, 20,  22, 22, 22 }, 
    {  0,  0,  0,  0,  0,   0,  0,  6,  4,  6,   3,  3,  3 },
    spell_null,		TAR_IGNORE,		POS_SLEEPING,
    &gsn_body_control,	SLOT( 0),	0,	0,
    "",			"!Body Control!",	""
  },

  {
    "haggle",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  7, 18,  1, 14, 15,   8, -1,  1, 13, 13,  15,  1, 15 }, 
    {  5,  8,  3,  6,  5,   5,  0,  2,  5,  5,   4,  2,  4 },
    spell_null,		TAR_IGNORE,		POS_RESTING,
    &gsn_haggle,	SLOT( 0),	0,	0,
    "",			"!Haggle!",		""
  },

  {
    "hide",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1, 12,  2,  -1, -1,  1, 11,  3,  -1, -1, -1 }, 
    {  0,  0,  4,  6,  2,   0,  0,  3,  5,  3,   0,  0,  0 },
    spell_null,		TAR_IGNORE,		POS_RESTING,
    &gsn_hide,		SLOT( 0),	 0,	12,
    "",			"!Hide!",		""
  },

  {
    "lore",	
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { 10, 10,  6, 20, 16,   8,  8,  5, 19, 12,   1,  1,  1 }, 
    {  6,  6,  4,  8,  7,   5,  5,  3,  7,  5,   0,  2,  0 },
    spell_null,		TAR_IGNORE,		POS_RESTING,
    &gsn_lore,		SLOT( 0),	0,	40,
    "",			"!Lore!",		""
  },

  {
    "meditation",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  6,  6, -1, -1, -1,   5,  5, -1, -1,  5,   7,  7,  7 }, 
    {  5,  5,  0,  0,  0,   4,  4,  0,  0,  6,   3,  4,  3 },
    spell_null,		TAR_IGNORE,		POS_SLEEPING,
    &gsn_meditation,	SLOT( 0),	0,	0,
    "",			"Meditation",		""
  },

  /* New Improved Meditation */
  {
    "trance",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1, -1, -1, -1,  25, 25, -1, -1, 35,  24, 24, 24 }, 
    {  0,  0,  0,  0,  0,   5,  5,  0,  0,  6,   3,  4,  3 },
    spell_null,		TAR_IGNORE,		POS_SLEEPING,
    &gsn_trance,	SLOT( 0),	0,	0,
    "",			"Meditation",		""
  },

  {
    "peek",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  1, -1, 11,  -1, -1,  1, -1, -1,  -1,  1, -1 }, 
    {  0,  0,  3,  0,  5,   0,  0,  2,  0,  0,   0,  2,  0 },
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_peek,		SLOT( 0),	 0,	0,
    "",			"!Peek!",		""
  },

  {
    "pick lock",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  7, -1, -1,  -1, -1,  6, -1, -1,  -1,  5, -1 }, 
    {  0,  0,  4,  0,  0,   0,  0,  3,  0,  0,   0,  2,  0 },
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_pick_lock,	SLOT( 0),	 0,	12,
    "",			"!Pick!",		""
  },

  {
    "sneak",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  4, 10,  5,  -1, -1,  1, -1, -1,  -1, -1, -1 }, 
    {  0,  0,  4,  6,  5,   0,  0,  2,  0,  0,   0,  0,  0 },
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_sneak,		SLOT( 0),	 0,	12,
    "",			"You no longer feel stealthy.",	""
  },

  {
    "steal",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    { -1, -1,  5, -1, -1,  -1, -1,  5, -1, -1,  -1, -1, -1 }, 
    {  0,  0,  4,  0,  0,   0,  0,  4,  0,  0,   0,  0,  0 },
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_steal,		SLOT( 0),	 0,	24,
    "",			"!Steal!",		""
  },

  {
    "scrolls",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1,  1, 16, -1, -1,   1,  1, 11, -1,  2,   1,  1,  1 }, 
    {  2,  3,  5,  0,  0,   1,  1,  4,  0,  2,   1,  2,  1 },
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_scrolls,	SLOT( 0),	0,	24,
    "",			"!Scrolls!",		""
  },

  {
    "staves",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1,  1, -1, -1, -1,   1,  1, -1, -1,  1,   1,  1,  1 }, 
    {  3,  2,  0,  0,  0,   1,  1,  0,  0,  3,   1,  2,  1 },
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_staves,	SLOT( 0),	0,	12,
    "",			"!Staves!",		""
  },
    
  {
    "wands",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1, -1, -1, -1, -1,   1, -1, -1, -1, -1,   1,  1,  1 }, 
    {  2,  0,  0,  0,  0,   1,  0,  0,  0,  0,   2,  4,  2 },
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_wands,		SLOT( 0),	0,	12,
    "",			"!Wands!",		""
  },

  {
    "recall",
    // M   C   T   W   R    W   P   A   K   D    A   T   D
    {  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1 }, 
    {  1,  1,  1,  1,  1,   1,  1,  1,  1,  1,   1,  1,  1 }, 
    spell_null,		TAR_IGNORE,		POS_STANDING,
    &gsn_recall,	SLOT( 0),	0,	12,
    "",			"!Recall!",		""
  }
};


/*
 * MEK 11-3-2004
 *
 * Added new groups for ranger, the remort classes, and the 2nd remort
 * classes
 *
 * Ranger  Basics & Default
 * Wizard  Basics & Default
 * Priest  Basics & Default
 * Assasin Basics & Default
 * Knight  Basics & Default
 * Druid   Basics & Default
 * Angel   Basics & Default
 * Titan   Basics & Default
 * Demon   Basics & Default
 *
 */
const   struct  group_type      group_table     [MAX_GROUP]     =
  {
    
    {
      "rom basics",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0 },
      { "recall" }
    },
    
    {
      "magic device",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  0,  0, -1, -1,  2,   0,  0, -1, -1,  1,   0,  0,  0 },  
      { "scrolls", "staves", "wands", "recall" }
    },

    //Basics
    {
      "mage basics",	  
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  0, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "dagger", "magic device" }
    },
    
    {
      "cleric basics",  
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  0, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "mace", "magic device" }
    },
   
    {
      "thief basics",
      // M   C   T   W   R    W   P   A   K   D    A   T   D   
      { -1, -1,  0, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "dagger", "steal" }
    },//5

    {
      "warrior basics",
      // M   C   T   W   R    W   P   A   K   D    A   T   D 
      { -1, -1, -1,  0, -1,  -1, -1, -1, -1,  -1, -1, -1, -1 },
      { "sword", "second attack" }
    },

    {
      "ranger basics",
      // M   C   T   W   R    W   P   A   K   D    A   T   D	
      { -1, -1, -1, -1,  0,  -1, -1, -1, -1, -1,  -1, -1, -1 },
      { "sword", "dual wield", "second attack" }
    },   

    {//remort classes 
      "wizard basics",
      // M   C   T   W   R    W   P   A   K   D    A   T   D 
      { -1, -1, -1, -1, -1,   0, -1, -1, -1, -1,  -1, -1, -1 },
      { "dagger", "magic device", "meditation" }
    },

    {
      "priest basics",
      // M   C   T   W   R    W   P   A   K   D    A   T   D 
      { -1, -1, -1, -1, -1,  -1,  0, -1, -1, -1, -1, -1, -1},
      { "mace", "magic device", "meditation" }
    },
   
    {
      "assasin basics", 
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1,  0, -1, -1,  -1, -1, -1 },
      { "dagger", "steal" }
    },//10

    {
      "knight basics", 
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1,  0, -1,  -1, -1, -1 },
      { "sword", "second attack" }
    },

    {
      "druid basics", 
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1,  0,  -1, -1, -1 },
      { "staff", "second attack" }
    },   
    //2nd remort classes

    {
      "angel basics", 
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1,   0, -1, -1 },
      { "sword" }
    },

    {
      "titan basics", 
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  -1,  0, -1 },
      { "mace" }
    },

    {
      "demon basics", 
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1,  0 },
      { "whip" }
    },//15

    

    //Defaults
    {
      "mage default",		
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { 40, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "abjuration", "conjuration", "detection", "enchantment", "evocation",
	"illusion", "transmutation", "meditation" }
    },

    {
      "cleric default",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, 40, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "flail", "attack", "creation", "curative",  "benedictions", 
	"divination", "healing", "maledictions", "guardian", "shield block", 
	"weather", "meditation" }
    },
 
    {
      "thief default",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, 40, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "mace", "sword", "backstab", "disarm", "dodge", "second attack",
	"trip", "hide", "peek", "pick lock", "sneak" }
    },

    {
      "warrior default",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, 40, -1,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "weaponsmaster", "shield block", "bash", "disarm", "enhanced damage", 
	"parry", "rescue", "third attack" }
    },

    {
      "ranger default",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, 40,  -1, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "sword", "staff", "sneak", "hide", "second attack", "parry", "plant",
        "enhanced damage" }
    },//20   
    
    //remort classes 
    {
      "wizard default",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  38, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "abjuration", "conjuration", "detection", "enchantment", "evocation",
	"illusion", "transmutation", "meditation" }
    },
    
    {
      "priest default",
      // M   C   T   W   R    W   P   A   K   D    A   T   D	
      { -1, -1, -1, -1, -1,  -1, 38, -1, -1, -1,  -1, -1, -1 }, 
      { "staff", "attack", "creation", "curative",  "benedictions", 
	"divination", "healing", "maledictions", "guardian", "shield block", 
	"weather", "meditation" }
    },
   
    {
      "assasin default",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, 38, -1, -1,  -1, -1, -1 }, 
      { "mace", "sword", "backstab", "disarm", "dodge", "parry",
	"second attack", "trip", "hide", "peek", "pick lock", "envenom" }
    },

    {
      "knight default",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, 38, -1,  -1, -1, -1 }, 
      { "weaponsmaster", "shield block", "bash", "disarm", "enhanced damage", 
	"parry", "rescue", "third attack", "dual wield" }
    },

    {
      "druid default",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1, 38,  -1, -1, -1 }, 
      { "dagger", "meditation", "guardian", "plant", "weather", "travel" }
    },//25


    //2nd remort classes
    {
      "angel default",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  40, -1, -1 }, 
      { "dagger", "mace", "whip", "healing", "benediction", "second attack" }
    },

    {
      "titan default",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, 40, -1 }, 
      { "dagger", "sword", "whip" }
    },

    {
      "demon default",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1,  -1, -1, 40 }, 
      { "dagger", "mace", "sword", "harmful", "malediction", "second attack" }
    },



    {
      "weaponsmaster",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1, -1, 32, 16, 24,  -1, -1, 30, 15, -1,  18, 15, 18 },
      { "axe", "dagger", "flail", "mace", "polearm", "spear", "sword",
	"whip", "staff" }
    },

    /* MEK
     * These groups correspond to the schools of magic and spheres of power
     * available to mages/wizards and clerics/priests. See magic.c for mage 
     * spell definitions and magic_clerical.c for clerical spell definitions 
     *
     */

    //Magic
    {
      "abjuration",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  4, -1, -1, -1, -1,   4, -1, -1, -1, -1,  -1,  5, -1 }, 
      {  "cancellation", "dispel magic", "fireproof", "shield", "teleport"
         /*,"spell turning"*/ }
    },//30

    { 
      "conjuration",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  4, -1, -1, -1, -1,   4, -1, -1, -1, -1,  -1,  5, -1 }, 
      { "armor", "floating disc", "nexus", "portal", "summon" }
    },
    
    {
      "detection",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  4, -1, -1, -1, -1,   3, -1, -1, -1, -1,  -1,  5, -1 }, 
      { "detect hidden", "detect invis", "detect magic", "farsight", 
	"identify" }
    },
    
    {
      "draconian",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  8, -1, -1, -1, -1,   7, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "acid breath", "fire breath", "frost breath", "gas breath",
	"lightning breath"  }
    },
    
    {
      "enchantment",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  6, -1, -1, -1, -1,   6, -1, -1, -1, -1,  -1,  6, -1 }, 
      { "calm", "charm person", "enchant armor", "enchant weapon", 
	"recharge", "sleep" }
    },

    {
      "evocation",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  6, -1, -1, -1, -1,   5, -1, -1, -1, -1,  -1, -1, -1 }, 
      { "magic missile", "burning hands", "shocking grasp", "lightning bolt",
	"fireball", "acid blast", "shockwave", "cone of cold", "force bolt",
	"chain lightning", "meteor swarm" }
    },//35

    {
      "illusion",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  4, -1, -1, -1, -1,   3, -1, -1, -1, -1,  -1,  3, -1 }, 
      { "blindness", "color spray", "continual light", "invis", "mass invis", 
	"ventriloquate"/*, "blur"*/ }
    },

    {
      "necromancy",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  6, -1, -1, -1, -1,   5, -1, -1, -1, -1,  -1, -1,  5 }, 
      { /*"animate dead,"*/ "chill touch", "energy drain", "vampiric touch", 
	"weaken"}
    },

    { 
      "transmutation",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      {  5, -1, -1, -1, -1,   4, -1, -1, -1, -1,  -1,  6, -1 }, 
      { "giant strength", "haste", "infravision", "fly", "pass door", 
	"stone skin" /*enlarge/shrink*/ }
    },



    //Clerical
    {
      "attack",		
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  5, -1, -1, -1,  -1,  5, -1, -1, -1,   4, -1,  4 }, 
      { "demonfire", "dispel evil", "dispel good", "earthquake", 
	"flamestrike", "heat metal", "ray of truth" }
    },

    {
      "benedictions",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  4, -1, -1, -1,  -1,  4, -1, -1, -1,   3, -1, -1 }, 
      { "bless", "calm", "frenzy", "holy word", "remove curse" }
    },//40

    {
      "creation",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  4, -1, -1, -1,  -1,  4, -1, -1, -1,  -1, -1, -1 }, 
      { "continual light", "create food", "create spring", "create water",
	"create rose", "floating disc" }
    },

    {
      "curative",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  4, -1, -1, -1,  -1,  3, -1, -1, -1,   3, -1, -1 }, 
      { "cure blindness", "cure disease", "cure poison", 
	"refresh", "rejuvenate"  }
    }, 

    {
      "divination",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  3, -1, -1, -1,  -1,  2, -1, -1, -1,   3, -1,  3 }, 
      { "detect evil", "detect good", "detect poison", "farsight",
	"know alignment", "locate object" } 
    },

    {
      "guardian",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  4, -1, -1, -1,  -1,  4, -1, -1,  7,   5, -1, -1 }, 
      { "cancellation", "dispel magic", "fireproof", "protection evil", 
	"protection good", "sanctuary" }
    },

    {
      "harmful",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  3, -1, -1, -1,  -1,  3, -1, -1, -1,  -1, -1,  2 }, 
      { "cause critical", "cause light", "cause serious", "harm" }
    },//45

    {   
      "healing",
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  3, -1, -1, -1,  -1,  3, -1, -1, -1,   2, -1, -1 }, 
      { "cure critical", "cure light", "cure serious", "heal", 
	"mass healing" }
    },

    {
      "maledictions",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  5, -1, -1, -1,  -1,  5, -1, -1, -1,  -1, -1,  5 }, 
      { "blindness", "change sex", "curse", "plague", "poison", "slow", 
	"weaken" }
    },

    {
      "plant",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  4, -1, -1,  4,  -1,  3, -1, -1,  2,  -1,  3, -1 }, 
      { "barkskin", "goodberry" }
    },

    {
      "weather",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  4, -1, -1, -1,  -1,  3, -1, -1,  4,   2,  6,  2 }, 
      { "call lightning", "control weather", "faerie fire", "faerie fog" }
    },

    {
      "travel",	
      // M   C   T   W   R    W   P   A   K   D    A   T   D
      { -1,  4, -1, -1, -1,  -1,  2, -1, -1,  4,   1,  5,  1 }, 
      { "gate", "word of recall" }
    }//50

  };
