/*
�w�肳�ꂽ���̂̉e��\������N���X
�쐬�ҁF���R
�쐬���F2021/09/23
*/
#include "pch.h"
#include "Shadow.h"

/*=================
�R���X�g���N�^
�����F�Ȃ�
====================*/
Shadow::Shadow()
	:
	FlatPolygon()
{
}

/*=========================
�f�X�g���N�^
=========================*/
Shadow::~Shadow()
{

}

/*================
���b�v����������
�����F�Ȃ�
�Ԃ�l�F�Ȃ�
==================*/
void Shadow::WrapInitialize()
{
	//�h�����̏���������
	this->Initialize();

	//�摜��ݒ肷��
	this->SetTexture(static_cast<int>(PlayTexturesResouce::TEXTURE__SHADOW));
}

