/*
�摜�Ǘ��N���X�̃C���^�[�t�F�[�X�N���X
�쐬�ҁF���R
�쐬���F2021/12/01
*/
#pragma once




class ITexture
{
private:
	//���W
	DirectX::SimpleMath::Vector2 mPosition;
	//�g�嗦
	DirectX::SimpleMath::Vector2 mScale;
	//��]��
	float mRot;
	// �����x
	float mAlpha;

	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

public:
	//�R���X�g���N�^
	ITexture(const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const float& rot, const float& alpha);

	//����������
	virtual void Initialize() = 0;

	//�`�揈��
	virtual void Draw() = 0;

	//�摜�̎w��
	void SetTexture(ID3D11ShaderResourceView* texture) { mTexture = texture; }
	ID3D11ShaderResourceView* GetTexture()const { return mTexture.Get(); }



	//���W�̎w��
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { mPosition = position; }
	//�g�嗦�̎w��
	void SetScale(const DirectX::SimpleMath::Vector2& scale) { mScale = scale; }
	//��]���̎w��
	void SetRot(const float& rot) { mRot = rot; }
	//�����x�̎w��
	void SetAlpha(const float& alpha) { mAlpha = alpha; }
	float GetAlpha()const { return mAlpha; }

	//���W�̎擾
	DirectX::SimpleMath::Vector2 GetPosition()const { return mPosition; }
	//�g�嗦�̎擾
	DirectX::SimpleMath::Vector2 GetScale()const { return mScale; }

protected:
	//��]���̎擾
	float GetRot()const { return mRot; }
};
