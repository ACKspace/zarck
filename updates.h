// NOTE: order of updates is of importance; they will both be 'spelled'
//          condition                   item_update, new_item, toggle_locations
update updates[] = { 
    { 0, "", 0, 0 },
    { DISPLAY, "you take your broken phone", 0, 0, 0 },       // broken phone accepts display
    { JUMPSTARTER, "you take your broken phone", 0, 0, 0 },  // broken phone accepts jump starter

    { DISPLAY, "you take your jump started phone", 0, 0, 0 },       // jump started phone accepts display
    { JUMPSTARTER, "you take your cracked phone", 0, 0, 0 },  // cracked phone accepts jump starter

    { PHONE_BROKEN, "put the new display in it", 0, PHONE_DEPLETED, 0 }, // display accepts broken phone
    { PHONE_CRACKED, "put the new display in it", 0, PHONE, 0 }, // display accepts cracked phone

    { PHONE_BROKEN, "put the jumpstarter on it", 0, PHONE_CRACKED, 0 }, // jump starter accepts broken phone
    { PHONE_DEPLETED, "put the jumpstarter on it", 0, PHONE, 0 }, // jump starter accepts depleted phone
    { QUICKEY, "you take the lasertag, open it with the quickey", LASERTAG_EMPTY, BATTERIES, 0 },
    { LASERTAG, "and take its batteries out.  This could be useful for a makeshift jumpstarter.", QUICKEY, 0, 0 },
    { PATCHCABLES, "you take the batteries", 0, 0, 0 },
    { BATTERIES, "and connect the patchcables to it to make a jumpstarter", 0, JUMPSTARTER, 0 },
    { HATCH, "You grab the stick", 0, 0, 0 }, // TODO: new item STICK (look for free spaces)
    { STICK, "and open the hatch.", 0, 0, WEST },
    { CAR_FIRE, "You grab the fire extinguisher's hose", EXTINGUISHER, 0, 0 },
    { EXTINGUISHER, "and extinguish the fire.", CAR_EXTINGUISHED, KEYS, 0 },
    { NOTE, "you grab your phone", PHONE, 0, 0 },
    { PHONE, "and dial 0118999881999119725..3.", NOTE, 0, SPECIAL1 },
/*REMOTE_JUNCTIONBOX_MOD*/
    { JUNCTIONBOX_MOD, "You hear: \"ACCESS GRANTED\", and the system hangs up.", JUNCTIONBOX_OPEN_GATE, 0, WEST }, // TODO: OPEN ZE GATE
/*REMOTE_ENGINE*/
    { ELEVATOR_OLD, "The engine squeaks, crashes and grinds to a halt. The belt that was driven by\n"
                    "it that goes outside, stops.", ELEVATOR_OFF, LANTERN, 0 },
    { MAILBOX, "You put the rope into the mailbox.", ROPE, 0, 0 },
    { ROPE, "and phish out a flyer.", MAILBOX_PHISHED, FLYER, 0 },
    { MAILBOX, "You put the rope into the mailbox.", ROPE, 0, 0 },
    { ROPE, "and phish out a note.", MAILBOX_EMPTY, NOTE, 0 },
    { DARKNESS, "You grab the lantern", 0, 0, 0 }, // TODO: add lantern in room (needs work)
    { LANTERN, "and turn on the light", 0, DUCAT, 0 }, // 

    { DUMPSTER_LOCKED, "You take the tri-angle-key", TRIANGLE_KEY, 0, 0 },
    { TRIANGLE_KEY, "and open the dumpster.", DUMPSTER_OPEN, THERMOSTATS, 0 },

    { JUNCTIONBOX, "You take the tri-angle-key", TRIANGLE_KEY, 0, 0 },
    { TRIANGLE_KEY, "and open the junctionbox.", JUNCTIONBOX_OPEN, 0, 0 },

    { JUNCTIONBOX_OPEN, "You take the thermostats", 0, 0, 0 },
    { THERMOSTATS, "and connect the relays of the thermostats to it.", JUNCTIONBOX_MOD, 0, 0 },

    // TODO: bug un the bushes: directions don't update both sides
    { SHRUBBERY, "You take the headgeshear", HEDGE_SHEAR, 0, 0 },
    { HEDGE_SHEAR, "and cut away the shrubbery.", 0, 0, EAST },

    { SHRUBBERY_OPPOSITE, "You take the headgeshear", HEDGE_SHEAR, 0, 0 },
    { HEDGE_SHEAR, "and cut away the shrubbery.", 0, 0, WEST },

    { VENDINGMACHINE, "you throw the ducat into the vendingmachine", 0, 0, 0 },
    { DUCAT, "the machine spits out the keychain", VENDINGMACHINE_EMPTY, KEYFOB, 0 },

    { ACK4_DOOR, "you hold the key fob in front of the door", KEYFOB, 0, NORTH },
    { KEYFOB, "and the lock toggles", 0, 0, 0 },

    { ACK1_DOOR, "you grab the lockpick rake", LOCKPICK_SET, 0, 0 },
    { LOCKPICK_SET, "and rake the lock open", ACK1_DOOR_OPEN, 0, EAST },

    { DOOR_LOCKED, "You try one of the keys", KEYS, 0, 0 },
    { KEYS, "and manage to open the door", DOOR_UNLOCKED, 0, NORTH },

    { OLD_DOOR_LOCKED, "You use to classic key", CLASSIC_KEY, 0, 0 },
    { CLASSIC_KEY, "to open the classic door", OLD_DOOR_UNLOCKED, 0, NORTH },

    { ENGINE_RUNNING, "You take out the spanner", ENGINE_STOPPED, 0, 0 }, 
    { SPANNER, "and throw it in the works", 0, 0, SPECIAL2 },

    { VAULT_DOOR, "You take the set of keys, try a couple..", KEYS, 0, 0 },
    { KEYS, "unlock the door and pull the big lever to open the door.", VAULT_DOOR_OPEN, 0, SOUTH },
};

