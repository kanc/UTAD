#ifndef BASE_HH
#define BASE_HH

#include <Windows.h>
#include <stdlib.h>
#include "Bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "Hero.h"
#include "InputManager.h"
#include "RainDrop.h"
#include "World.h"

const int NUMDROPS = 30;
const int LIFEMAX = 30;
const int LIFEMIN = 15;
const int TIMETOREBORN = 10;
const int WORLDWIDTH = 80;
const int WORLDBEGIN = 0;
const int FLOORLINE = 15;
const char KEYLEFT = 'o';
const char KEYRIGHT = 'p';
const char LEFTFIRE = 'q';
const char RIGHTFIRE = 'w';
const char QUIT = 's';

#endif