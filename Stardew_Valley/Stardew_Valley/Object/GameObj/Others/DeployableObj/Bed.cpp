#include "framework.h"
#include "Bed.h"

Bed::Bed(string name, Vector2 pos)
    :DeployableObject(DeployableObject::Type::BED, name, pos)
{
}

void Bed::Interaction()
{
    //�Ϸ� ������  Timer->
    //�÷��̾� �ʱ�ȭ 

    if (KEY_DOWN(VK_RBUTTON))
        TIMER->SetNextDay();
}

vector<int> Bed::GetProperty()
{
    return vector<int>(2, (0, 0));
}
