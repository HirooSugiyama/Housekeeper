/*
���ʃ|���S���`����N���X
�쐬�ҁF���R
�쐬���F2021/11/13
*/
#pragma once





class FlatPolygonBase
{
protected:


	//�R���X�g���N�^
	FlatPolygonBase() = default;
	//�f�X�g���N�^
	virtual ~FlatPolygonBase() = default;

public:

	//������
	virtual void Initialize() = 0;

	//�`��
	virtual void Draw(const DirectX::SimpleMath::Vector3& position) = 0;

	//�g�嗦�̃A�N�Z�T
	virtual void SetScale(const DirectX::SimpleMath::Vector2& scale) = 0;


};
