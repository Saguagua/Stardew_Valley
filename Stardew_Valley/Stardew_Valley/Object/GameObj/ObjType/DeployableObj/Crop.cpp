#include "framework.h"
#include "DeployableObject.h"
#include "Crop.h"

void Crop::Update()
{
	if (_quality == 0)
	{
		_name = "BLANK";
		return;
	}

	if (_progress < _period)
	{
		_progress++;

		if (_progress % 2 == 0)
			_index++;
	}

	_quality -= 1;

	if (_water)
		_quality += 2;
	
	if (_ferti)
		_quality += 2;

	_water = false;
}

void Crop::Interaction()
{
	if (_progress < _period)
		return;

	ObjectSpawner::GetInstance()->ActiveDropItem("Potato", "Potato", _centerPos, 2);
}

