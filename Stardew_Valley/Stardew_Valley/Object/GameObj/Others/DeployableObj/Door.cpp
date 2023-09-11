#include "framework.h"
#include "Door.h"

Door::Door(string name,  Vector2 pos)
    :DeployableObject(Type::DOOR, name, pos)
{
}

void Door::Interaction()
{
    if (KEY_DOWN(VK_RBUTTON))
    {
        DungeonSystem::GetInstance()->NextStage();
    }
    
}

vector<int> Door::GetProperty()
{
    return vector<int>(2, (0,0));
}
