/*
�w�肳�ꂽ���̂̉e��\������N���X
�쐬�ҁF���R
�쐬���F2021/09/23
*/
#include "pch.h"
#include "FlatPolygon.h"

/*=============================
�R���X�g���N�^
�����F�Ȃ�
===============================*/
FlatPolygon::FlatPolygon()
	:
	FlatPolygonBase(),
	mScale(),
	mTexture(nullptr),
	mInputLayout(nullptr)
{
}

/*=========================
�f�X�g���N�^
=========================*/
FlatPolygon::~FlatPolygon()
{

}

/*==================================
������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
===================================*/
void FlatPolygon::Initialize()
{
	const auto pDR = DX::DeviceResources::GetInstance();
	ResourceManager* pRM = ResourceManager::GetInstance();

	// �e�N�X�`���̓ǂݍ���
	mTexture = pRM->GetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SHADOW));


	// �v���~�e�B�u�o�b�`�̍쐬 
	mpPrimitiveBatch =
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(pDR->GetD3DDeviceContext());


	//�x�[�V�b�N�G�t�F�N�g�̍쐬
	mpBasicEffect = std::make_unique<DirectX::BasicEffect>(pDR->GetD3DDevice());

	//���̓��C�A�E�g���쐬���邽�߂ɕK�v�ȏ��
	const void* shaderByteCode;
	size_t byteCodeLength;

	//���_�������肷�邽�߂ɕK�v�ȏ��
	mpBasicEffect->SetLightingEnabled(false);		//���C�gOFF
	mpBasicEffect->SetTextureEnabled(true);			//�e�N�X�`��ON
	mpBasicEffect->SetVertexColorEnabled(false);	//���_�J���[OFF

	//�g�p���钸�_�V�F�[�_�[���̎擾
	mpBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//���̓��C�A�E�g�̍쐬
	pDR->GetD3DDevice()->CreateInputLayout(
		DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		mInputLayout.GetAddressOf()
	);

	//�v���~�e�B�u�o�b�`�̍쐬
	mpPrimitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>
		(pDR->GetD3DDeviceContext());
}



/*=========================
�`�揈��
�����F�`����W
�Ԃ�l�F�Ȃ�
=========================*/
void FlatPolygon::Draw(const DirectX::SimpleMath::Vector3& position)
{
	const auto& pDxIF = DirectXtkComponent::GetDirectXtkComponentInstance();
	const auto& pCiIF = CameraInfoComponent::GetCameraInfoComponentInstance();
	const auto pDR = DX::DeviceResources::GetInstance();

	// D3D�f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̎擾
	auto* context = pDR->GetD3DDeviceContext();


	//�����W�̎w��p�ϐ��̐錾
	float polyRight, polyLeft, polyTop, polyBottom;

	polyRight = position.x + mScale.x;
	polyLeft = position.x - mScale.x;
	polyTop = position.z + mScale.y;
	polyBottom = position.z - mScale.y;

	//�G�t�F�N�g�Ɋe��ϊ��s��̎w��i���[���h�s��ȊO�j
	mpBasicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	mpBasicEffect->SetView(*pCiIF.GetView());				//�r���[�s��̐ݒ�
	mpBasicEffect->SetProjection(*pCiIF.GetProjection());	//�ˉe�s��̐ݒ�
	mpBasicEffect->SetTexture(mTexture.Get());
	mpBasicEffect->Apply(context);
	//���̓A�Z���u���X�e�[�W�ɓ��̓��C�A�E�g��ݒ�
	context->IASetInputLayout(mInputLayout.Get());
	//�����������̐ݒ�:NonPremultiplied->�摜���X�g���[�g�E���`�����l���̏ꍇ
	context->OMSetBlendState(pDxIF.GetCommonStates()->NonPremultiplied(), nullptr,
		0xFFFFFFFF);


	//�s�N�Z���V�F�[�_�ɃT���v���i�e�N�X�`���̈������j���w�肷��
	auto sampler = pDxIF.GetCommonStates()->LinearWrap();
	context->PSSetSamplers(0, 1, &sampler);

	//���X�^���C�U�X�e�[�g�̐ݒ�F�w�ʉ������O(�A�ʏ���)���Ȃ�->�|���S���̗��ʂ��\��
	context->RSSetState(pDxIF.GetCommonStates()->CullNone());

	//// ���_���i�|���S���̒��_�j 
	DirectX::VertexPositionTexture vertex[4] =
	{
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, position.y, polyTop),
			DirectX::SimpleMath::Vector2(0.f, 0.f)
		),	//����	
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight, position.y, polyTop),
			DirectX::SimpleMath::Vector2(0.f, 1.f)
		),	//�E��
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyLeft, position.y, polyBottom),
			DirectX::SimpleMath::Vector2(1.f,0.f)
		),	//����
		DirectX::VertexPositionTexture
		(
			DirectX::SimpleMath::Vector3(polyRight,position.y, polyBottom),
			DirectX::SimpleMath::Vector2(1.f, 1.f)
		),//�E��
	};

	static const uint16_t indices[] = {
		0,1,2,		//1���ڂ̎O�p�`
		1,3,2		//2���ڂ̎O�p�`
	};
	//�v���~�e�B�u�o�b�`�̍쐬
	mpPrimitiveBatch->Begin();

	//���_�C���f�b�N�X���g�����`��
	mpPrimitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indices,
		(sizeof(indices) / sizeof(indices[0])),
		vertex,
		(sizeof(vertex) / sizeof(vertex[0]))
	);

	//�v���~�e�B�u�o�b�`�̏I��
	mpPrimitiveBatch->End();
}

/*=======================
�`�揈��
�����F�摜�̌�
�Ԃ�l�F�Ȃ�
=========================*/
void FlatPolygon::SetTexture(const int& texPath)
{
	ResourceManager* pRM = ResourceManager::GetInstance();

	// �e�N�X�`���̓ǂݍ���
	mTexture = pRM->GetTexture(texPath);

}
