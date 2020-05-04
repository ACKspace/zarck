/*
* No Copyright
*
* The person who associated a work with this deed has dedicated the work to the public domain by waiving all of his or her rights to the work worldwide under copyright law, including all related and neighboring rights, to the extent allowed by law.
*
* You can copy, modify, distribute and perform the work, even for commercial purposes, all without asking permission.
*
* See https://creativecommons.org/share-your-work/public-domain/cc0/ for more information on the license.
*/

#define DONT_SHIT_YOUR_PANTS
#define MUD

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

//#define DEBUG
#include <stdio.h>
#ifdef DEBUG
#include <stdlib.h>
#endif
#include <string.h>
#include "vanalles.h"
#include "world.h"

#include "lists.h"
#include "objects.h"
#include "locations.h"
#include "updates.h"

//----------------------------------------------------------------------------
// WORLD DEFINITION
//----------------------------------------------------------------------------

world world1 = {
    1,
    "You wakeup dizzy at a cold concrete floor in the dark near a wall.\n"
    "The stench of burnt plastic, petrol and rubber is horrible, which may be the\n"
    "reason of your headache.  Apparently, your clothes are somewhat frayed and have\n"
    "a smokey scent, which could mean that you were in some kind of explosion,\n"
    "knocking you unconscious.  About 30 meters in front of you lingers a small fire.\n"
    "When going through your pockets, you notice your phone isn't there.  Luckily,\n"
    "you see it on the floor but its screen is cracked. You might want to take a\n"
    "closer look at it.  After you've checked that you are physically ok, you look\n"
    "around to see some dim light on the left side and a little more light on the\n"
    "right side that also has a sign saying \"SOUTH EXIT\".\n"
};

inventory user_inventory = {
#ifdef DONT_SHIT_YOUR_PANTS
    PANTS,
#endif
0
};


//----------------------------------------------------------------------------
// ATTRIBUTES
//----------------------------------------------------------------------------

int curloc;
char temp[1024];
int exitflag = 0;
char prompt[100] = ">";

//----------------------------------------------------------------------------
// ROUTINES
//----------------------------------------------------------------------------

void beginworld() {
  curloc = world1.startloc;
  printf("%s\n", world1.welcome);

  //location_look(curloc);
  command_loop();
}

void command_loop()
{
#ifndef __EMSCRIPTEN__
  while (!exitflag)
  {
    printf( "%s", prompt );

    if ( fgets( temp, 256, stdin ) )
        do_command(temp);
  }
#endif
}

#ifdef __EMSCRIPTEN__
void EMSCRIPTEN_KEEPALIVE command(char *temp)
{
    do_command(temp);
}

#ifdef MUD
int* EMSCRIPTEN_KEEPALIVE mudata( int* _arr, int _len )
{
    if ( _len < 7 )
        return _arr;

    // int[7]: current, N, S, E, W, U, D: 0 is non-existant
    _arr[ 0 ] = curloc;
    _arr[ 1 ] = locs[curloc].north;
    _arr[ 2 ] = locs[curloc].south;
    _arr[ 3 ] = locs[curloc].east;
    _arr[ 4 ] = locs[curloc].west;
    _arr[ 5 ] = locs[curloc].up;
    _arr[ 6 ] = locs[curloc].down;

    return _arr;
}
#endif

#endif

