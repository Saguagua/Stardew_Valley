#include "framework.h"
#include "DeployableObject.h"
#include "Crop.h"

Crop::Crop(string name, Vector2 pos, short progress, short quality)
	:DeployableObject(DeployableObject::Type::CROP, name, pos)
	,_progress(progress), _quality(quality)
{
	shared_ptr<CropInfo> info = DATA->GetCropInfo(name);
	_period = info->_period;
	_imgIndex = info->_levels[_progress - 1];
	_cropType = info->_type;
}

void Crop::Update()
{
	if (_quality == 0)
	{
		_name = "BLANK";
		_imgIndex = 0;
		return;
	}

	if (_progress < _period)
	{
		_progress++;

		_imgIndex = DATA->GetCropInfo(_name)->_levels[_progress - 1];

		_quality -= 1;

		if (_water)
			_quality += 2;

		if (_ferti)
			_quality += 2;
	}

	_water = false;
}

void Crop::Interaction()
{
	if (_progress < _period || _name == "BLANK")
		return;
	if (!KEY_DOWN(VK_LBUTTON))
		return;

	OBJECT_SPAWNER->ActiveDropItem(DATA->GetCropInfo(_name)->_dropName , _centerPos);

	if (_cropType == 1)
	{
		_imgIndex--;
		_progress--;
	}
	else
	{
		_name = "BLANK";
		_imgIndex = 0;
	}
}

vector<int> Crop::GetProperty()
{
	return vector<int>(2 ,(_progress, _quality));
}

