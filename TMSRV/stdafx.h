#pragma once

#include <Windows.h>
#include <singleton.h>

using namespace std;
#include <cstdint>
#include <cassert>
#include <vector>
#include <ctime>
#include <stdint.h>
#include <timeapi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma comment(lib, "winmm.lib")

#include <structs.h>
#include <packetstruct.h>
#include <nativefunctions.h>
#include <random.h>
#include <ItemEffect.h>
#include "HookImpl.h"
#include "Global.h"
#include "Functions.h"
#include "ProcessClientMessage.h"
#include "ProcessSecMinTimer.h"
#include "ConstantPatch.h"
#include "Language.h"
#include "CWarTower.h"
#include <time.h>