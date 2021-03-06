// SPRITES
#define SPRITES_COUNT 8
#define SPRITES_SIZE 8

#define SPRITE_CLEAR 0
#define SPRITE_DINO1 1
#define SPRITE_DINO2 2
#define SPRITE_JUMP 3
#define SPRITE_DIED 4
#define SPRITE_TREE 5
#define SPRITE_ROCK 6
#define SPRITE_COIN 7

byte sprites[SPRITES_COUNT][SPRITES_SIZE] = {{B00000,
                                              B00000,
                                              B00000,
                                              B00000,
                                              B00000,
                                              B00000,
                                              B00000,
                                              B00000},
                                             {B00000,
                                              B00111,
                                              B00111,
                                              B00110,
                                              B10110,
                                              B11111,
                                              B01010,
                                              B01010},
                                             {B00000,
                                              B00110,
                                              B00110,
                                              B00100,
                                              B10110,
                                              B11111,
                                              B00101,
                                              B00101},
                                             {B00111,
                                              B00111,
                                              B00110,
                                              B00110,
                                              B11111,
                                              B11010,
                                              B01010,
                                              B00000},
                                             {B10010,
                                              B00101,
                                              B01000,
                                              B00010,
                                              B10100,
                                              B00010,
                                              B01010,
                                              B10001},
                                             {B00000,
                                              B00100,
                                              B00100,
                                              B10100,
                                              B10101,
                                              B01110,
                                              B00100,
                                              B00100},
                                             {B00000,
                                              B00000,
                                              B00000,
                                              B00110,
                                              B01010,
                                              B01101,
                                              B11011,
                                              B10111},
                                             {B00000,
                                              B00000,
                                              B00000,
                                              B01010,
                                              B11111,
                                              B11111,
                                              B01110,
                                              B00100}};