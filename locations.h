//                                      N, S, E, W, U, D, 3 objects
location locs[] = {
/* 0*/{ "This location does not exist", 0, 0, 0, 0, 0, 0,   { 0, 0, 0 } },
/* 1*/{ "About 30 meters east lingers a small fire.  You see some dim light on the north\n"
        "side and a little more light on the south side with a sign saying \"SOUTH EXIT\".\n",                             
                                        2, 3, 4, 0, 0, 0,   { PHONE_BROKEN, FIRE, 0 } }, // START
/* 2*/{ "At north, there is a car ramp going up and outside; light is shining in.\n"
        "There is also a dim light east of you.\n",
                                        11, 1, 15, 0, 0, 0,   { 0, 0, 0 } }, // south of gate
/* 3*/{ "You are outside, of what appears to be a parking garage.\n"
        "The exit ramp leads east.\n",
                                        1, 0, 5, 0, 0, 0,   { 0, 0, 0 } }, // utter south
/* 4*/{ "You are standing next to a car which, apart from a small fire is completely\n"
        "burned out.  There is some light shining down from a concrete staircase.\n",
                                        0, 0, 0, 1, 7, 0,   { CAR_FIRE, 0, 0 } }, // south-stairs-south
/* 5*/{ "You are standing at a gate. On your west, there is a ramp going down. North,\n"
        "there is a path as far as you can see, and east a small path\n",
                                        6, 0, 49, 3, 0, 0,   { GATE_CLOSED, 0, 0 } },
/* 6*/{ "You are standing next to a parking lot.\n",
                                        7, 5, 0, 51, 0, 0,   { 0, 0, 0 } },
/* 7*/{ "You are standing next to a staircase that looks like a bus shelter.  Opposite\n"
        "of that, there is a shrubbery.",
                                        8, 6, -45, 52, 0, 4,   { SHRUBBERY, 0, 0 } },
/* 8*/{ "You are standing next to a parking lot.  The shrubbery continues here\n"
        "along the east side\n",
                                        9, 7, 0, 53, 0, 0,   { SHRUBBERY, 0, 0 } },
/* 9*/{ "You are standing next to a staircase that looks like a bus shelter.\n"
        "Opposite of that, there is a fairly tall building made of concrete next\n"
        "with some shrubbery.\n",
                                        10, 8, -43, 54, 0, 15,   { SHRUBBERY, 0, 0 } },
/*10*/{ "You are standing at an intersection. The east way has a slanted curbstone.\n"
        "Between west and north the road also has a sidewalk.\n",
                                        14, 9, 36, 11, 0, 0,   { 0, 0, 0 } },
/*11*/{ "You are standing at a gate. Both north and south have a ramp going down into something that looks like a parking garage.\n",
                                        12, 2, 10, -65, 0, 0,   { MOTORIZED_GATE, JUNCTIONBOX, 0 } },
/*12*/{ "At south, there is a car ramp going up and outside, since light is shining in.\n"
        "There is also some orange blinking light east of you.\n",
                                        17, 11, 13, 0, 0, 0,   { 0, 0, 0 } },
/*13*/{ "You are standing next to a car with its warning lights blinking.\n"
        "There is some light shining down from a concrete staircase.\n",
                                        16, 0, 0, 12, 14, 0,   { CAR_BLINK, 0, 0 } },
/*14*/{ "You are standing next to a staircase that looks like a bus shelter.\n"
        "A sidewalk starts here.\n",
                                        25, 10, 0, 27, 0, 13,   { 0, 0, 0 } },
/*15*/{ "It's pitch black here, except for some light shining down from what appears to\n"
        "be a concrete staircase.\n",
                                        0, 0, 0, 2, 9, 0,   { DARKNESS, 0, 0 } },
/*16*/{ "You are in a car of which someone left abandoned with the lights blinking.\n"
        "Maybe it was to add to the idea of a post-apocalyptical playfield.\n",
                                        0, 13, 0, 0, 0, 0,   { ROPE, LASERTAG, 0 } },
//                                      N, S, E, W, U, D, 3 objects
/*17*/{ "At north, there is light is shining in. This probably leads outside.  There is\n"
        "also a bit of light coming from the south.  There is even a tiny bit of light\n"
        "on the far east.",
                                        18, 12, 21, 0, 0, 0,   { 0, 0, 0 } },

/*18*/{ "You are outside, of what appears to be a parking garage.\n"
        "The exit ramp leads east.\n",
                                        0, 17, 19, 0, 0, 0,   { 0, 0, 0 } },
/*19*/{ "You are at a T-intersection.  There is a ramp going down on your west, and a\n"
        "long path going both south and east.\n",
                                        0, 20, 28, 18, 0, 0,   { STICK, 0, 0 } },

/*20*/{ "You are standing next to a staircase that looks like a bus shelter.\n"
        "Opposite of that, there is a fairly tall building made of concrete.\n",

                                        19, 24, 0, 22, 0, 21,   { 0, 0, 0 } },
/*21*/{ "You are standing on a fairly dark place.\n"
        "There is some light shining down from a concrete staircase.\n",
                                        0, 0, 0, 17, 20, 0,   { 0, 0, 0 } },
/*22*/{ "You are standing on a parking lot.\n",
                                        0, 23, 20, 0, 0, 0,   { 0, 0, 0 } },
/*23*/{ "You are standing on a parking lot.\n",
                                        22, 26, 24, 0, 0, 0,   { 0, 0, 0 } },
/*24*/{ "You are standing next to a parking lot.\n",
                                        20, 25, 0, 23, 0, 0,   { 0, 0, 0 } },
/*25*/{ "You are standing next to a parking lot.\n",
                                        24, 14, 39, 26, 0, 0,   { 0, 0, 0 } },
/*26*/{ "You are standing on a parking lot.\n",
                                        23, 27, 25, 0, 0, 0,   { 0, 0, 0 } },
/*27*/{ "You are standing on a parking lot.\n",
                                        26, 0, 14, 0, 0, 0,   { 0, 0, 0 } },
/*28*/{ "You are standing along a fence with a gate.  The fence is just a bit too high to climb\n"
        "over it.  There are some stairs going up-south, and a sloped path that leads\n"
        "south-southwest.\n",
                                        0, 36, 55, 19, 29, 0,   { MAILBOX, GATE_CLOSED, 0 } },
/*29*/{ "You ar standing at some stairs. Down north, there is a fence. South leads to a building.\n",
                                        28, 30, 0, 0, 0, 28,   { 0, 0, 0 } },
/*30*/{ "You are standing in front of a tall building.  There is a revolving door south\n"
        "of you which is already rotating.\n",
                                        29, 31, 0, 36, 0, 0,   { 0, 0, 0 } },
/*31*/{ "You are inside the building. There is a revolving door north of you which is\n"
        "already rotating.  The building partially collapsed in the back, which renders\n"
        "the elevators useless.  Also, the staircase is heavily damaged.\n",
                                        30, 0, 0, 0, 0, 32,   { DOOR_POWERLESS, ELEVATOR, KEYCABINET } },
/*32*/{ "You are standing in a basement.\n",
                                        0, -67, 0, 0, 31, 0,   { VAULT_DOOR, 0, 0 } },
/*33*/{ "You are standing in a basement.\n",
                                        0, 0, 67, 0, 34, 0,   { VAULT_DOOR_OPEN, 0, 0 } },

/*34*/{ "You are standing in a room that looks to be a central hub of passages.\n",
                                        35, 40, 0, WASHINGROOM, 57, 33,   { STAIRCASE, 0, 0 } },
/*35*/{ "You are standing in a room that looks to be a central hub of passages.\n",
                                        0, 34, 36, 0, 0, 0,   { ELEVATOR, VENDINGMACHINE, 0 } }, // one way east
/*36*/{ "You are standing next to a pair of stairs.\n",
                                        28, 0, 30, 10, -35, 37,   { 0, 0, 0 } },
/*37*/{ "This seems to be a bike shelter.\n",
                                        38, 0, 0, 0, 36, 0,   { 0, 0, 0 } },
/*38*/{ "The bike shelter ends here, but an automatic door opened on the west of you.\n",
                                        0, 37, 0, 39, 0, 0,   { EXTINGUISHER, 0, 0 } },
/*39*/{ "This path went down to some kind of basement access.\n",
                                        0, 0, -38, 25, 0, 0,   { DOOR_POWERLESS, 0, 0 } },
/*40*/{ "You are standing in a passage.\n",
                                        34, 47, 0, 41, 0, 0,   { OPEN_WINDOW, 0, 0 } },
/*41*/{ "There is something shiny on your north\n",
                                        42, 0, 0, 44, 0, 0,   { OPEN_WINDOW, 0, 0 } },
/*42*/{ "You are standing in an outside corner of the building on a small tile pathway.\n",
                                        0, 41, 0, 43, 0, 0,   { HEDGE_SHEAR, 0, 0 } }, // TODO: ball points?
/*43*/{ "You are standing on a small tile pathway.\n",
                                        0, 0, 42, -9, 0, 0,   { SHRUBBERY_OPPOSITE, 0, 0 } },
/*44*/{ "You are standing on a small tile pathway in front of a building.\n",
                                        -46, 0, 41, 45, 0, 0,   { OLD_DOOR_LOCKED, 0, 0 } },
/*45*/{ "You are standing on a small tile pathway.\n",
                                        0, 0, 44, -7, 0, 0,   { SHRUBBERY_OPPOSITE, 0, 0 } },
/*46*/{ "You stand inside a building that appears to be an engine room.\n",
                                        0, 44, 0, 0, 0, 0,   { ENGINE_RUNNING, SPANNER, 0 } },
/*47*/{ "You are standing in a hallway.  South of you seems to be an emergency exit.\n",
                                        40, 48, -66, 0, 0, 0,   { ACK1_DOOR, 0, 0 } }, // TODO: enable exit 48 north
/*48*/{ "You are standing on a small pathway on the head end of a tall building.\n",
                                        -47, 0, 0, 49, 0, 0,   { DOOR_LOCKED, 0, 0 } },
/*49*/{ "You are standing in front of an old building.\n",
                                        -50, 0, 48, 5, 0, 0,   { DOOR_LOCKED, 0, 0 } },
/*50*/{ "Inside the building, it looks like a museum.  Something with an old elevator in it.\n",
                                        0, 49, 0, 0, 0, 0,   { ELEVATOR_OLD, CLASSIC_KEY, 0 } }, // TODO: lantern
/*51*/{ "You are standing on a parking lot.\n",
                                        52, 0, 6, 0, 0, 0,   { 0, 0, 0 } },
/*52*/{ "You are standing on a parking lot.\n",
                                        53, 51, 7, 0, 0, 0,   { 0, 0, 0 } },
/*53*/{ "You are standing on a parking lot.\n",
                                        54, 52, 8, 0, 0, 0,   { 0, 0, 0 } },
/*54*/{ "You are standing on a parking lot.\n",
                                        0, 53, 9, 0, 0, 0,   { 0, 0, 0 } },
/*55*/{ "You stand in a fenced corner.\n",
                                        0, 56, 0, 28, 0, 0,   { GATE_CLOSED, 0, 0 } },
/*56*/{ "You arrived at a distant square.  It's a dead end here.\n",
                                        55, 0, 0, 0, 0, 0,   { DUMPSTER_LOCKED, 0, 0 } },
/*57*/{ "You are standing in a room that looks to be a central hub of passages, third floor.\n",
                                        58, 0, 0, 0, 61, 34,   { STAIRCASE, ELEVATOR, 0 } },
/*58*/{ "You are standing in a hallway.\n",
                                        0, 57, 59, 0, 0, 0,   { ACK3_DOOR, 0, 0 } },
/*59*/{ "You stand in a room that looks abandoned.\n",
                                        60, 0, 0, 58, 0, 0,   { CANDY, QUICKEY, HARDWARE } },
/*60*/{ "You entered a room that probably was for recreational purposes.\n",
                                        0, 59, 0, 0, 0, 0,   { PIZZABOXES, TRASHCANS, LOCKPICK_SET } },
/*61*/{ "You are standing in a room that looks to be a central hub of passages, fourth floor.\n",
                                        0, 0, 62, 0, 0, 57,   { STAIRCASE, SUNRISE, ELEVATOR } },
/*62*/{ "You are standing in a hallway.\n",
                                        -63, 0, 0, 61, 0, 0,   { ACK4_DOOR, 0, 0 } },
/*63*/{ "You are in a room that definitely is for tech users. You can tell it has been visited recently.\n",
                                        0, 62, 64, 0, 0, 0,   { COMPUTER, TRIANGLE_KEY, BOTTLE } },
/*64*/{ "You are in a room that looks like it is meant for recreation.\n",
                                        0, 0, 0, 63, 0, 0,   { BOTTLES, SCREEN, 0 } },
/*65*/{ "CONGRATULATIONS, you found the game's exit! Now go tell xopr how lame this message is.\n",
                                        0, 0, 0, 0, 0, 0,   { 0, 0, 0 } },
/*66*/{ "You are in a room with a stale scent.  It looks like an old hideout for hackers,\n"
"but it seems, it hasn't been visited for years.\n",
                                        0, 0, 0, 47, 0, 0,   { DISPLAY, 0, 0 } },
/*67*/{ "You stand in a room that appears to be an old server room.\n",
                                        32, 0, 0, -33, 0, 0,   { PATCHCABLES, HATCH, SERVER_RACK } },
#ifdef DONT_SHIT_YOUR_PANTS
/*68*/{ "You are standing in a toilet washing room.\n",
                                        // TODO: door doorknob
                                        TOILETROOM, 0, 34, 0, 0, 0,   { PILLS, 0, 0 } },
/*69*/{ "You are standing in the toilet room.\n",
                                        0, WASHINGROOM, 0, 0, 0, 0,   { TOILET, 0, 0 } },


#endif
/*  */{ "\n",
                                        0, 0, 0, 0, 0, 0,   { 0, 0, 0 } },


};

