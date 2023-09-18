#include "framework.h"
#include "Door.h"

Door::Door(string name,  Vector2 pos)
    :DeployableObject(Type::DOOR, name, pos)
{
    _cb = std::bind(&DungeonSystem::NextStage, DungeonSystem::GetInstance());
}

void Door::Interaction()
{
    if (PLAYERUI->GetBagActive())
        return;

    if (KEY_DOWN(VK_RBUTTON))
    {
        SCENEMANAGER->_cover->_isActive = true;
        SCENEMANAGER->_cover->SetCallBack(_cb);
    }
    
}

vector<int> Door::GetProperty()
{
    return vector<int>(2, (0,0));
}