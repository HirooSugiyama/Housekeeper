/*
�J�E���g�_�E���t�F�[�Y
�쐬�ҁF���R
�쐬���F2021/09/30
*/

#include"pch.h"

#include"PScenePhaseResult.h"

//������
#include"../PlayScene.h"

//�֐������̎g�p
#include"Game/Money/Money.h"
#include"../PlaySceneCommon/Administrator/Administrator.h"
#include"../PlaySceneCommon/Administrator/Score.h"
#include"../PlaySceneCommon/Enemy/EnemyManager.h"

#include"Game/StageSelect/StageNumer.h"


//Master�Ńt���O
#include"Game/Master.h"

//�኱�̃C���^�[�o��
const int PScenePhaseResult::SLIGHTLY_INTERVAL = 2;

//������������
const int PScenePhaseResult::NUM_MOVE_TIME = 1;

//�X�R�A�{�[�i�X�W��
//������
const int PScenePhaseResult::MONEY_CAST_BONUS = 10;
//���j��
const int PScenePhaseResult::DEFFEAT_CAST_BONUS = 10;


//���U���g�摜�ړ����x
const int PScenePhaseResult::TEXTURE_MOVE_VELOCITY = 30;


//���ʉ摜�̊g�嗦
const DirectX::SimpleMath::Vector2 PScenePhaseResult::COMMONTEXTURE_SCALE = DirectX::SimpleMath::Vector2(0.95f, 0.9f);
const DirectX::SimpleMath::Vector2 PScenePhaseResult::COMMONTEXTURE_POSITION = DirectX::SimpleMath::Vector2(-1280.f, 0.f);

/*=====================
�R���X�g���N�^
�����F�Ȃ�
=====================*/
PScenePhaseResult::PScenePhaseResult()
	:
	mpPlayScene(nullptr),
	mpDrawString{},
	mpCommonTexture(),
	mScoreNum(),
	mpScoreMoveNum(nullptr),
	mMoneyNum(),
	mpMoneyMoveNum(nullptr),
	mDeffeatBonusNum(),
	mpDeffeatBonusMoveNum(nullptr),
	mClearBonusNum(),
	mpClearBonusMoveNum(nullptr),
	mScoreRankingNum{},
	mpRanking{nullptr},
	mpResultInfo(nullptr),
	mNumState(eMoveNumState::NONE),
	mpTimer(nullptr)
{
	for (int i = 0; i < static_cast<int>(eResultDrawString::NUM); i++)
	{
		mpDrawString[i] = std::make_unique<MoveString>();
	}


	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mpRanking[i] = std::make_unique<MoveSpriteNumber2D>();
	}


	mpScoreMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpMoneyMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpDeffeatBonusMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpClearBonusMoveNum = std::make_unique<MoveSpriteNumber2D>();
	mpTimer = std::make_unique<Timer>();
	mpResultInfo = std::make_unique<ResultInfo>();
	mpCommonTexture = std::make_unique<ObjectTexture>();
}

/*====================
�f�X�g���N�^
=====================*/
PScenePhaseResult::~PScenePhaseResult()
{
}

/*===============================
����������
�����F�v���C�V�[���̃|�C���^
�Ԃ�l�F�Ȃ�
===============================*/
void PScenePhaseResult::Initialize(PlayScene* pPlayScene)
{
	//�|�C���^�̕ۑ�
	mpPlayScene = pPlayScene;

	//������Ƃ������Ԃ�u�������̏���������
	mpTimer->SetMaxTime(SLIGHTLY_INTERVAL);

	mpResultInfo->Initialize(mpPlayScene->GetStageNum());

	//�N���A���̃{�[�i�X�X�R�A��ۑ�
	mClearBonusNum = PlayScenePhaseBase::GetAdministrator()->GetClearBonusScoreNum();

	//�摜�擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__RESULT));

	mpCommonTexture->SetTexture(texture);
	mpCommonTexture->Initialize();
	mpCommonTexture->SetScale(COMMONTEXTURE_SCALE);
	mpCommonTexture->SetPosition(COMMONTEXTURE_POSITION);

}

/*====================
���Z�b�g����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=====================*/
void PScenePhaseResult::Reset()
{
	//�l�ݒ菈��
	this->Configuration();
}

