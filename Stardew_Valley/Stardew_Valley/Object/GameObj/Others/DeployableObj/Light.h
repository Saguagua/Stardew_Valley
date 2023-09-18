#pragma once
class Light :public BreakableItem
{
public:
	Light(string name, Vector2 pos, int lightIndex);
	~Light() {}

	virtual vector<int> GetProperty() override;
	virtual void GetDamage(shared_ptr<Item> item) override;

	int _lightIndex;
private:

	short _hp = 1;
};

