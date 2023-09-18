#include "framework.h"
#include "Elevator.h"

Elevator::Elevator(string name, Vector2 pos)
    :DeployableObject(DeployableObject::Type::DOOR, name, pos)
{
    _cb = std::bind(&DungeonSystem::Return, DungeonSystem::GetInstance());
}

void Elevator::Interaction()
{
    if (PLAYERUI->GetBagActive())
        return;

    if (KEY_DOWN(VK_RBUTTON))
    {
        SCENEMANAGER->_cover->_isActive = true;
        SCENEMANAGER->_cover->SetCallBack(_cb);
    }
}

vector<int> Elevator::GetProperty()
{
    return vector<int>(2, (0,0));
}
