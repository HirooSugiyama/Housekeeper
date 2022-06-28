/*
操作方法描画UIの定数群
作成者：杉山
作成日：2022/01/30
*/


struct ControlPanelConstant
{
	//画像拡大率
	static const DirectX::SimpleMath::Vector2 TEX_SCALE;

	//描画位置
	static const DirectX::SimpleMath::Vector2 MOVE_POS;
	static const DirectX::SimpleMath::Vector2 ATTACK_POS;
	static const DirectX::SimpleMath::Vector2 CHANGE_POS;
	static const DirectX::SimpleMath::Vector2 PAUSE_POS;
	static const DirectX::SimpleMath::Vector2 RESTART_POS;

	//画像切り取り位置
	static const RECT MOVE_RECT;
	static const RECT ATTACK_RECT;
	static const RECT CHANGE_RECT;
	static const RECT PAUSE_RECT;
	static const RECT RESTART_RECT;

	//key→GamePad
	static const LONG GAMEPAD_TOP;
	static const LONG GAMEPAD_BOTTOM;




};