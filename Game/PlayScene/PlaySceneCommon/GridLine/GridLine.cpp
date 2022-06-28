/*
�ǂ�u������p���C���̃N���X
�쐬�ҁF���R
�쐬���F2021/08/28
*/

#include"pch.h"
#include "GridLine.h"



//���C���̍��W
//X���W(�Ֆʒ��S���W)
const float GridLine::LINE_MODEL_CENTER_POSITION_X = 0.f;
//Y���W(����)
const float GridLine::LINE_MODEL_POSITION_Y = 0.75f;
//Z���W(�Ֆʒ��S���W)
const float GridLine::LINE_MODEL_CENTER_POSITION_Z = -15.f;


//���C�����f���̊g�嗦
//���ʊg�嗦
const float GridLine::LINE_MODEL_SCALE_Y = 3.f;
//�c��
const DirectX::SimpleMath::Vector3 GridLine::VERTICAL_LINE_MODEL_SCALE(0.02f, LINE_MODEL_SCALE_Y, 25.f);
//����
const DirectX::SimpleMath::Vector3 GridLine::HORIZONTAL_LINE_MODEL_SCALE(20.f, LINE_MODEL_SCALE_Y, 0.02f);


/*====================
�R���X�g���N�^
�����F�Ȃ�
=======================*/
GridLine::GridLine()
	:
	mpLineModel(nullptr),
	mpLineCollider(nullptr)
{
	mpLineModel = std::make_unique<ObjectModel>();
	mpLineCollider = std::make_unique<LineSegment>();
}



/*====================
�f�X�g���N�^
=======================*/
GridLine::~GridLine()
{
}

/*====================
����������
�����F���̃^�C�v
�Ԃ�l�F�Ȃ�
=======================*/
void GridLine::Initialize(const eGridLineType& lineType)
{
	//���\�[�X�}�l�[�W���̏���
	auto pRM = ResourceManager::GetInstance();
	auto model = pRM->GetCmoModel(static_cast<int>(PlayModelsResouce::MODEL__PIXELMODEL));
	mpLineModel->SetModel(model);


	//���̎�ނɉ����ď������s��
	switch (lineType)
	{
		case eGridLineType::VERTICAL:
		{
			//�g�嗦��ݒ肷��
			mpLineModel->SetScale(VERTICAL_LINE_MODEL_SCALE);
			break;
		}
		case eGridLineType::HORIZONTAL:
		{
			//�g�嗦��ݒ肷��
			mpLineModel->SetScale(HORIZONTAL_LINE_MODEL_SCALE);
			break;
		}
	}
}

/*====================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=======================*/
void GridLine::Draw()
{
	//�`�悷��
	mpLineModel->Draw();
}

/*===============================
��ނɍ��킹�����W�ݒ菈��
�����F����p���C���̎�ށA���W
�Ԃ�l�F�Ȃ�
================================*/
void GridLine::SetLineModelPosition(const eGridLineType& lineType, const float& position)
{
	//���̎�ނɉ����č��W�ݒ菈�����s��
	switch (lineType)
	{
		case eGridLineType::VERTICAL:
		{
			this->SetModelPositionX(position);
			break;
		}
		case eGridLineType::HORIZONTAL:
		{
			this->SetModelPositionZ(position);
			break;
		}
	}

	//���W�����Ƃɓ����蔻���ݒ肷��
	this->ColliderSet();
}

/*================================
�����蔻���ݒ肷��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
================================*/
void GridLine::ColliderSet()
{
	//�ȗ����p�ϐ��̐錾
	DirectX::SimpleMath::Vector3 modelPosition(DirectX::SimpleMath::Vector3::Zero), modelscale(DirectX::SimpleMath::Vector3::Zero);

	//����p�ϐ��̐錾
	DirectX::SimpleMath::Vector2 lineStart(DirectX::SimpleMath::Vector2::Zero), lineEnd(DirectX::SimpleMath::Vector2::Zero);

	//���W���ȗ���
	modelPosition = mpLineModel->GetPosition();
	//�g�嗦���ȗ���
	modelscale = mpLineModel->GetScale();

	//���W�����ƂɎn�_�����߂�
	lineStart.x = modelPosition.x - modelscale.x;
	lineStart.y = modelPosition.z - modelscale.z;

	//���W�����ƂɏI�_�����߂�
	lineEnd.x = modelPosition.x + modelscale.x;
	lineEnd.y = modelPosition.z + modelscale.z;


	mpLineCollider->mStart = lineStart;
	mpLineCollider->mEnd = lineEnd;
}

/*================================
�c���̍��W�ݒ菈��:private
�����F���f����X���W
�Ԃ�l�F�Ȃ�
================================*/
void GridLine::SetModelPositionX(const float& positionX)
{
	//����p�ϐ��̏���
	DirectX::SimpleMath::Vector3 modelPosition = DirectX::SimpleMath::Vector3::Zero;
	modelPosition.x = positionX;
	modelPosition.y = LINE_MODEL_POSITION_Y;
	modelPosition.z = LINE_MODEL_CENTER_POSITION_Z;

	//���W��ݒ肷��
	mpLineModel->SetPosition(modelPosition);
}

/*=================================
�����̍��W�ݒ菈��:private
�����F���f����Z���W
�Ԃ�l�F�Ȃ�
================================*/
void GridLine::SetModelPositionZ(const float& positionZ)
{
	//����p�ϐ��̏���
	DirectX::SimpleMath::Vector3 modelPosition = DirectX::SimpleMath::Vector3::Zero;
	modelPosition.x = LINE_MODEL_CENTER_POSITION_X;
	modelPosition.y = LINE_MODEL_POSITION_Y;
	modelPosition.z = positionZ;

	mpLineModel->SetPosition(modelPosition);
}
