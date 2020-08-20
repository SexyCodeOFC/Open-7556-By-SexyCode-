#pragma once

#include <windows.h>

#include <stdlib.h>
#include <time.h>

#include <stdio.h> 
#include <iostream> 

#include <cstdint>
#include <cassert>
#include <tlhelp32.h>
#include <list>
#include <Shellapi.h>
#include <vector>
#include <future>
#include <array>
#include <memory>
#include <stdexcept>

#include <Rpc.h>
#include <functional>
#include <map>
#include <singleton.h>
#include <tlhelp32.h>
#include <process.h>
#include <fstream>
#include <io.h>
#include <Urlmon.h>
#include <mshtmhst.h>
#include <algorithm>
#include <string>

#include <packetstruct.h>
#include <structs.h>
#include <nativefunctions.h>
#include <ItemEffect.h>
#include <singleton.h>

#include "Global.h"
#include "Functions.h"

using namespace std;
using std::search; using std::count; using std::string;
#pragma comment(lib, "Rpcrt4.lib")



enum Costumes
{
	Valquiria = 1,
	Esqueleto,
	Romano,
	Kalintz_M,
	Kalintz_F,
	Draco,
	Bruxa,
	RedSanta,
	WhiteSanta,
	Purple_Rudolph = 0xD,
	Blue_Rudolph,
	White_Police,
	Black_Police,
	Blindness,
	Deafness,
	Hanbok,
	Rabbit_Girl,
	ST_Set,
	Kingdom_Red,
	Kingdom_Blue,
	Gandi,
	Odin,
	Rabbit,
	Dancing_Girl,
	Feudal,
	Oriental,
	Plant,
	Succubus,
	Tigregelo,
	Oriental_F,
	Elegant,
	Dosa,
	Feudal_F,
};

enum Error
{
	NoError = 0,
	Size,
	PacketCraft,
	ClientRange,
	ClientOff,
	OtherClientRange,
	OtherClientOff,
	ClientOrOtherClientRange,
	ClientOrOtherClientOff,
	ItemError,
	ItemRange,
	InternalError,
	CityError,
	Gold,
	EventNotFound,
	Exception,
	LoginSize,
	Database,
	Range,
	MobError
};

enum PacketSide
{
	CLIENT,
	SERVER
};


extern char LoadFileName[24];
