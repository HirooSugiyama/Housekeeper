/*
�����������\�����s���N���X�̊��N���X
�쐬�ҁF���R
�쐬���F2021/10/22
*/

#pragma once


class NumberBase
{
private:

	//�����x�����l
	static const float INIT_ALPHA;
	//�����̐��̍ő吔
	static const int MAX_NUMTYPE_NUM;


	//�����x�Ǘ��ϐ�
	float mTextureAlpha;

	//�摜�L�[
	int mTextureKey;


protected:
	//�R���X�g���N�^
	NumberBase();

	//�f�X�g���N�^
	virtual ~NumberBase();

public:

	//�X�V����
	virtual void Update() {}

	//�`�揈��
	virtual void Draw() = 0;

	//�摜�L�[�̃A�N�Z�T
	void SetTextureKey(int key) { mTextureKey = key; }
	int GetTextureKey()const { return mTextureKey; }


protected:

	//�擾������������K�v�Ȑ�����I�яo��
	std::vector<int> ChooseNum(int num);

	//�A�N�Z�T
	//�����x�Ǘ��ϐ�
	float GetTextureAlpha() const { return mTextureAlpha; }
	void SetTextureAlpha(float alpha) { mTextureAlpha = alpha; }

	float GetInitAlpha()const { return INIT_ALPHA; }
	int GetMaxNumTypeNum()const { return MAX_NUMTYPE_NUM; }

};
