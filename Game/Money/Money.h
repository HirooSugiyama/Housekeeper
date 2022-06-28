/*
�������Ǘ��t�@�C��
�쐬�ҁF���R
�쐬���F2021/10/21
*/
#pragma once



class Money final
{
private:

	////���g
	static std::unique_ptr<Money> sMoney;

	//�R�s�[�R���X�g���N�^�A�R�s�[������Z�q��delete�B
	Money(const Money& money) = delete;
	Money operator=(const  Money& money) = delete;

	//�t�@�C����
	std::string mFilepath;
	//�������z
	int mPossessionMoney;

	//�R���X�g���N�^
	Money();

public:

	//���g�̃C���X�^���X
	static Money& GetMoneyInstance();

	//�t�@�C�����̐ݒ�
	void LoadFileSet(std::string filepath);

	//���z������������
	void ReduceMoney(const int& moneynum) { mPossessionMoney -= moneynum; }
	//���z�̏㏑��
	void SetMoney(const int& moneynum) { mPossessionMoney = moneynum; }

	//���z���擾
	int GetMoney()const { return mPossessionMoney; }
private:

	//���z�̏�����
	void MoneyInit();

};
