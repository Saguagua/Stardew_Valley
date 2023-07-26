#pragma once
#include "../../Data/ObjectInfo.h"

class GameObject
{
public:
	GameObject(int itemCode, short count = 1)
		:_itemCode(itemCode), _count(count) {}
	~GameObject() {}

	void SetCode(int code) { _itemCode = code; }

	ObjectInfo::Type GetType() { return _type; }
	int GetCode() { return _itemCode; }
	short GetCount() { return _count; }
	
	virtual void Interaction() {};

protected:
	ObjectInfo::Type _type = ObjectInfo::Type::NONE;
	int _itemCode;
	short _count;
};

