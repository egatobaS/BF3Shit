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

#include "SimpleIni.h"

#include "EASTL/algorithm.h"
#include "EASTL/allocator.h"
#include "EASTL/bitset.h"
#include "EASTL/core_allocator_adapter.h"
#include "EASTL/deque.h"
#include "EASTL/fixed_allocator.h"
#include "EASTL/fixed_hash_map.h"
#include "EASTL/fixed_hash_set.h"
#include "EASTL/fixed_list.h"
#include "EASTL/fixed_map.h"
#include "EASTL/fixed_set.h"
#include "EASTL/fixed_string.h"
#include "EASTL/fixed_substring.h"
#include "EASTL/fixed_vector.h"
#include "EASTL/functional.h"
#include "EASTL/hash_map.h"
#include "EASTL/hash_set.h"
#include "EASTL/heap.h"
#include "EASTL/iterator.h"
#include "EASTL/list.h"
#include "EASTL/map.h"
#include "EASTL/memory.h"
#include "EASTL/set.h"
#include "EASTL/sort.h"
#include "EASTL/string.h"
#include "EASTL/type_traits.h"
#include "EASTL/utility.h"
#include "EASTL/vector.h"

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

extern bool ShouldSetIni;

using namespace std;