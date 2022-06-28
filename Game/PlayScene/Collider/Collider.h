/*
�����蔻����񂷂��߂����̃N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once





//�~���\����
struct Circle
{
	//���W
	Vector2XZ mCenter;
	//���a
	float mRadius;

	//�R���X�g���N�^
	//center(�����S���W)�Aradius(���̔��a)
	Circle(const Vector2XZ& center, float radius)
		: mCenter(center)
		, mRadius(radius)
	{
	}

	Circle()
		: mCenter()
		, mRadius()
	{
	}
};


//�������\����
struct LineSegment
{
	//�����̊J�n�_
	DirectX::SimpleMath::Vector2 mStart;
	//�����̏I�~�_
	DirectX::SimpleMath::Vector2 mEnd;

	//�R���X�g���N�^
	//�����Fstart(�����̊J�n�_���W)�Aend(�����̏I�~�_���W)
	LineSegment(const DirectX::SimpleMath::Vector2& start, const DirectX::SimpleMath::Vector2& end)
		:mStart(start)
		, mEnd(end)
	{}
	LineSegment()
		: mStart()
		, mEnd()
	{
	}
};

//�����\����
struct Sphere
{
	//���̒��S���W
	DirectX::SimpleMath::Vector3 mCenter;
	//���̔��a
	float mRadius;

	//�R���X�g���N�^
	//center(�����S���W)�Aradius(���̔��a)
	Sphere(const DirectX::SimpleMath::Vector3& center, float radius)
		: mCenter(center)
		, mRadius(radius)
	{
	}

	Sphere()
		: mCenter()
		, mRadius()
	{
	}
};


//AABB�Ǘ��\����
struct AABB
{
	//BOX�̍ŏ����W
	DirectX::SimpleMath::Vector3 mMin;
	//BOX�̍ő���W
	DirectX::SimpleMath::Vector3 mMax;

	//�R���X�g���N�^
	//�����Fmin(BOX�̍ŏ����W)�Amax(BOX�̍ő���W)
	AABB::AABB(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
		: mMin(min)
		, mMax(max)
	{
	}

	AABB::AABB()
		: mMin()
		, mMax()
	{
	}
	//�����蔻���ݒ肷��
	//�����Fmin(BOX�̍ŏ����W)�Amax(BOX�̍ő���W)
	void SetCollider(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
	{
		mMin = min;
		mMax = max;
	}

	//������2������߂鏈��
	float MinDistSq(const DirectX::SimpleMath::Vector3& point) const;
};

//�����蔻����܂Ƃ߂�Singleton
class Collider
{
private:
	//���g
	static Collider* sCollider;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete
	Collider(const Collider& collider) = delete;
	Collider operator=(const  Collider& collider) = delete;

	//�R���X�g���N�^
	Collider() = default;

	//�f�X�g���N�^
	~Collider() = default;

public:

	//���g�̃C���X�^���X
	static Collider& GetColliderInstance();

	void Destroy()const;
	bool Intersect(AABB* box1, AABB* box2);
	bool Intersect(Sphere* s,AABB* box);

	bool Intersect(const Circle& circle, const DirectX::SimpleMath::Vector2& pixel);
	bool Intersect(const Circle& circle1, const Circle& circle2);

	bool Intersect(const LineSegment& line1, const LineSegment& line2,DirectX::SimpleMath::Vector2& returnPosition);



private:
	float Dot(const DirectX::SimpleMath::Vector3&vel1, const DirectX::SimpleMath::Vector3& vel2);
	float Sqrt(const float& num);
	float Cross( const DirectX::SimpleMath::Vector2& a,  const DirectX::SimpleMath::Vector2& b);
};