/*====================
�X�V����
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=====================*/
void PScenePhaseResult::Update()
{
	//�^�C�}�[�̎擾
	const auto& pT = TimerComponent::GetTimerInstance();
	DX::StepTimer time = pT.GetTimer();

	switch (mNumState)
	{
		case eMoveNumState::NONE:
		{
			//�����Ԃ�u��
			bool flag = mpTimer->Update();

			//���ԂɂȂ����玟�̏�����
			if (flag)
			{
				//�^�C�}�[�����ɔ����ă��Z�b�g���Ă���
				mpTimer->ResetMainTimer();

				mNumState = eMoveNumState::STRING_MOVE;
			}

			break;
		}
		case eMoveNumState::STRING_MOVE:
		{
			bool flag = this->MoveTexture();

			if (flag)
			{
				//�����Ԃ�u��
				flag = mpTimer->Update();

				//���ԂɂȂ����玟�̏�����
				if (flag)
				{
					//�^�C�}�[�����ɔ����ă��Z�b�g���Ă���
					mpTimer->ResetMainTimer();

					mNumState = eMoveNumState::BONUS_UP;
				}
			}
			break;
		}
		case eMoveNumState::BONUS_UP:
		{
			//���������̍X�V����
			int moneyNum = mpMoneyMoveNum->Update(time);
			int deffeatNum = mpDeffeatBonusMoveNum->Update(time);
			int clearnum = mpClearBonusMoveNum->Update(time);
			//�ő�l�ɂȂ����玟�̏�����
			if (moneyNum == mMoneyNum &&
				deffeatNum == mDeffeatBonusNum &&
				clearnum == mClearBonusNum)
			{
				//�����Ԃ�u��
				bool flag = mpTimer->Update();

				//���ԂɂȂ����玟�̏�����
				if (flag)
				{
					//�^�C�}�[�����ɔ����ă��Z�b�g���Ă���
					mpTimer->ResetMainTimer();


					mNumState = eMoveNumState::SCORE_UP;
				}
			}

			break;
		}
		case eMoveNumState::SCORE_UP:
		{
			//���������̍X�V����
			int num = mpScoreMoveNum->Update(time);
			//�ő�l�ɂȂ����玟�̏�����
			if (num == mScoreNum)
			{
				//�����Ԃ�u��
				bool flag = mpTimer->Update();

				//���ԂɂȂ����玟�̏�����
				if (flag)
				{
					//�^�C�}�[�����ɔ����ă��Z�b�g���Ă���
					mpTimer->ResetMainTimer();


					mNumState = eMoveNumState::SCORE_BLINKING;
				}
			}

			break;
		}
		case eMoveNumState::SCORE_BLINKING:
		{
			bool flag = false;
			for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
			{
				int num = mpRanking[i]->Update(time);

				if (num != mScoreRankingNum[i] && !flag)
				{
					flag = true;
				}
			}
			if (!flag)
			{
				//��Ԃ��ŏI��
				mNumState = eMoveNumState::PUSH_ENTER;
			}
			break;
		}
		case eMoveNumState::PUSH_ENTER:
		{
			break;
		}
	}
	//���U���g�I������
	this->ForcedTermination();

}

