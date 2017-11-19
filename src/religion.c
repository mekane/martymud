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

/***************************************************************************
 *                                                                         *
 *  This file created and copyrighted (c) 3-12-2004 by Marty Kane          *
 *  Permission is given to use, modify, and distribute this file and the   *
 *  code contained within, provided this copyright statement is left       *
 *  intact.                                                                *
 *                                                                         *
 *  Inspired and based partly on deity worship code by                     *
 *  Jair <jddotter@ou.edu>                                                 *
 *                                                                         *
 ***************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "merc.h"


/* MEK 3-14-2004
 * For religions:
 * Allows a character to choose a God to worship
 */
void do_worship( CHAR_DATA *ch, char *argument )
{
  char buf[MAX_STRING_LENGTH];
  sh_int god;

  if ( IS_NPC(ch) || ch == NULL )
    return;
  
  if ( IS_IMMORTAL(ch) )
  {
    send_to_char( "What do you need a religion for? You're immortal!\n\r",ch);
    return;
  }


  if ( argument[0] != '\0' )
  {//with argument

    //if they have a god, they shouldn't be worshipping others
    if ( ch->religion)
    {
      sprintf(buf,"But you worship %s!  Did you want to RENOUNCE %s?\n\r",
	      (god_table[ch->religion].name),(god_table[ch->religion].name) );
      
      send_to_char( buf, ch);
      return;
    }

    //if they don't have a god, they're choosing a new one
    god = god_lookup(argument);

    if ( god == 0 )
    {
      send_to_char( "That religion does not exist.\n\r", ch);
      return;
    }
    
    //If alignment is not right, print a nice message
    if ( ch->alignment < god_table[god].min_align )
    {
      if ( ch->alignment < ( god_table[god].min_align - 500 ) )
	sprintf( buf, "You are much too unclean to worship %s.\n\r",
		 (god_table[god].name));
      else
	sprintf( buf, "You are too unclean to worship %s.\n\r",
		 (god_table[god].name));
      
      send_to_char( buf, ch);
      return;
    }
    
    if ( ch->alignment > god_table[god].max_align )
    {
      if ( ch->alignment > ( god_table[god].max_align + 500 ) )
	sprintf( buf, "You are much too pure to worship %s.\n\r",
		 (god_table[god].name));
      else
	sprintf( buf, "You are too pure to worship %s.\n\r",
		 (god_table[god].name));
      send_to_char( buf, ch);
      return;
    }

    //otherwise, set them up with a religion!
    sprintf( buf, "You dedicate yourself to %s!\n\r", (god_table[god].name));
    send_to_char( buf, ch);

    ch->religion = god;
    
    //do special things:

    //if character is in the god's temple, or a cleric, get a holy item
    if ( (ch->in_room->vnum == god_table[god].temple) ||
	 (ch->class == class_lookup("cleric"))        ||
	 (ch->class == class_lookup("priest")) )
    {
      int symbol_index = god_table[god].symbol;
      OBJ_DATA *symbol = create_object( get_obj_index(symbol_index), 1 );

      sprintf( buf, "%s grants you %s!\n\r", (god_table[god].name), 
	       symbol->short_descr);
      send_to_char( buf, ch);
      
      obj_to_char(symbol,ch);
    }
    
    //special skills
    //if they are a cleric - something cool
    //special spells

    //tattoo / mark?
    
    return;
  }
  else
  {
    //if they don't have a god, show them the list
    if ( ch->religion == 0 )
    {
      sprintf( buf, "The following religions are available:\n\r" );
      for ( god = 1; god < MAX_GOD; god++ )
      {
	strcat( buf, (god_table[god].name) );
	if ( ch->in_room->vnum == god_table[god].temple )
	  strcat( buf, " (in temple!)" );
	strcat( buf, "\n\r" );
      }

      send_to_char( buf, ch);
    }
    else
    {
      sprintf( buf, "You worship %s.\n\r",(god_table[ch->religion].name));
      send_to_char( buf, ch);
    }
  }
}


