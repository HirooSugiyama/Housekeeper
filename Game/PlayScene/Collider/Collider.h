/*
当たり判定を回すためだけのクラス
作成者：杉山
作成日：2021/10/21
*/
#pragma once





//円情報構造体
struct Circle
{
	//座標
	Vector2XZ mCenter;
	//半径
	float mRadius;

	//コンストラクタ
	//center(球中心座標)、radius(球の半径)
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


//線分情報構造体
struct LineSegment
{
	//線分の開始点
	DirectX::SimpleMath::Vector2 mStart;
	//線分の終止点
	DirectX::SimpleMath::Vector2 mEnd;

	//コンストラクタ
	//引数：start(線分の開始点座標)、end(線分の終止点座標)
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

//球情報構造体
struct Sphere
{
	//球の中心座標
	DirectX::SimpleMath::Vector3 mCenter;
	//球の半径
	float mRadius;

	//コンストラクタ
	//center(球中心座標)、radius(球の半径)
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


//AABB管理構造体
struct AABB
{
	//BOXの最小座標
	DirectX::SimpleMath::Vector3 mMin;
	//BOXの最大座標
	DirectX::SimpleMath::Vector3 mMax;

	//コンストラクタ
	//引数：min(BOXの最小座標)、max(BOXの最大座標)
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
	//当たり判定を設定する
	//引数：min(BOXの最小座標)、max(BOXの最大座標)
	void SetCollider(const DirectX::SimpleMath::Vector3& min, const DirectX::SimpleMath::Vector3& max)
	{
		mMin = min;
		mMax = max;
	}

	//距離の2乗を求める処理
	float MinDistSq(const DirectX::SimpleMath::Vector3& point) const;
};

//当たり判定をまとめたSingleton
class Collider
{
private:
	//自身
	static Collider* sCollider;

	//コピーコンストラクタ、コピー代入演算子をdelete
	Collider(const Collider& collider) = delete;
	Collider operator=(const  Collider& collider) = delete;

	//コンストラクタ
	Collider() = default;

	//デストラクタ
	~Collider() = default;

public:

	//自身のインスタンス
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
