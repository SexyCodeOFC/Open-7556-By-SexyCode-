#include "stdafx.h"
#include "DBSRV.h"
#include "ConstantPatch.h"
#include "HookPatch.h"

bool DBSRV::initialize()
{
	if (!ConstantPatch::instance().initialize())
		return false;

	if (!HookPatch::instance().initialize())
		return false;

	return true;
}
void DBSRV::cleanup()
{

}