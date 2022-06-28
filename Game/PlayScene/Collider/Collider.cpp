/*
当たり判定を回すためだけのクラス
作成者：杉山
作成日：2021/10/21
*/

#include<pch.h>
#include"Collider.h"

//クラス外部で初期化
Collider* Collider::sCollider = nullptr;

/*=====================
距離の2乗を求める処理
引数	：対象の頂点座標
返り値	：最短距離
=====================*/
float AABB::MinDistSq( const DirectX::SimpleMath::Vector3& point) const
{

	//各軸の差を計算する
	float dx = std::max(mMin.x - point.x, 0.0f);
	dx = std::max(dx, point.x - mMax.x);
	float dy = std::max(mMin.y - point.y, 0.0f);
	dy = std::max(dy, point.y - mMax.y);
	float dz = std::max(mMin.z - point.z, 0.0f);
	dz = std::max(dz, point.z - mMax.z);

	// 距離の2乗を求める
	float square = dx * dx + dy * dy + dz * dz;


	return square;
}

/*===============================================================
インスタンスの取得
引数：なし
戻り値：自身のインスタンス
===============================================================*/
Collider& Collider::GetColliderInstance()
{
	if (sCollider == nullptr)
	{
		sCollider = new Collider();
	}
	return *sCollider;
}

/*===============================================================
自身の削除
引数：なし
返り値：なし
===============================================================*/
void Collider::Destroy() const
{
	if (sCollider != nullptr)
	{
		delete sCollider;
		sCollider = nullptr;
	}	
}


/*==========================================
球とAABBの当たり判定
引数	：s(球情報)、box(AABB情報)
返り値	：衝突判定(True→当たっている)
==========================================*/

bool Collider::Intersect(Sphere* s, AABB* box)
{

	bool flag = false;
	float distSq = box->MinDistSq(s->mCenter);

	if (distSq <= (s->mRadius * s->mRadius))
	{
		flag = true;
	}
	return flag;
}



/*==============================================================
AABB同士の当たり判定
引数	：box1(1つ目のAABB情報),box2(2つ目のAABB情報)
返り値	：衝突判定(True→当たっている)
===============================================================*/

bool Collider::Intersect(AABB* box1, AABB* box2)
{
	AABB boxa, boxb;
	boxa = *box1;
	boxb = *box2;

	if (boxa.mMin.x > boxb.mMax.x) 
	{
		return false;
	}
	if (boxa.mMax.x < boxb.mMin.x) 
	{
		return false;
	}
	if (boxa.mMin.y > boxb.mMax.y) 
	{
		return false;
	}
	if (boxa.mMax.y < boxb.mMin.y) 
	{
		return false;
	}
	if (boxa.mMin.z > boxb.mMax.z) 
	{
		return false;
	}
	if (boxa.mMax.z < boxb.mMin.z) 
	{
		return false;
	}
	return true;
}





/*==============================================================
円と点の当たり判定
引数	：circle(円情報)、pixel(座標)
返り値	：衝突判定(True→当たっている)
===============================================================*/
bool Collider::Intersect(const Circle& circle, const DirectX::SimpleMath::Vector2& pixel)
{
	//簡略化用変数の宣言
	float disA, disB, disC;

	//返り値用変数の宣言
	bool flag = false;

	//距離を求める
	disA = pixel.x - circle.mCenter.x;
	disB = pixel.y - circle.mCenter.z;
	disC = sqrt( disA * disA + disB * disB);

	//距離と半径を比較する
	if (disC <= circle.mRadius)
	{
		flag = true;
	}

	return flag;
}

/*==============================================================
円と円の当たり判定
引数	：circle1(円情報)、circle2(円情報)
返り値	：衝突判定(True→当たっている)
===============================================================*/
bool Collider::Intersect(const Circle& circle1, const Circle& circle2)
{
	float x = abs(circle1.mCenter.x - circle2.mCenter.x);
	float z = abs(circle1.mCenter.z - circle2.mCenter.z);
	float dis = sqrt(x * x + z * z);
	float sum_radius = circle1.mRadius + circle2.mRadius;

	if (dis <= sum_radius)
	{
		return true;
	}
	return false;
}

/*==============================================================
線分同士の当たり判定
引数	：line1(1つ目の線分情報)、line2(2つ目の線分情報)、returnPosition(交差座標[参照型])
返り値	：衝突判定(True→当たっている)
===============================================================*/
bool Collider::Intersect(const LineSegment& line1,
						 const LineSegment& line2,
						 DirectX::SimpleMath::Vector2& returnPosition)
{
	//仮保存用変数の宣言
	float s, t, deno;
	

	deno = Cross(line1.mEnd - line1.mStart, line2.mEnd - line2.mStart);


	// 線分が平行なら衝突していない
	if (deno == 0.0) 
	{
		return false;
	}


	s = Cross(line2.mStart - line1.mStart, line2.mEnd - line2.mStart) / deno;
	t = Cross(line1.mEnd - line1.mStart, line1.mStart - line2.mStart) / deno;

	returnPosition = DirectX::SimpleMath::Vector2(line1.mStart.x + s * (line1.mEnd - line1.mStart).x,
							line1.mStart.y + s * (line1.mEnd - line1.mStart).y);


	// 線分が交差していない
	if (s < 0.f || 1.f < s || t < 0.f || 1.f < t) 
	{		
		return false;
	}


	//交差している
	return true;
}



/*===============================================================
ドット積を求める処理:private
引数	：vel1(１つ目のベクトル)、vel2(２つ目のベクトル)
返り値	：長さの平方
===============================================================*/
float Collider::Dot(const DirectX::SimpleMath::Vector3& vel1, const DirectX::SimpleMath::Vector3& vel2)
{
	float velX=vel1.x* vel2.x;
	float velY=vel1.y* vel2.y;
	float velZ=vel1.z* vel2.z;

	return velX + velY + velZ;
}

/*==========================================
平方根を求める処理:private
引数	：平方根を求めたい数
返り値	：引数の平方根
==========================================*/
float Collider::Sqrt(const float& num)
{
	float y, z, result;

	if (num == 0)
		return 0.0f;
	else
	{
		y = 1;

		for (int i = 0; i <= 10; i++)
		{
			z = num / y;
			result = (y + z) / 2;
			y = result;
		}
		return result;
	}
}

/*==========================================
外積を求める処理:private
引数	：2点の座標
返り値	：外積値
==========================================*/
float Collider::Cross(const DirectX::SimpleMath::Vector2& a, const DirectX::SimpleMath::Vector2& b)
{
	float cross = a.x * b.y - a.y * b.x;

	return cross;
}