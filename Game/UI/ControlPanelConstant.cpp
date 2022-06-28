/*
������@�`��UI�̒萔�Q
�쐬�ҁF���R
�쐬���F2022/01/30
*/
#include"pch.h"
#include"ControlPanelConstant.h"

//�摜�g�嗦
const DirectX::SimpleMath::Vector2 ControlPanelConstant::TEX_SCALE(0.65f, 0.65f);

//�`��ʒu
const DirectX::SimpleMath::Vector2 ControlPanelConstant::MOVE_POS(21.f, 236.f);
const DirectX::SimpleMath::Vector2 ControlPanelConstant::ATTACK_POS(21.f, 343.f);
const DirectX::SimpleMath::Vector2 ControlPanelConstant::CHANGE_POS(923.f, 543.f);
const DirectX::SimpleMath::Vector2 ControlPanelConstant::PAUSE_POS(21.f, 450.f);
const DirectX::SimpleMath::Vector2 ControlPanelConstant::RESTART_POS(21.f, 550.f);

//�摜�؂���ʒu
const RECT ControlPanelConstant::MOVE_RECT		{ 226,0,473,140 };
const RECT ControlPanelConstant::ATTACK_RECT	{ 0,0,226,140 };
const RECT ControlPanelConstant::CHANGE_RECT	{ 700,0,928,140 };
const RECT ControlPanelConstant::PAUSE_RECT		{ 473,0,700,140 };
const RECT ControlPanelConstant::RESTART_RECT	{ 929,0,1152,140 };

//key��GamePad
const LONG ControlPanelConstant::GAMEPAD_TOP = 140;
const LONG ControlPanelConstant::GAMEPAD_BOTTOM = 280;