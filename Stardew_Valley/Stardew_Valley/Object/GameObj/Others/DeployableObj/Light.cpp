#include "framework.h"
#include "Light.h"

Light::Light(string name, Vector2 pos, int lightIndex)
    :BreakableItem(name, pos, 1), _lightIndex(lightIndex)
{
	_type = LIGHT;
}



vector<int> Light::GetProperty()
{
    return vector<int>(2, (0,0));
}

void Light::GetDamage(shared_ptr<Item> item)
{
	if (!_isActive)
		return;
	if (item->GetType() == _breakType)
	{
		_hp -= item->GetVals()[2];

		if (_hp <= 0)
		{
			OBJECT_SPAWNER->ActiveDropItem(_name, _centerPos);
			_name = "BLANK";
			_isActive = false;
			LightManager::GetInstance()->DisableLight(_lightIndex);
		}
	}
}
