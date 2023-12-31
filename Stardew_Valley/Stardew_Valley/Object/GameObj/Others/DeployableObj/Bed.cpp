#include "framework.h"
#include "Bed.h"

Bed::Bed(string name, Vector2 pos)
    :DeployableObject(DeployableObject::Type::BED, name, pos)
{
    _cb = std::bind(&Bed::SceneChange, this);
}

void Bed::Interaction()
{
    if (PLAYERUI->GetBagActive())
        return;
    //하루 끝내기  Timer->
    //플레이어 초기화 

    if (KEY_DOWN(VK_RBUTTON))
    {
        SCENEMANAGER->_cover->FadeStart(_cb, nullptr);
    }
}

vector<int> Bed::GetProperty()
{
    return vector<int>(2, (0, 0));
}

void Bed::SceneChange()
{
    SCENEMANAGER->ChangeScene(SceneManager::DAYEND);
}
