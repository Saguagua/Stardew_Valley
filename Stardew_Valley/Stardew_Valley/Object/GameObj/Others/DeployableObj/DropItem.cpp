#include "framework.h"
#include "DeployableObject.h"
#include "DropItem.h"

DropItem::DropItem()
{
    _collider = make_shared<CircleCollider>(10);
    _collider->SetDebug(true);
}

void DropItem::Update()
{
    if (_pop)
    {
        if (_tmpPos.y > _collider->GetWorldPos().y)
        {
            _pop = false;
            _power = 0;
        }
        if (_power < _maxPower)
        {
            _power = 50;
        }

        _power -= GRAVITY * _speed;

        _collider->AddPos(Vector2(_xDir, DELTA_TIME * 10 * _power));
    }
    else
    {
        if (_power < -_range)
            _speed = 0.2f;
        
        else if (_power > _range)
            _speed = -0.2f;
        
        _power += GRAVITY * _speed;

        _collider->AddPos(Vector2(0.0f, DELTA_TIME * 5 * _power));
    }

    _collider ->Update();
}

void DropItem::Render(shared_ptr<Sprite> renderer)
{
    _collider->GetTransform()->Set_World(0);
    renderer->ChangePicture(_name, 0);
    renderer->Render();
    _collider->Render();
}



void DropItem::Spawn(string name, string itemName, Vector2 pos)
{
    _isActive = true;
    _name = name;
    _itemName = itemName;
    _collider->SetPos(pos + Vector2(0, 5));
    _collider->Update();

    _xDir = rand() / (float)RAND_MAX;
    _xDir -= 1.0f; //여긴 다시 체크

    _power = 50.0f;
    _pop = true;
    _tmpPos = pos;
    _speed = 0.5f;
}
