#include "framework.h"
#include "FishingHook.h"

FishingHook::FishingHook()
{
	_transform = make_shared<Transform>();
	
}

void FishingHook::Update()
{
	if (!_isActive)
		return;

	if (_transform->GetWorldPos().x > _originPos.x)
	{
		_transform->AddPos(_dir * DELTA_TIME * _power);
		_transform->Update();
		_dir.y -= DELTA_TIME;
	}
}

void FishingHook::Render(shared_ptr<Sprite> renderer)
{
	if (!_isActive)
		return;

	_transform->Set_World();
	renderer->ChangePicture("Potato", 0);
	renderer->Render();
}

void FishingHook::SetActive(Vector2 originPos, Vector2 dir, float power, float angle)
{
	_isActive = true;
	_transform->SetPos(originPos);
	_originPos = originPos;
	_dir = dir;
	_power = power;
	_angle = angle * 3.141592f / 180.0f;
}

//타겟 포스, 오리진 포스로 거리 구하고 파워 거리로 각도 구하면 trans의 x가 target의 xy와 같을 때 멈추기

//void FishingHook::CalculateProjectile()
//{
//	float xVelocity = _power * cos(_angle);
//	float yVelocity = _power * sin(_angle);
//
//
//}
//
////높이 = 수평거리 X tan(발사각) - 중력 X 수평거리 제곱 / 2 X 수평거리 제곱 X cos제곱 발사각
//
//void CalculateProjectile(Projectile& projectile, double angle, double initialVelocity, double time) {
//	double horizontalVelocity = initialVelocity * cos(angle);
//	double verticalVelocity = initialVelocity * sin(angle);
//
//	projectile.x = horizontalVelocity * time;
//	projectile.y = verticalVelocity * time - 0.5 * g * time * time;
//}
//
//int main() {
//	double angle = 3.141582 / 4.0; // 45도
//	double initialVelocity = 20.0; // 초기 속도
//
//	Projectile projectile(0, 0);
//
//	for (double time = 0; time <= 10; time += 0.1) {
//		calculateProjectile(projectile, angle, initialVelocity, time);
//	}
//
//	return 0;
//}