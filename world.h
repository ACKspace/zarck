/*
* No Copyright
*
* The person who associated a work with this deed has dedicated the work to the public domain by waiving all of his or her rights to the work worldwide under copyright law, including all related and neighboring rights, to the extent allowed by law.
*
* You can copy, modify, distribute and perform the work, even for commercial purposes, all without asking permission.
*
* See https://creativecommons.org/share-your-work/public-domain/cc0/ for more information on the license.
*/

typedef struct world
{
  int startloc;
  const char* welcome;
} world;

typedef struct inventory
{
  int objects[20];
} inventory;


typedef struct location
{
  const char* text;
  int north, south, east, west;
  int up, down;
  int objects[3];
} location;

typedef struct object
{
  const char* prefix;
  const char* name;
  const char* appearance;
  int pickup;
  int update1;
  int update2;
} object;

typedef struct update
{
  int condition;
  const char* description;
  int item_update;
  int new_item;
  int toggle_location;
} update;

typedef struct special
{
  int location;
  int update;
} special;


int do_command(char *cmd);
int hasInventoryItem( int _item );
void location_look(int loc);
void go_location(int loc);
void exit_game(void);
void beginworld();
void command_loop();
void spell_directions(int loc);
void item_look(char* itemstr);
void item_pickup(char* itemstr, int loc);
void item_drop(char* inventorystr, int loc);
void list_items( int* _objects, int _count );
void item_use(char* inventorystr, char* itemstr);
void update_item( int _updateIdx, int _inventoryIdx, int _locationIdx, int _loc );
void toggle_location( int _direction, int _loc );
int handle_special( int _idx );
int find_locationindex( char* _locationstr, int _loc );
int find_inventoryindex( char* inventorystr );

