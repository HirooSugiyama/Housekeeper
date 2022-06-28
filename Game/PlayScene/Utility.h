/*
�ėp�������܂Ƃ߂��w�b�_�[�t�@�C��
�쐬�ҁF���R
�쐬���F2021/08/31
*/
#pragma once

//3D����2D���W�Ŏg�p�����X,Z���g�p���邽�߂̕ϊ��p�\����
struct Vector2XZ
{
	float x;
	float z;

};


struct Utility
{
	//�����t�H���g�T�C�Y
	//��
	static const float STRING_SIZE_LARGE;
	//��
	static const float STRING_SIZE_MEDIUM;
	//��
	static const float STRING_SIZE_SMALL;
	//�ɏ�
	static const float STRING_SIZE_MINIMUM;

	//�����o�b�t�@�[�T�C�Y
	static const size_t BUFFER_SIZE;
	

	//��O����
	static const int EXCEPTION_NUM;

	//�g�嗦�𔼕��ɂ���
	static const int SCALE_HALF;

	//���p
	static const float RIGHT_ANGLE;

	//�ŏI�N���A�X�e�[�W�ۑ��p�t�@�C���p�X
	static const wchar_t* NEXT_STAGE_NUM_FILEPATH;

	//�X�v���C�g�摜�ړ�
	static const int SHIFT_SPRITE_TEXTURE;

	//�t�B�[���h�͈�
	static const float FIELD_MAX_SIZE_X;
	static const float FIELD_MIN_SIZE_X;
	static const float FIELD_MAX_SIZE_Z;
	static const float FIELD_MIN_SIZE_Z;

	//������`�悷��֐�
	static void DrawString
	(
		const int& drawNum= EXCEPTION_NUM,
		const DirectX::SimpleMath::Vector2& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		const DirectX::FXMVECTOR& stringColor= DirectX::Colors::White,
		const float& stringSize= STRING_SIZE_LARGE,
		const int& secondNum=EXCEPTION_NUM
	);
	static void DrawString
	(
		wchar_t const* string=L"none",
		const DirectX::SimpleMath::Vector2& stringPosition = DirectX::SimpleMath::Vector2::Zero,
		const DirectX::FXMVECTOR& stringColor= DirectX::Colors::White,
		const float& stringSize= STRING_SIZE_LARGE
	);


	//�t�@�C�����W�J�G���[
	static void FileError(const std::string& filePath);
	static void FileError(const wchar_t* filePath);

};
