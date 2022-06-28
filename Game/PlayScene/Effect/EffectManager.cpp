/*
�G�t�F�N�g�}�l�[�W���[
�쐬�ҁF���R
�쐬���F2021/09/19
*/

#include"pch.h"
#include"EffectManager.h"
#include"Libraries/DirectXTK/Inc/Effects.h"
#include"DeviceResources.h"

//�֐��̎g�p
#include"Libraries/MyLibraries/Camera.h"
#include"Effect.h"

//���ޓ�����̃G�t�F�N�g�̐�
const int EffectManager::EFFECT_NUM = 70;

/*=========================================
�R���X�g���N�^
�����F�Ȃ�
=========================================*/
EffectManager::EffectManager()
	:mpEffectDB{}
	, mpCamera(nullptr)
{
}

/*=========================================
�f�X�g���N�^
=========================================*/
EffectManager::~EffectManager()
{
	//�S�Ẵ��\�[�X����j��
	this->DeleteAllData();
}

/*=========================================
������
�����F�t�@�C���̃p�X
�Ԃ�l�F�Ȃ�
=========================================*/
void EffectManager::Initialize(const wchar_t* filepath)
{
	setlocale(LC_CTYPE, "");


	//�Ƃ肠�����������Y��h�~�̏�����
	this->DeleteAllData();

	//�t�@�C���ǂݍ���
	this->LoadCSV(filepath);
}

/*=======================================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void EffectManager::Update()
{
	for (int key = 1; key < static_cast<int>(eEffectType::NUM); key++)
	{
		//�g�p���łȂ��Ȃ�ʂ��Ȃ�
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			if (mpEffectDB[static_cast<eEffectType>(key)][i]->GetSpriteFlag() == false)
			{
				continue;
			}

			mpEffectDB[static_cast<eEffectType>(key)][i]->Update();
		}
	}	
}

/*========================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void EffectManager::Draw()
{
	for (int key = 1; key < static_cast<int>(eEffectType::NUM); key++)
	{
		//�g�p���łȂ��Ȃ�ʂ��Ȃ�
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			if (mpEffectDB[static_cast<eEffectType>(key)][i]->GetSpriteFlag() == false)
			{
				continue;
			}

			//�J�����̈ʒu���擾
			mpEffectDB[static_cast<eEffectType>(key)][i]->
				SetCameraEyePosition(mpCamera->GetEyePosition());

			mpEffectDB[static_cast<eEffectType>(key)][i]->ExtendDraw();
		}
	}
}

/*=========================================
�I������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void EffectManager::Finalize()
{
	//��U�Ō�Ȃ̂ł��ׂď�����
	this->DeleteAllData();
}

/*=========================================
�G�t�F�N�g�̎擾
�����F�G�t�F�N�g�̎��ʖ�
�Ԃ�l�F�g�p�\��̃G�t�F�N�g�̃|�C���^
=========================================*/
EffectSpriteTexture* EffectManager::GetEffect(const eEffectType& key)
{
	//�g�p���łȂ�ʂ��Ȃ�
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		if (mpEffectDB[key][i]->GetSpriteFlag() == true)
		{
			continue;
		}
		return mpEffectDB[key][i].get();
	}

	return nullptr;
}

/*=========================================================
�S�G�t�F�N�g�̉ғ��t���O
�����F�Ȃ�
�Ԃ�l�F�ғ��t���O(true�c�g�p���̃G�t�F�N�g����)
==========================================================*/
bool EffectManager::ChackAllEffect()
{
	for (int key = 1; key < static_cast<int>(eEffectType::NUM); key++)
	{
		//�g�p���łȂ��Ȃ�ʂ��Ȃ�
		for (int i = 0; i < EFFECT_NUM; i++)
		{
			if (mpEffectDB[static_cast<eEffectType>(key)][i]->GetSpriteFlag())
			{
				return true;
			}
		}
	}

	return false;
}

/*========================
�t�@�C���ǂݍ��ݏ���
�����F�t�@�C���̃p�X
�Ԃ�l�F�Ȃ�
=========================*/
void EffectManager::LoadCSV(const wchar_t* filepath)
{
	//��O����
	Utility::FileError(filepath);

	//�t�@�C�����擾
	std::ifstream ifs(filepath);
	//1�s�̏���ۑ�����ϐ�
	std::string lineBuf;

	//1�s�̓ǂݍ��ݏ���_
	for (int i = 0; std::getline(ifs, lineBuf); i++)
	{
		//1�s�̏���stream�ɂ���
		std::stringstream lineStream(lineBuf);
		//1�}�X�̏��ۑ��p
		std::string tileBuf;

		//�ۑ��p�ϐ�
		EffectSpriteTexture texture;
		std::string filename = "none";			//�t�@�C����
		wchar_t* wcs = L"none";					//�ϊ��p�ϐ�
		const wchar_t* texturename = L"none";	//�e�N�X�`���̑��΃p�X

		//�g�嗦�p�ϐ�
		DirectX::SimpleMath::Vector2 scale= DirectX::SimpleMath::Vector2::Zero;

		//1�}�X�̏��ǂݍ��ݏ���
		for (int j = 0; std::getline(lineStream, tileBuf, ','); j++)
		{
			//�t�@�C�����̕ۑ�
			if (j == static_cast<int>(eEffectFileReading::FILE_NAME))
			{
				std::string omission = "Resources/Textures/Play/Effect/";
				filename = omission + tileBuf;
				//�}���`�o�C�g���������C�h�����ɕϊ�
				wcs = new wchar_t[filename.length() + 1];
				size_t size;
				mbstowcs_s(&size,wcs, filename.length() + 1,filename.c_str(), filename.length() + 1);
				texturename = wcs;


				texture.SetFileName(texturename);
				texture.Initialize();
			}
			//�X�v���C�g�̃^�C�}�[�l��ۑ�
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_SPRITE_TIMER))
			{
				texture.SetConstTimer(atoi(tileBuf.c_str()));
			}
			//���������̕ۑ�
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_HORIZONTAL_SIZE))
			{
				texture.SetHorizontalCutNum(atoi(tileBuf.c_str()));
			}
			//�g�嗦�̕ۑ�
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_SCALE_X))
			{
				scale.x = static_cast<float>(atof(tileBuf.c_str()));
			}
			else if (j == static_cast<int>(eEffectFileReading::EFFECT_SCALE_Y))
			{
				scale.y = static_cast<float>(atof(tileBuf.c_str()));
				texture.SetScale(scale);
			}

		}

		//����ۑ�����
		mpEffectDB[static_cast<eEffectType>(i + 1)].resize(EFFECT_NUM);

		for (int j = 0; j<EFFECT_NUM; j++)
		{
			//����ۑ�����
			mpEffectDB[static_cast<eEffectType>(i + 1)][j] = std::make_unique<EffectSpriteTexture>();
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->Initialize();
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->SetTexture(texture.GetTexture());
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->SetConstTimer(texture.GetConstTimer());
			mpEffectDB[static_cast<eEffectType>(i + 1)][j]->
				SetHorizontalCutNum(texture.GetHorizontalCutNum());
		}		
		delete[] wcs;
	}
}

/*=========================================
�S�Ẵ��\�[�X�̍폜
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=========================================*/
void EffectManager::DeleteAllData()
{
	mpEffectDB.clear();	
}