/* MEK 3-17-2004
 * For religions:
 * Make sure people really mean it
 */
void do_renounc( CHAR_DATA *ch, char *argument )
{
  send_to_char( "If you want to RENOUNCE your god, you must spell it out.\n\r",
		ch );
  return;
}


/* MEK 3-17-2004
 * For religions:
 * Allows a character to renounce the god they currently worship -
 * and get blasted with the consequences.
 */
void do_renounce( CHAR_DATA *ch, char *argument )
{
  char buf[MAX_STRING_LENGTH];
  sh_int god;
  
  if ( IS_NPC(ch) || ch == NULL )
    return;

  if ( IS_IMMORTAL(ch) )
  {
    send_to_char( "There's no point to that - you're immortal!\n\r",ch);
    return;
  }

  if ( !ch->religion )
  {
    send_to_char( "There's no point to that - you're an atheist!\n\r",ch);
    return;
  }


  if ( argument[0] != '\0' )
  {//with argument

    god = god_lookup(argument);

    if ( god == 0 )
    {
      send_to_char( "That religion does not exist.\n\r", ch);
      return;
    }

    //make sure they're renouncing their actual god
    if ( ch->religion != god )
    {
      sprintf(buf,"But you worship %s! How can you renounce %s?!\n\r",
	      (god_table[ch->religion].name),(god_table[god].name) );
      
      send_to_char( buf, ch);
      return;
    }
    else
    {//they mean it
      sprintf(buf,"You turn from the way of %s!\n\r",
	      (god_table[god].name) );
      
      send_to_char( buf, ch);
      return;
      //do it up
      
      //get rid of god
      ch->religion = 0;

      //get rid of holy symol
      OBJ_INDEX_DATA *symbol = get_obj_index( god_table[god].symbol );
      char *name = symbol->name;
      OBJ_DATA *delete;

      if ( (delete = get_obj_carry( ch, name, ch )) )
      {
     	act("Your god demands the return of $p.",ch,delete,NULL,TO_CHAR);
     	act("It flares brightly and vanishes!",ch,delete,NULL,TO_CHAR);
     	extract_obj(delete);
      }
      
      //choose a nasty consequence: for now just a big curse
      AFFECT_DATA af;
      af.where     = TO_AFFECTS;
      af.type      = gsn_curse;
      af.level     = 300;
      af.duration  = 300;
      af.location  = APPLY_HITROLL;
      af.modifier  = -33;
      af.bitvector = AFF_CURSE;
      affect_to_char( ch, &af );

      af.location  = APPLY_SAVING_SPELL;
      af.modifier  = 33;
      affect_to_char( ch, &af );

      sprintf(buf,"You feel the wrath of %s!\n\r", god_table[god].name );
      send_to_char( buf, ch);

      //-lose a level
      //-lose skill / percent
      //-lose eq
      //-lose xp (%)
    }
  }
  else
  {//no argument
    send_to_char("You must state the name of the god to renounce.\n\r", ch);
    return;
  }
}








/* Code by Jair <jddotter@ou.edu>
 * returns god number 
 */
int god_lookup (const char *name)
{
  int god;
  
  for ( god = 0; god < MAX_GOD; god++)
  {
    if (LOWER(name[0]) == LOWER(god_table[god].name[0])
	&&  !str_prefix( name,god_table[god].name))
      return god;
  }
  
  return 0;
}




/* god table */
const   struct  god_type       god_table      []           = 
  {
    /*
      {
      name,  
      temple,   symbol,       relic,
      max_align, min_align
      },
    */
    
    { "Nobody", 0, 0, 0, 0, 0 },
    
    {
      "Lupo",
      8808,     8801,         8800,
      1000,     500
    },
    
    {
      "Neutrus",
      8807,     8803,         8802,
      250,      -250
    },
    
    {
      "Bad Dude",
      8806,     8805,         8804,
      -500,     -1000
    }
  };

