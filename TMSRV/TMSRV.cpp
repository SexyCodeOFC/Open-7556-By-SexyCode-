#include "stdafx.h"
#include "TMSRV.h"
#include "ConstantPatch.h"
#include "HookPatch.h"
#include <time.h>
#include <io.h>

#include <fcntl.h>
bool TMSRV::initialize()
{
	 
	if (!ConstantPatch::instance().initialize())
		return false;

	if (!HookPatch::instance().initialize())
		return false;

	if (!Func::ReadMileageListItem())
		return false;

	if (!Func::StartCoinsNPC())
		return false;

	// Gera uma semente para nosso gerador de aleatórios
	Rnd::instance().Seed(uint32_t(time(0)));
	return true;
}
void TMSRV::cleanup()
{

}
