#ifndef ANTI_RE_H
#define ANTI_RE_H
class Protect
{

private:
	static int Speed();
	static int Range();
	static int Explosao();
	static int SMO();
	static int Unk();
	static int Wall();
	static int SkillRange();
	static int CheckAddress();

	static int CheckTitle();
	static int CheckInjection();
	static int NomeJanela();
	static bool Titles(LPCTSTR WindowTitle);

	

public:
	static int Validar();
	static void CheckNewDll();
	static bool IsInsideVPC()
	
	{
		bool rc = false;

		__try
		{
			_asm push ebx
			_asm mov  ebx, 0
			_asm mov  eax, 1


			_asm __emit 0Fh
			_asm __emit 3Fh
			_asm __emit 07h
			_asm __emit 0Bh

			_asm test ebx, ebx
			_asm setz[rc]
				_asm pop ebx
		}

		__except (EXCEPTION_EXECUTE_HANDLER)//__except (Func::IsInsideVPC_exceptionFilter(GetExceptionInformation()))
		{
		}

		return rc;
	}
	static bool IsInsideVMWare()
	{

		bool rc = true;

		__try
		{
			__asm
			{
				push   edx
				push   ecx
				push   ebx

				mov    eax, 'VMXh'
				mov    ebx, 0
				mov    ecx, 10
				mov    edx, 'VX'

				in     eax, dx

				cmp    ebx, 'VMXh'
				setz[rc]

				pop    ebx
				pop    ecx
				pop    edx
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			rc = false;
		}

		return rc;
	}
};

#endif // !ANTI_RE_H
