#include "framework.h"
#include "Light.h"

Light::Light(string name, Vector2 pos, int lightIndex)
    :DeployableObject(Type::LIGHT, name, pos), _lightIndex(lightIndex)
{
}

void Light::Interaction()
{
    if (KEY_PRESS(VK_RBUTTON))
    {
        LightManager::GetInstance()->DisableLight(_lightIndex);
        OBJECT_SPAWNER->ActiveDropItem(_name, _centerPos);
    }
}

vector<int> Light::GetProperty()
{
    return vector<int>(2, (0,0));
}