int do_command(char *cmd)
{
  char ourtemp[100];
  char ourtemp2[100];
  char ourtemp3[100];
  char *parm2;
  char *parm3;
  char *xtemp;
  int itemidx;

  ucase(cmd);
  removetrailingcrlf(cmd);
  strcpy(ourtemp, xthword(cmd, 0));
  strcpy(ourtemp2, xthword(cmd, 1));
  strcpy(ourtemp3, xthword(cmd, 2));
  xtemp = trim(ourtemp);
  parm2 = trim(ourtemp2);
  parm3 = trim(ourtemp3);

  if (emptystring(xtemp))
    goto end_command;

#ifdef MUD
  if ( strcmp(xtemp, "SAY") == 0 )
    goto end_command;
#endif

  if ( strcmp(xtemp, "LOOK") == 0 || strcmp(xtemp, "L") == 0 || strcmp(xtemp, "READ") == 0 )
  {
    if (emptystring(parm2))
      location_look(curloc);
    else
      item_look(parm2);
  }

  else if (strcmp(xtemp, "N")==0 || strcmp(xtemp, "NORTH")==0)
    go_location( locs[curloc].north );

  else if (strcmp(xtemp, "S")==0 || strcmp(xtemp, "SOUTH")==0)
    go_location( locs[curloc].south );

  else if (strcmp(xtemp, "W")==0 || strcmp(xtemp, "WEST")==0)
    go_location( locs[curloc].west );

  else if (strcmp(xtemp, "E")==0 || strcmp(xtemp, "EAST")==0)
    go_location( locs[curloc].east );

  else if (strcmp(xtemp, "U")==0 || strcmp(xtemp, "UP")==0)
    go_location( locs[curloc].up );

  else if (strcmp(xtemp, "D")==0 || strcmp(xtemp, "DOWN")==0)
    go_location( locs[curloc].down );

  else if (strcmp(xtemp, "P")==0 || strcmp(xtemp, "T")==0 || strcmp(xtemp, "G")==0)
    item_pickup(parm2, curloc);

  else if (strcmp(xtemp, "PICKUP")==0 || strcmp(xtemp, "TAKE")==0 || strcmp(xtemp, "GRAB")==0)
    item_pickup(parm2, curloc);

  else if (strcmp(xtemp, "DROP") ==0 )
    item_drop(parm2, curloc);

  else if (strcmp(xtemp, "HELP") ==0 )
  {
    printf( "Try entering a \"verb\" or \"noun\", or \"verb noun\".\nIf you're really lost, type INSTRUCTIONS.\n" );
  }
  else if (strcmp(xtemp, "INSTRUCTIONS") ==0 )
  {
    if ( hasInventoryItem( INSTRUCTIONS ) )
    {
        printf( "Just type \"LOOK INSTRUCTIONS\" without the quotes.\n" );
        return 1;
    }

    // Found item on location
    for ( int inv=0; inv < 20; inv++ )
    {
        if ( !user_inventory.objects[inv] )
        {
            printf( "INSTRUCTIONS have been added to your INVENTORY.\nYou might want to have a LOOK at it.\n" );
            user_inventory.objects[inv] = INSTRUCTIONS;
            return 1;
        }
    }
  }

  else if (strcmp(xtemp, "I")==0 || strcmp(xtemp, "INVENTORY")==0)
  {
    printf( "Inventory: " );
    list_items( user_inventory.objects, 20 );
  }

  else if (strcmp(xtemp, "USE")==0)
    item_use(parm2, parm3);

  else if (strcmp(xtemp, "EXIT")==0 || strcmp(xtemp, "QUIT")==0 || strcmp(xtemp, "Q")==0)
    exit_game();

#ifdef DEBUG
  else if (strcmp(xtemp, "GIVE")==0)
  {
        int i = atoi( parm2 );
        if ( i && i < OBJ_LEN )
        {
            for ( int inv=0; inv < 20; inv++ )
            {
                if ( !user_inventory.objects[inv] )
                {
                    printf( "%s %s now injected to your inventory.\n", objs[i].name, objs[i].pickup == 1 ? "is" : "are" );

                    user_inventory.objects[inv] = i;
                    return 0;
                }
            }
        }
  }

  else if ( int i = atoi( xtemp ) )
        go_location( i );
#endif
#ifdef DONT_SHIT_YOUR_PANTS
  else if ( strcmp( xtemp, "DIE" ) ==0 )
  {
    printf( "Your vision fades and you hear a soft\n'pbffffff' as you shit your pants. Game over.\n" );
    exit_game();
  }
  else if ( strcmp( xtemp, "SHIT" ) == 0 )
  {
    // 
    if ( curloc != WASHINGROOM && curloc != TOILETROOM && hasInventoryItem( PANTS ) )
    {
        // Not in the special rooms?
        printf( "The game hasn't started yet but you just\ncouldn't help yourself.  You just shit in your\npants. Game  over.\n" );

        itemidx = find_inventoryindex( "PANTS" );
        user_inventory.objects[ itemidx ] = PANTS_DIRTY;
        //exit_game();
    }
    else if ( hasInventoryItem( PANTS ) )
    {
        // Pants in inventory?
        printf( "You just shit your pants! Game over!.\n" );

        // Make pants dirty
        itemidx = find_inventoryindex( "PANTS" );
        user_inventory.objects[ itemidx ] = PANTS_DIRTY;
        //exit_game();
    }
    else if ( hasInventoryItem( PANTS_DIRTY ) )
    {
        // Pants in inventory?
        printf( "You just shit your pants again, wow! Game over!.\n" );

        //exit_game();
    }
    else if ( curloc == WASHINGROOM )
    {
        printf( "You just shit on the floor! Congratulations!\n" );
        // NOTE: this overrides the second item, but since drop item uses the 3rd, we're safe         
        locs[curloc].objects[ 1 ] = SHIT;
    }
    else if ( curloc == TOILETROOM )
    {
        printf( "You just shit in the  toilet! Congratulations!\n" );
    }
  }
#endif
  else printf("Unrecognized command \"%s\".\n", xtemp);

  end_command:
    return 1;
}


