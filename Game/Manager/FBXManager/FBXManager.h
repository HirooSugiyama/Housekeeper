/*
FBXマネージャー
作成者：杉山
作成日：2021/06/24
*/



//class FBXManager
//{
//private:
//
//	// FBXManager作成
//	FBXManager* fbx_manager = FBXManager::Create();
//	if (fbx_manager == nullptr)
//	{
//		// 作成失敗
//		return 0;
//	}
//
//
//
//public:
//
//	// FbxImporter作成
//	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "ImportTest");
//	if (fbx_importer == nullptr)
//	{
//		fbx_manager->Destroy();
//
//		// 作成失敗
//		return 0;
//	}
//
//
//	// FbxScene作成
//		FbxScene * fbx_scene = FbxScene::Create(fbx_manager, "SceneTest");
//	if (fbx_scene == nullptr)
//	{
//		fbx_importer->Destroy();
//		fbx_manager->Destroy();
//
//		// 作成失敗
//		return 0;
//	}
//
//
//
//	// ファイルを初期化する
//	if (fbx_importer->Initialize("Box.fbx") == false)
//	{
//		fbx_importer->Destroy();
//		fbx_scene->Destroy();
//		fbx_manager->Destroy();
//
//		// 初期化失敗
//		return 0;
//	}
//
//
//	// インポート
//	if (fbx_importer->Import(fbx_scene) == false)
//	{
//		fbx_importer->Destroy();
//		fbx_scene->Destroy();
//		fbx_manager->Destroy();
//
//		// インポート失敗
//		return 0;
//	}
//
//
//
//	if (fbx_importer != nullptr)
//	{
//		fbx_importer->Destroy();
//	}
//
//	if (fbx_scene != nullptr)
//	{
//		fbx_scene->Destroy();
//	}
//
//	if (fbx_manager != nullptr)
//	{
//		fbx_manager->Destroy();
//	}
//
//
//
//
//};