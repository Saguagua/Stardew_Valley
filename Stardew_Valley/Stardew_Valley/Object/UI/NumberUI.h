#pragma once
class NumberUI
{
public:
	NumberUI(int num, int maxCount, Vector2 size);
	~NumberUI() {}

	void Render();
	void Update(); //�ִϸ��̼� ������ ����� ��
	
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

