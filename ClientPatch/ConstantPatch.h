#pragma once

class Fixed : public Singleton<Fixed>
{
protected:
	friend class Singleton<Fixed>;
	Fixed() {}
	virtual ~Fixed() {}
	Fixed(const Fixed&) = delete;
	Fixed& operator=(const Fixed&) = delete;

private:
	static bool setNewIconesSkill();
	static bool setEffectStringBuffer();
	static bool setNewResolution();
	static bool MontariasDano();

	static EffectName pEffectName[MAX_EFFECT_NAME];

public:
	bool initialize()
	{
		try
		{
			setNewIconesSkill();
			setEffectStringBuffer();
			setNewResolution();
			MontariasDano();

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

};