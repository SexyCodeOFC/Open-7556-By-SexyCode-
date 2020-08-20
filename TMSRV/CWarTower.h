#include <stdio.h>
#include "stdafx.h"

class CWarTower
{
private:
	CWarTower();

public:

	static void __stdcall GuildProcess(tm* timeinfo);

	static void __stdcall MobKilled(int target, int conn, int PosX, int PosY);
	static void __stdcall CGenerateMob(int index, int PosX, int PosY, int tmob);
	static BOOL TowerAttack(int conn, int idx);
	static void ProcessEnd(tm* timeinfo);
};