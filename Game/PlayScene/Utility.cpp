/*
�ėp�������܂Ƃ߂��t�@�C��
�쐬�ҁF���R
�쐬���F2021/08/31
*/
#include"pch.h"
#include"Utility.h"

//�����t�H���g�T�C�Y
//��
const float Utility::STRING_SIZE_LARGE = 3.f;
//��
const float Utility::STRING_SIZE_MEDIUM = 2.f;
//��
const float Utility::STRING_SIZE_SMALL = 1.5f;
//�ɏ�
const float Utility::STRING_SIZE_MINIMUM = 1.f;


//�����o�b�t�@�[�T�C�Y
const size_t Utility::BUFFER_SIZE = 32;


//��O����
const int Utility::EXCEPTION_NUM = -1;

//�g�嗦�𔼕��ɂ���
const int Utility::SCALE_HALF = 2;

//���p
const float Utility::RIGHT_ANGLE = 90.f;

//�ŏI�N���A�X�e�[�W�ۑ��p�t�@�C���p�X
const wchar_t* Utility::NEXT_STAGE_NUM_FILEPATH = L"SaveData/FinalClear.csv";

//�X�v���C�g�摜�ړ�
const int Utility::SHIFT_SPRITE_TEXTURE = 2;

//�t�B�[���h�͈�
const float Utility::FIELD_MAX_SIZE_X = 19.f;
const float Utility::FIELD_MIN_SIZE_X = -FIELD_MAX_SIZE_X;
const float Utility::FIELD_MAX_SIZE_Z = 11.f;
const float Utility::FIELD_MIN_SIZE_Z = -40.f;

/*==============================
�������`�悷�鋤�ʊ֐�
�����F�`�悷�鐔��
		���W
		�F
		�����T�C�Y
�Ԃ�l�F�Ȃ�
==============================*/
void Utility::DrawString(const int& drawNum,
						const DirectX::SimpleMath::Vector2& stringPosition,
						const DirectX::FXMVECTOR& stringColor,
						const float& stringSize,
						const int& secondNum)
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	wchar_t buf[32];

	swprintf_s(buf, Utility::BUFFER_SIZE, L" %d", drawNum);
	if (secondNum != EXCEPTION_NUM)
	{
		swprintf_s(buf, Utility::BUFFER_SIZE, L" %d:%d", drawNum, secondNum);
	}

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		buf,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero, 
		stringSize
	);
}

/*==============================
�������`�悷�鋤�ʊ֐�
�����F�`�悷�镶����
		���W
		�F
		�����T�C�Y
�Ԃ�l�F�Ȃ�
==============================*/
void Utility::DrawString(wchar_t const* string,
	const DirectX::SimpleMath::Vector2& stringPosition,
	const DirectX::FXMVECTOR& stringColor,
	const float& stringSize)
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();

	pDxIF.GetSpriteFont()->DrawString
	(
		pDxIF.GetSpriteBatch(),
		string,
		stringPosition,
		stringColor,
		0,
		DirectX::SimpleMath::Vector2::Zero,
		stringSize
	);
}


/*==============================
�t�@�C�����W�J�G���[
�����F�t�@�C���p�X
�Ԃ�l�F�Ȃ�
==============================*/
void Utility::FileError(const std::string& filePath)
{
	//�t�@�C���ϊ�
	std::ifstream ifs(filePath);
	//���ۑ��p�ϐ�
	std::string lineBuf;

	//�����o��
	std::getline(ifs, lineBuf);

	//���g�������Ă���ꍇ�͔�����
	if (lineBuf != "")
	{
		return;
	}
	else
	{
		throw "Unable to extract file";
	}
}

void Utility::FileError(const wchar_t* filePath)
{
	//�t�@�C���ϊ�
	std::ifstream ifs(filePath);
	//���ۑ��p�ϐ�
	std::string lineBuf;

	//�����o��
	std::getline(ifs, lineBuf);

	//���g�������Ă���ꍇ�͔�����
	if (lineBuf != "")
	{
		return;
	}
	else
	{
		throw "Unable to extract file";
	}
}