// Only 2 specials
special specials[] = {
    { 11, REMOTE_JUNCTIONBOX_MOD },
    { 50, REMOTE_ENGINE }
};

/* Tests:
need:
note
lasertag
stick
keys



1 : START
p phone
n
n
n
e
n
    16 : blinky car
p rope
p lasertag
s
w
n
n
e
    19 : T-stick
p stick
e
    28 : mailbox
use rope mailbox
p flyer
use rope mailbox
p note
s
d
n
    38 : extinguisher
p extinguisher
w
w
s
s
s
d
w
s
e
    4 : burning car
use extinguisher car
p keys
w
n
n
n
n
n
e
e
u
s
s
d
    32 : vault door
use keys door
s
    67 : serverroom
p patchcables
use stick hatch
w
u
u
n
e
    59 : hACKspace 3
p quickey
n
    60 : slackspace3
p lockpick-kit
s
w
s
d
s
s
    47 : ACK1 locked
use lockpick-kit door
e
    66 : ACKspace1
use phone display
TODO: look for free space(s)
p phone
use quickey lasertag
p batteries
use patchcables batteries
p jumpstarter
use jumpstarter phone
p phone
w
n
TODO: window east/west
w
n
    42 : hedgeshear
p hedgeshear
s
w
w
use hedgeshear shrubbery
w
s
s
e
    49 : museum locked
use keys door
n
    50 : museum
p key
s
w
n
n
TODO BUG:
use hedgeshear shrubbery
e
e
    44 : engineroom locked
use key door
n
    46 : engineroom
p spanner
use spanner engine
s
w
w
s
s
e
n
    50 : museum
p lantern
s
w
w
n
n
e
    15 : darkness
use lantern darkness
p ducat
u
n
e
TODO: 36 keyfob up heavy door?
    e
    s
    d
    s
    w
    u
    n
35 : core z
use ducat vendingmachine
p keychain
s
u
u
e
    62 : ACKspace4 locked
use keychain door
n
    63 : ACKspace4
p tri-angle-key
s
w
d
d
n
e
n
e
s
    56 : dumpster
use tri-angle-key dumpster
p thermostats
n
w
w
w
s
s
s
use tri-angle-key junctionbox
use thermostats junctionbox
use note phone
west
*/