/*=================================
�`�揈��
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void PScenePhaseResult::Draw()
{	
	//���ډ摜�̕`�揈��
	mpCommonTexture->Draw();

	//�l�̕`��
	this->NumDraw();
}

/*================================
�l�̊e��ݒ�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseResult::Configuration()
{

	//�ŏI�X�R�A���Z�o����
	this->CalculationScore();

	//�X�R�A�����L���O�ɒl��ݒ肷��
	mpResultInfo->SetScoreRanking(mScoreNum);

	int textureKey = static_cast<int>(PlayTexturesResouce::TEXTURE__NEWMONEYSTRING);

	//���������̏���������
	mpScoreMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mScoreNum);
	mpScoreMoveNum->SetScale(Utility::STRING_SIZE_MEDIUM);
	mpScoreMoveNum->SetAlign(eAlign::LEFT);

	mpMoneyMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mMoneyNum);
	mpMoneyMoveNum->SetScale(Utility::STRING_SIZE_MINIMUM);
	mpMoneyMoveNum->SetAlign(eAlign::LEFT);

	mpDeffeatBonusMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mDeffeatBonusNum);
	mpDeffeatBonusMoveNum->SetScale(Utility::STRING_SIZE_MINIMUM);
	mpDeffeatBonusMoveNum->SetAlign(eAlign::LEFT);

	mpClearBonusMoveNum->Initialize(textureKey, 0, NUM_MOVE_TIME, mClearBonusNum);
	mpClearBonusMoveNum->SetScale(Utility::STRING_SIZE_MINIMUM);
	mpClearBonusMoveNum->SetAlign(eAlign::LEFT);


	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mScoreRankingNum[i] = mpResultInfo->GetScoreRanking(i);
		mpRanking[i]->Initialize(textureKey, 0, NUM_MOVE_TIME, mScoreRankingNum[i]);
		mpRanking[i]->SetScale(Utility::STRING_SIZE_MINIMUM);
		mpRanking[i]->SetAlign(eAlign::LEFT);
	}
	//1�Ԃ̂݃T�C�Y�ύX
	mpRanking[0]->SetScale(Utility::STRING_SIZE_MEDIUM);

}

/*=================================
�e��l�̕`�揈��:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseResult::NumDraw()
{

	if (static_cast<int>(mNumState) < static_cast<int>(eMoveNumState::BONUS_UP))
	{
		return;
	}

	//�N���A�{�[�i�X�l�̕`��
	mpClearBonusMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_CLEARBONUS_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT
	);
	mpClearBonusMoveNum->Draw();

	//�c���̕`��
	mpMoneyMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_MONEYBONUS_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT		
	);
	mpMoneyMoveNum->Draw();

	//���j���{�[�i�X�l�̕`��
	mpDeffeatBonusMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_DEFEATBONUS_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT	
	);
	mpDeffeatBonusMoveNum->Draw();


	if (static_cast<int>(mNumState) < static_cast<int>(eMoveNumState::SCORE_UP))
	{
		return;
	}

	//�݌v�X�R�A�l�̕`��
	mpScoreMoveNum->SetPosition
	(
		ResultDrawStringConstant::STRING_SCORE_POSITION +
		ResultDrawStringConstant::STRING_NUM_SHIFT
	);
	mpScoreMoveNum->Draw();

	//�X�R�A�����L���O�̕`��
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mpRanking[i]->SetPosition
		(
			ResultDrawStringConstant::SCORE_RANKING_NUM_POSITION +
			DirectX::SimpleMath::Vector2(0.f, i * ResultDrawStringConstant::SCORE_RANKING_SHIFT)
		);
		mpRanking[i]->Draw();
	}
}

/*=================================
�X�R�A���Z�o����:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseResult::CalculationScore()
{
	//���݂̃X�R�A���擾
	int score= PlayScenePhaseBase::GetAdministrator()->DirectAcceserScore()->GetScoreNum();

	mDeffeatBonusNum = PlayScenePhaseBase::GetEnemyManager()->GetBreakEnemyNum();
	//���j���ɌW����������
	int deffeatScore = mDeffeatBonusNum * DEFFEAT_CAST_BONUS;

	//���݂̏������̎擾
	auto& pM = Money::GetMoneyInstance();
	mMoneyNum = pM.GetMoney();
	//�c���ɌW����������
	int moneyScore = mMoneyNum * MONEY_CAST_BONUS;

	//�S�đ���
	mScoreNum = score + deffeatScore + moneyScore + mClearBonusNum;
}

/*=================================
�l�������ړ�������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseResult::ForcedChange()
{
	//�l�������ړ�
	mpClearBonusMoveNum->ForcedChangeMoveNum();
	mpMoneyMoveNum->ForcedChangeMoveNum();
	mpDeffeatBonusMoveNum->ForcedChangeMoveNum();
	mpScoreMoveNum->ForcedChangeMoveNum();

	//�����Q�̈ʒu�������ړ�
	for (int i = 0; i < static_cast<int>(eResultDrawString::NUM); i++)
	{
		mpDrawString[i]->ForcedChangeString();
	}
	for (int i = 0; i < ResultDrawStringConstant::SCORE_RANKING_STORAGE; i++)
	{
		mScoreRankingNum[i] = mpResultInfo->GetScoreRanking(i);
		mpRanking[i]->ForcedChangeMoveNum();
	}

	//�摜�������ړ�
	mpCommonTexture->SetPosition(DirectX::SimpleMath::Vector2::Zero);
}

/*=================================
�摜�ړ�����:private
�����F�Ȃ�
�Ԃ�l�F�I���t���O
=================================*/
bool PScenePhaseResult::MoveTexture()
{
	mpCommonTexture->SetPosition(mpCommonTexture->GetPosition()+ DirectX::SimpleMath::Vector2(TEXTURE_MOVE_VELOCITY,0.f));

	//�����w��ʒu�ɗ�����
	if (mpCommonTexture->GetPosition().x >= 0)
	{
		mpCommonTexture->SetPosition(DirectX::SimpleMath::Vector2::Zero);
		return true;
	}
	return false;
}

/*=================================
�����I������:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
=================================*/
void PScenePhaseResult::ForcedTermination()
{
	// �L�[���͏����擾����
	KeyTracker* pKey = KeyTracker::GetKeyTrackerInstance();
	GamePadTracker* pGamePad = GamePadTracker::GetGamePadTrackerInstance();

	if (pKey->Decision() || pGamePad->Decision())	//����
	{

		if (mNumState != eMoveNumState::PUSH_ENTER)
		{
			//�`��������ړ�����
			this->ForcedChange();

			//��Ԃ��ŏI��
			mNumState = eMoveNumState::PUSH_ENTER;
		}
		else
		{
			//�X�e�[�W�ԍ��ۑ�
			this->SaveNextStageNum();
			mpResultInfo->WriteScore();

			//�����t���O�����Ă�
			mpPlayScene->SetClearFlag(true);
		}
	}
}

/*===================================================
�Ō�ɃN���A�����X�e�[�W�ԍ��̕ۑ�:private
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================================*/
void PScenePhaseResult::SaveNextStageNum()
{
	//�t�@�C�����J��
	std::ofstream writingFile;
	writingFile.open(Utility::NEXT_STAGE_NUM_FILEPATH, std::ios::out);

	//�ԍ���ۑ�
	if (mpPlayScene->GetStageNum() + 1 < static_cast<int>(eSelectNum::NUM))
	{
		writingFile << mpPlayScene->GetStageNum() + 1 << std::endl;
	}
	else
	{
		writingFile << mpPlayScene->GetStageNum() << std::endl;
	}

	writingFile.close();
}