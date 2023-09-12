#pragma once
class NumberUI
{
public:
	NumberUI(int num, int maxCount, Vector2 size);
	~NumberUI() {}

	void Render();
	void Update(); //애니메이션 넣으면 사용할 것
	
	void SetNumber(int num);

	shared_ptr<Transform> _transform;
	Vector2 _originPos;
private:
	vector<string> _number;

	shared_ptr<Sprite> _renderer;
	Vector2 _size;
	float _startPos = 0;
	int _maxNumberCount;
	int _distance = 0;
};

