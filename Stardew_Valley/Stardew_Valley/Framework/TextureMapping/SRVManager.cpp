#include "framework.h"
#include "SRVManager.h"

SRVManager* SRVManager::_instance = nullptr;

SRVManager::SRVManager()
{
}


shared_ptr<SRV> SRVManager::AddSRV(wstring file)
{
	if (_srvTable.count(file) == 0)
		_srvTable[file] = make_shared<SRV>(file);

	return _srvTable[file];
}

shared_ptr<SRV> SRVManager::AddSRV(wstring file, Vector2 size)
{
	if (_srvTable.count(file) == 0)
		_srvTable[file] = make_shared<SRV>(file, size);

	return _srvTable[file];
}