int hasInventoryItem( int _item )
{
    // Try and look into the inventory
    for ( int inv=0; inv < 20; inv++ )
    {
        if ( (user_inventory.objects[inv] ) && ( user_inventory.objects[inv] == _item ) )
            return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// COMMANDS
//----------------------------------------------------------------------------

void location_look(int loc) {
  printf("%s\n", locs[loc].text);
  printf("You see: ");
  list_items( locs[loc].objects, 3 );

  printf("Exits: ");
  spell_directions(loc);
  printf("\n");

#ifdef DEBUG
  printf("loc: %d\n", loc );
#endif
}

void item_look(char* itemstr)
{
    char utemp[200];

    for ( int i=0; i < 3; i++ )
    {
        if (locs[curloc].objects[i])
        {
            strcpy(utemp, objs[locs[curloc].objects[i]].name);
            ucase(utemp);

#ifdef DEBUG
            if ( strcmp("*", itemstr)==0 || (strcmp(utemp, itemstr))==0 )
#else
            if ( strcmp(utemp, itemstr)==0)
#endif
            {
                // Found item on location
                printf( "%s", objs[locs[curloc].objects[i]].appearance );
#ifndef DEBUG
                return;            
#endif
            }
        }
    }

    // Try and look into the inventory
    for ( int inv=0; inv < 20; inv++ )
    {
        if (user_inventory.objects[inv])
        {
            strcpy(utemp, objs[user_inventory.objects[inv]].name);
            ucase(utemp);

#ifdef DEBUG
            if ( strcmp("*", itemstr)==0 || strcmp(utemp, itemstr)==0)
#else
            if (strcmp(utemp, itemstr)==0)
#endif
            {
                // Found item in inventory
                printf( "%sIt's in your inventory.\n", objs[user_inventory.objects[inv]].appearance );
#ifndef DEBUG
                return;            
#endif
            }
        }
    }

    printf("You don't see that here.\n");
}

void item_pickup(char* itemstr, int _loc)
{
    char utemp[200];
    if (emptystring(itemstr))
        goto nofound;

    // TODO: use find_locationidx
    for ( int i=0; i < 3; i++ )
    {
        if (locs[_loc].objects[i])
        {
            strcpy(utemp, objs[locs[_loc].objects[i]].name);
            ucase(utemp);

#ifdef DONT_SHIT_YOUR_PANTS
            if ( strcmp(utemp, itemstr) == 0 && locs[_loc].objects[i] == PILLS )
            {
                printf( "You eat the pills. Hopefully they'll start working in time.\n" );
                locs[_loc].objects[i] = 0;
                return;
            }
#endif
#ifdef DEBUG
            if ((strcmp(utemp, itemstr)==0||strcmp("*", itemstr)==0) && objs[locs[_loc].objects[i]].pickup)
#else
            if (strcmp(utemp, itemstr)==0 && objs[locs[_loc].objects[i]].pickup)
#endif
            {
                // Found item on location
                for ( int inv=0; inv < 20; inv++ )
                {
                    if ( !user_inventory.objects[inv] )
                    {
                        printf( "%s %s now added to your inventory.\n", objs[locs[_loc].objects[i]].name, objs[locs[_loc].objects[i]].pickup == 1 ? "is" : "are" );

                        user_inventory.objects[inv] = locs[_loc].objects[i];
                        locs[_loc].objects[i] = 0;

                        return;
                    }
                }

                printf("Your inventory is full, drop an item first.\n");
#ifndef DEBUG
                return;
#endif
            }
        }
    }

  nofound:
    printf("You can't pick that up.\n");
}

void item_drop(char* inventorystr, int _loc)
{
    int inventoryitemidx;

    if (emptystring( inventorystr ))
    {
        printf("Drop what?\n");
        return;
    }

    // find inventorystr or nofound
    inventoryitemidx = find_inventoryindex( inventorystr );
    if ( inventoryitemidx == -1 )
        inventoryitemidx = find_inventoryindex( inventorystr );

    if ( inventoryitemidx == -1 )
    {
        printf("You don't have that.\n");
        return;
    }

    for ( int i=0; i < 3; i++ )
    {
        if (!locs[_loc].objects[i])
        {
            locs[_loc].objects[i] = user_inventory.objects[ inventoryitemidx];
            user_inventory.objects[ inventoryitemidx] = 0;

            printf( "%s %s now removed from your inventory.\n", objs[locs[_loc].objects[i]].name, objs[locs[_loc].objects[i]].pickup == 1 ? "is" : "are" );

            return;
        }
    }

    printf( "You can't drop that here: there is no room to do that.\n" );
}

void item_use(char* inventorystr, char* itemstr)
{
    int inventoryitemidx;
    int inventoryitemidx2;
    int locationitemidx = -1;
    int inventoryitem;
    int locationitem = 0;

    if (emptystring( inventorystr ))
    {
        printf("Use what?\n");
        return;
    }

    if (emptystring(itemstr))
    {
        printf("Use on what?\n");
        return;
    }

    inventoryitemidx = find_inventoryindex( inventorystr );
    inventoryitemidx2 = find_inventoryindex( itemstr );

    if ( inventoryitemidx == -1 && inventoryitemidx2 == -1 )
    {
        printf("You don't have that.\n");
        return;
    }
    else if ( inventoryitemidx == -1 )
    {
        inventoryitemidx = inventoryitemidx2;
        inventoryitemidx2 = -1;

        // NOTE: Could still return -1
        locationitemidx = find_locationindex( inventorystr, curloc );
    }
    else if ( inventoryitemidx2 == -1 )
    {
        // NOTE: Could still return -1
        locationitemidx = find_locationindex( itemstr, curloc );
    }

    if ( locationitemidx != -1 )
    {
        locationitem = locs[curloc].objects[locationitemidx];
    }
    else if ( inventoryitemidx2 != -1 )
    {
        locationitem = user_inventory.objects[ inventoryitemidx2 ];
    }
    else
    {
        printf("That's not here.\n");
        return;
    }

    inventoryitem = user_inventory.objects[ inventoryitemidx];

    object locationobject = objs[ locationitem ];
    object inventoryobject = objs[ inventoryitem ];

    int locationupdate = 0;
    int inventoryupdate = 0;

#ifdef DEBUG
        //printf("locationitem: %d, inventoryitem: %d\n", locationitem, inventoryitem );

        printf("l1: %d, l1 cond: %d, inv: %d\n", locationobject.update1, updates[ locationobject.update1 ].condition, inventoryitem );
        printf("l2: %d, l2 cond: %d, inv: %d\n", locationobject.update2, updates[ locationobject.update2 ].condition, inventoryitem );
#endif

    if ( locationobject.update1 && updates[ locationobject.update1 ].condition == inventoryitem )
    {
        locationupdate = locationobject.update1;
    }
    else if ( locationobject.update2 && updates[ locationobject.update2 ].condition == inventoryitem )
    {
        locationupdate = locationobject.update2;
    }

#ifdef DEBUG
        //printf("locationitem: %d, inventoryitem: %d\n", locationitem, inventoryitem );

        printf("i1: %d, i1 cond: %d, loc: %d\n", inventoryobject.update1, updates[ inventoryobject.update1 ].condition, locationitem );
        printf("i2: %d, i2 cond: %d, loc: %d\n", inventoryobject.update2, updates[ inventoryobject.update2 ].condition, locationitem );
#endif
    if ( inventoryobject.update1 && updates[ inventoryobject.update1 ].condition == locationitem )
    {
        inventoryupdate = inventoryobject.update1;
    }
    else if ( inventoryobject.update2 && updates[ inventoryobject.update2 ].condition == locationitem )
    {
        inventoryupdate = inventoryobject.update2;
    }

    // Check if the location item matches and triggers an action 
    if ( locationupdate && updates[ locationupdate ].condition == inventoryitem)
    {
        if ( locs[curloc].objects[2] && ( updates[ locationupdate ].new_item || updates[ inventoryupdate ].new_item ) )
        {
            // TODO: check all object locations for a free spot
            //       check location item_update for a new spot
            printf( "You can't do that action here: there is no room to do that.\n" );
            return;
        }

        // Order of updates are important
        if ( inventoryupdate > locationupdate )
        {
            update_item( locationupdate, inventoryitemidx2, locationitemidx, curloc );
            update_item( inventoryupdate, inventoryitemidx, -1, curloc );
        }
        else
        {
            update_item( inventoryupdate, inventoryitemidx, -1, curloc );
            update_item( locationupdate, inventoryitemidx2, locationitemidx, curloc );
        }
    }
    else
    {
        printf( "You cant use it on that.\n" );
        return;
    }
}

void update_item( int _updateIdx, int _inventoryIdx, int _locationIdx, int _loc )
{
    printf( "%s\n", updates[ _updateIdx ].description ); 

    // if Add new item
    // TODO: find empty spot
    if ( !locs[ _loc ].objects[ 2 ] )
        locs[ _loc ].objects[ 2 ] = updates[ _updateIdx ].new_item;

    // Update item in inventory (if applicable)
    if ( _inventoryIdx != -1 )
        user_inventory.objects[ _inventoryIdx ] = updates[ _updateIdx ].item_update;

    // Update item on location (if applicable)
    if ( _locationIdx != -1 )
        locs[_loc].objects[ _locationIdx ] = updates[ _updateIdx ].item_update;

    // Update location direction
    toggle_location( updates[ _updateIdx ].toggle_location, _loc );
};

void toggle_location( int _direction, int _loc )
{
    if ( !_direction )
        return;

    if ( _direction & NORTH )
        locs[ _loc ].north = -locs[ _loc ].north;
    if ( _direction & SOUTH )
        locs[ _loc ].south = -locs[ _loc ].south;
    if ( _direction & EAST )
        locs[ _loc ].east = -locs[ _loc ].east;
    if ( _direction & WEST )
        locs[ _loc ].west = -locs[ _loc ].west;
    if ( _direction & UP )
        locs[ _loc ].up = -locs[ _loc ].up;
    if ( _direction & DOWN )
        locs[ _loc ].down = -locs[ _loc ].down;

    int success = 1;
    if ( _direction & SPECIAL1 )
        success &= handle_special( 0 );

    if ( _direction & SPECIAL2 )
        success &= handle_special( 1 );

    if  ( !success )
        printf("Nothing happened.\n" );
}

int handle_special( int _idx )
{
    // read update
    int item = updates[ specials[ _idx ].update ].condition;

    // on location, find condition item
    for ( int i=0; i < 3; i++ )
    {
        if ( locs[ specials[ _idx ].location ].objects[i] == item )
        {
            update_item( specials[ _idx ].update, -1, i, specials[ _idx ].location );
            return 1;
        }
    }

    return 0;
}

int find_locationindex( char* _locationstr, int _loc )
{
  char utemp[200];
  if ( emptystring(_locationstr) )
    return 0;

    for ( int i=0; i < 3; i++ )
    {
        if (locs[_loc].objects[i])
        {
            strcpy(utemp, objs[locs[_loc].objects[i]].name);
            ucase(utemp);

#ifdef DEBUG
            if (strcmp(utemp, _locationstr)==0||strcmp("*", _locationstr)==0)
#else
            if (strcmp(utemp, _locationstr)==0)
#endif
            {
                // Found item on location
                return i;
            }
        }
    }

    return -1;
}

int find_inventoryindex( char* inventorystr )
{
  char utemp[200];
  if ( emptystring(inventorystr) )
    return -1;

    for ( int i=0; i < 20; i++ )
    {
      if (user_inventory.objects[i])
      {

        strcpy(utemp, objs[user_inventory.objects[i]].name);
        ucase(utemp);
        if ((strcmp(utemp, inventorystr))==0)
            return i;
      }
    }
    return -1;
}

void list_items( int* _objects, int _count )
{
    int firstone = 1;
    for ( int i=0; i < _count; i++ )
    {
      if (_objects[i])
      {
        if (!firstone) printf(", ");
        printf("%s %s", objs[_objects[i]].prefix,
          objs[_objects[i]].name);
#ifdef DEBUG
        if (objs[_objects[i]].pickup != 0 )
        printf( "(!)" );
#endif



        firstone = 0;
      }
    }

    if (firstone)
        printf("nothing");

    printf( ".\n" );
};

void spell_directions(int loc)
{
  int firstone = 1;
#ifdef DEBUG
  if (locs[loc].north != 0 )
#else
  if (locs[loc].north > 0 )
#endif
  {
    if (!firstone) printf(", ");
    printf("north");
#ifdef DEBUG
    printf("(%d)", locs[loc].north );
#endif
    firstone = 0;
  }
#ifdef DEBUG
  if (locs[loc].south != 0 )
#else
  if (locs[loc].south > 0 )
#endif
  {
    if (!firstone) printf(", ");
    printf("south");
#ifdef DEBUG
    printf("(%d)", locs[loc].south );
#endif
    firstone = 0;
  }
#ifdef DEBUG
  if (locs[loc].east != 0 )
#else
  if (locs[loc].east > 0 )
#endif
  {
    if (!firstone) printf(", ");
    printf("east");
#ifdef DEBUG
    printf("(%d)", locs[loc].east );
#endif
    firstone = 0;
  }
#ifdef DEBUG
  if (locs[loc].west != 0 )
#else
  if (locs[loc].west > 0 )
#endif
  {
    if (!firstone) printf(", ");
    printf("west");
#ifdef DEBUG
    printf("(%d)", locs[loc].west );
#endif
    firstone = 0;
  }
#ifdef DEBUG
  if (locs[loc].up != 0 )
#else
  if (locs[loc].up > 0 )
#endif
  {
    if (!firstone) printf(", ");
    printf("up");
#ifdef DEBUG
    printf("(%d)", locs[loc].up );
#endif
    firstone = 0;
  }
#ifdef DEBUG
  if (locs[loc].down != 0 )
#else
  if (locs[loc].down > 0 )
#endif
  {
    if (!firstone) printf(", ");
    printf("down");
#ifdef DEBUG
    printf("(%d)", locs[loc].down );
#endif
    firstone = 0;
  }

  if (firstone)
    printf("none");
  printf(".");
}

void go_location(int loc)
{
    if (loc > 0 )
    {
        curloc = loc;
        location_look(loc);
    }
    else
    {
        printf("You can't go there.\n");
    }

}

void exit_game(void)
{
  printf("Goodbye.");
  exitflag = 1;
}

