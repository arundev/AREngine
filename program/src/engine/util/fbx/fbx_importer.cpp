#include "fbx_importer.h"

#ifdef IOS_REF
	#undef  IOS_REF
	#define IOS_REF (*(fbx_manager_->GetIOSettings()))
#endif

FbxImporterTool::FbxImporterTool() :
fbx_manager_(NULL),
scene_(NULL){
	Init();
}

FbxImporterTool::~FbxImporterTool(){
	Free();
}

bool FbxImporterTool::Init(){

	fbx_manager_ = FbxManager::Create();
	if (fbx_manager_ == NULL){
		g_log->Write("failed to create fbx manager");
		return false;
	}
	else{
		FBXSDK_printf("Autodesk FBX SDK version %s\n", fbx_manager_->GetVersion());
	}

	FbxIOSettings* ios = FbxIOSettings::Create(fbx_manager_, IOSROOT);
	fbx_manager_->SetIOSettings(ios);

	FbxString lPath = FbxGetApplicationDirectory();
	fbx_manager_->LoadPluginsDirectory(lPath.Buffer());

	scene_ = FbxScene::Create(fbx_manager_, "");
	if (scene_ == NULL){
		g_log->Write("failed to create scene");
		return false;
	}

	return true;
}

void FbxImporterTool::Free(){
	if (fbx_manager_ != NULL){
		fbx_manager_->Destroy();
	}
	
}

bool FbxImporterTool::LoadScene(const char* pchPath){
	if (fbx_manager_ == NULL){
		return false;
	}

	FbxImporter* importer = FbxImporter::Create(fbx_manager_, "");
	if (importer == nullptr) {
		g_log->Write("failed to create fbx importer");
		return false;
	}
	
	bool status = importer->Initialize(pchPath, -1, fbx_manager_->GetIOSettings());
	if (!status) {
		g_log->Write("failed to initialize importer");
		importer->Destroy();
		return false;
	}

	if (importer->IsFBX()){
		IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
		IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
		IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
		IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
		IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
		IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
		IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
		IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
	}

	status = importer->Import(scene_);

	ParseAll();

	importer->Destroy();

	return status;
}

bool FbxImporterTool::ParseAll(){
	FbxNode *root = scene_->GetRootNode();
	return ParseNode(root);
}

bool FbxImporterTool::ParseNode(FbxNode* node){
	if (node == NULL){
		return false;
	}

	FbxNodeAttribute::EType attribute_type;

	if (node->GetNodeAttribute() == NULL){
		FBXSDK_printf("node attribute is null");
	}
	else {
		attribute_type = node->GetNodeAttribute()->GetAttributeType();
		switch (attribute_type) {
		case fbxsdk_2015_1::FbxNodeAttribute::eMesh:
			ParseMesh(node);
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < node->GetChildCount(); i++) {
		ParseNode(node->GetChild(i));
	}

	return true;
}

bool FbxImporterTool::ParseMesh(FbxNode* node){
	return true;
}
