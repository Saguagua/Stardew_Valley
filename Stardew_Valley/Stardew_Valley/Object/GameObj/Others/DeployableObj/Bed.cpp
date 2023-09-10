#include "framework.h"
#include "Bed.h"

Bed::Bed(string name, Vector2 pos)
    :DeployableObject(DeployableObject::Type::BED, name, pos)
{
}

void Bed::Interaction()
{
    //하루 끝내기  Timer->
    //플레이어 초기화 

    if (KEY_DOWN(VK_RBUTTON))
        TIMER->SetNextDay();
}

vector<int> Bed::GetProperty()
{
    return vector<int>(2, (0, 0));
}
