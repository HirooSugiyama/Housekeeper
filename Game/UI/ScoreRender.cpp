/*
�X�R�A����̕`��N���X
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#include"pch.h"

#include"ScoreRender.h"

//�X�R�A�̕`��ʒu
const DirectX::SimpleMath::Vector2 ScoreRender::SCORE_NUM_POSITION(270.f, 0.f);

//�X�R�A�̕����摜�̕`��ʒu
const DirectX::SimpleMath::Vector2 ScoreRender::SCORE_STRING_POSITION(20.f, 10.f);

//�X�R�A�̊g�嗦
const float ScoreRender::SCORE_NUM_SCALE = 1.5f;

//�X�R�A�����̊g�嗦
const float ScoreRender::SCORE_STRING_SCALE = 1.5f;

/*===================================
�R���X�g���N�^
�����F�Ȃ�
===================================*/
ScoreRender::ScoreRender()
	: 
	mpDrawScore(),
	mpScoreStringTexture()
{
	mpDrawScore = std::make_unique<SpriteNumber2D>();
	mpScoreStringTexture = std::make_unique<ObjectTexture>();
}

/*===================================
�f�X�g���N�^
===================================*/
ScoreRender::~ScoreRender()
{
}

/*===================================
����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void ScoreRender::Initialize()
{
	//�X�R�A�̃t�H���g���w��
	mpDrawScore->SetTextureKey(static_cast<int>(PlayTexturesResouce::TEXTURE__NEWNORMALSTRING));
	mpDrawScore->Initialize();
	mpDrawScore->SetAlign(eAlign::LEFT);
	mpDrawScore->SetScale(SCORE_NUM_SCALE);

	//���\�[�X�̎擾
	ResourceManager* pRM = ResourceManager::GetInstance();
	auto texture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SCORE));

	//�X�R�A�����̏���������
	mpScoreStringTexture->SetTexture(texture);
	mpScoreStringTexture->Initialize();
	mpScoreStringTexture->SetPosition(SCORE_STRING_POSITION);
	mpScoreStringTexture->SetScale(DirectX::SimpleMath::Vector2(SCORE_STRING_SCALE, SCORE_STRING_SCALE));
}

/*===================================
�`�揈��
�����F�X�R�A�l
�Ԃ�l�F�Ȃ�
===================================*/
void ScoreRender::Draw(int scoreNum)
{
	//�X�R�A�̕`��
	mpScoreStringTexture->Draw();

	mpDrawScore->Create(scoreNum, SCORE_NUM_POSITION);
	mpDrawScore->Draw();
}
