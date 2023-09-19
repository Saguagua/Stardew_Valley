#include "framework.h"
#include "MoneyManager.h"

MoneyManager* MoneyManager::_instance = nullptr;

MoneyManager::MoneyManager()
{
}

void MoneyManager::Update()
{
	_farmmingPrice = 0;
	_fishingPrice = 0;
	_miningPrice = 0;
	_extraPrice = 0;
	_priceSum = 0;


	for (int i = 0; i < _saleItems.size(); )
	{
		shared_ptr<Item> item = _saleItems.top();
		shared_ptr<SaleInfo> info = DATA->GetSaleInfo(item->GetName());

		short price = info->_price * item->GetCount();

		_priceSum += price;

		switch (info->_type)
		{
		case FARM:
		{
			_farmmingPrice += price;
			break;
		}
		case FISH:
		{
			_fishingPrice += price;
			break;
		}
		case MINE:
		{
			_miningPrice += price;
			break;
		}
		case EXTRA:
		{
			_extraPrice += price;
			break;
		}
		default:
			break;
		}


		_saleItems.pop();
	}

	_playerMoney += _priceSum;
	
}

shared_ptr<Item> MoneyManager::GetTopItem()
{
	if (_saleItems.size() != 0)
		return _saleItems.top();

	return nullptr;
}

shared_ptr<Item> MoneyManager::Undo()
{
	if (_saleItems.size() == 0)
		return nullptr;

	auto item = _saleItems.top();

	_saleItems.pop();

	return item;
}

void MoneyManager::SaleItem(shared_ptr<Item> item)
{
	shared_ptr<Item> copy = make_shared<Item>();
	copy->Copy(item);

	_saleItems.push(copy);
	item->SetItem("BLANK", 0);
}
