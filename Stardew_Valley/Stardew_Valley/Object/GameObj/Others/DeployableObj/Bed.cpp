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
    //�Ϸ� ������  Timer->
    //�÷��̾� �ʱ�ȭ 

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
