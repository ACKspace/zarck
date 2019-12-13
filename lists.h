enum direction
{
    NORTH =  1,
    SOUTH =  2,
    EAST  =  4,
    WEST  =  8,
    UP    = 16,
    DOWN  = 32,
    SPECIAL1 = 64,
    SPECIAL2 = 128
};

enum updatename
{
    NO_UPDATE,
    BROKENPHONE_DISPLAY,
    DEPLETEDPHONE_DISPLAY,
    CRACKEDPHONE_DISPLAY,
    CRACKEDPHONE_JUMPSTART,
    DISPLAY_BROKENPHONE,
    DISPLAY_CRACKEDPHONE,
    JUMPSTART_BROKENPHONE,
    JUMPSTART_DEPLETEDPHONE,
    LASERTAG_QUICKEY,
    QUICKEY_LASERTAG,
    BATTERIES_PATCHCABLE,
    PATCHCABLE_BATTERIES,
    STICK_HATCH,
    HATCH_STICK,
    EXTINGUISHER_CAR,
    CAR_EXTINGUISHER,
    PHONE_NOTE,
    NOTE_PHONE,
    REMOTE_JUNCTIONBOX_MOD,
    REMOTE_ENGINE,
    ROPE_MAILBOX1,
    MAILBOX_ROPE1,
    ROPE_MAILBOX2,
    MAILBOX_ROPE2,
    LIGHT_DARKNESS,
    DARKNESS_LIGHT,
    KEY_DUMPSTER,
    DUMPSTER_KEY,
    KEY_JUNCTIONBOX,
    JUNCTIONBOX_KEY,
    THERMOSTATS_JUNCTIONBOX,
    JUNCTIONBOX_THERMOSTATS,
    HEDGESHEAR_SHRUBBERY_EAST,
    SHRUBBERY_HEDGESHEAR_EAST,
    HEDGESHEAR_SHRUBBERY_WEST,
    SHRUBBERY_HEDGESHEAR_WEST,
    DUCAT_VENDINGMACHINE,
    VENDINGMACHINE_DUCAT,
    KEYFOB_DOOR,
    DOOR_KEYFOB,
    LOCKPICK_DOOR,
    DOOR_LOCKPICK,
    KEYS_DOOR,
    DOOR_KEYS,
    OLD_KEY_DOOR,
    OLD_DOOR_KEY,
    SPANNER_MACHINE,
    MACHINE_SPANNER,
    KEYS_VAULT,
    VAULT_KEYS
};


enum objectname
{
    NO_OBJECT,
    PHONE_BROKEN,
    PHONE_CRACKED,
    PHONE_DEPLETED,
    PHONE,
    FIRE,
    CAR_FIRE,
    CAR_EXTINGUISHED,
    GATE_CLOSED,
    SHRUBBERY,
    SHRUBBERY_OPPOSITE,
    CAR_BLINK,
    ROPE,
    LASERTAG,
    LASERTAG_EMPTY,
    BATTERIES,
    QUICKEY,
    EXTINGUISHER,
    MAILBOX,
    MAILBOX_PHISHED,
    MAILBOX_EMPTY,
    FLYER,
    NOTE,
    DUCAT,
    VENDINGMACHINE,
    VENDINGMACHINE_EMPTY,
    KEYFOB,
    DUMPSTER_LOCKED,
    DUMPSTER_OPEN,
    TRIANGLE_KEY,
    COMPUTER,
    LOCKPICK_SET,
    ACK1_DOOR,
    ACK1_DOOR_OPEN,    
    DISPLAY,
    KEYS,
    PATCHCABLES,
    JUMPSTARTER,
    HEDGE_SHEAR,
    THERMOSTATS,
    CLASSIC_KEY,
    LANTERN,
    MOTORIZED_GATE,
    JUNCTIONBOX,
    JUNCTIONBOX_OPEN,
    JUNCTIONBOX_MOD,
    ELEVATOR,
    PIZZABOXES,
    TRASHCANS,
    CANDY,
    HARDWARE,
    DOOR_POWERLESS,
    VAULT_DOOR,
    VAULT_DOOR_OPEN,
    HATCH,
    STICK,
    SERVER_RACK,
    STAIRCASE,
    SUNRISE,
    OPEN_WINDOW,
    OLD_DOOR_LOCKED,
    OLD_DOOR_UNLOCKED,
    DOOR_LOCKED,
    DOOR_UNLOCKED,
    ACK3_DOOR,
    ACK4_DOOR,
    DISHES,
    BOTTLE,
    BOTTLES,
    SCREEN,
    KEYCABINET,
    ENGINE_RUNNING,
    ENGINE_STOPPED,
    DARKNESS,
    SPANNER,
    ELEVATOR_OLD,
    ELEVATOR_OFF,
    JUNCTIONBOX_OPEN_GATE,
    INSTRUCTIONS,
#ifdef DONT_SHIT_YOUR_PANTS
    PILLS,
    TOILET,
    PANTS,
    PANTS_DIRTY,
    SHIT,
#endif
    OBJ_LEN
};

enum locationname
{
#ifdef DONT_SHIT_YOUR_PANTS
    // entrance from 34: central hub
    WASHINGROOM = 68,
    TOILETROOM,
#else
    WASHINGROOM = 0,
    TOILETROOM = 0,
#endif
};

