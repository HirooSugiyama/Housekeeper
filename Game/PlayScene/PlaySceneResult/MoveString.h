/*
�w�肵���ꏊ�Ɉړ����镶��
�쐬�ҁF���R
�쐬���F2021/10/13
*/
#pragma once




class MoveString
{
private:

	//���C 
	static const float FRICTION_FORCE;

	//���C��������͈�
	static const float FRICTION_RANGE;

	//���݂̈ʒu
	DirectX::SimpleMath::Vector2 mPosition;

	//�ŏI�ʒu
	DirectX::SimpleMath::Vector2 mFinishPosition;

	//�ړ����x
	float mMoveVelocityNum;

	//�`�悷�镶��
	const wchar_t* mpDrawString;

	//�����T�C�Y
	float mStringSize;

	//�E������o�Ă���t���O
	bool mRightFlag;

public:

	//�R���X�g���N�^
	MoveString();
	//�f�X�g���N�^
	~MoveString();
	//����������
	void Initialize(const DirectX::SimpleMath::Vector2& firstpos,	//�ŏ��̍��W
		const DirectX::SimpleMath::Vector2& finishpos,				//�ŏI�I�ȍ��W
		const float& velnum,										//�ړ����x
		const wchar_t* drawString,									//�`�悷�镶��
		const float& stringSize = 1.f								//�����T�C�Y
		);
	//�X�V����
	bool Update();
	//�`�揈��
	void Draw();

	//�w��̈ʒu�ɋ����ړ�
	void ForcedChangeString() { mPosition = mFinishPosition; }

private:

	//�����̈ړ�
	void StringMove();

};
