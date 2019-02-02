#include <xtl.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
#include <vector>
#include <iomanip>
#include <locale>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdarg.h>
#include <xboxmath.h>

#include <AtgApp.h>
#include <AtgFont.h>
#include <AtgResource.h>
#include <AtgUtil.h>

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#define POINTERCHK( pointer ) ( pointer && pointer != 0 && HIWORD( pointer ) )

#include "Detour.h"
#include "Utils.h"
#include "Structures.h"
#include "Functions.h"
#include "Drawing.h"
#include "Menu.h"
#include "GameDrawing.h"
#include "MenuOptions.h"
#include "MenuDrawing.h"
#include "Hooks.h"

using namespace std;