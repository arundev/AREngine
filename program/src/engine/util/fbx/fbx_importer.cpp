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
	mesh_data_ = new MeshRes();
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

	FbxMesh* mesh = node->GetMesh();
	if (mesh == NULL){
		return false;
	}

	

	int triangle_num = mesh->GetPolygonCount();
	MeshRes::Vertex* vertex_data = new MeshRes::Vertex[triangle_num * 3];
	for (int i = 0; i < triangle_num; i++){
		for (int j = 0; j < 3; j++){
			int vertex_index = mesh->GetPolygonVertex(i, j);
			ReadVertex(mesh, vertex_index, vertex_data[i * 3 + j]);
			ReadColor(mesh, i*3+j, vertex_index, vertex_data[i * 3 + j]);
			for (int k = 0; k < 2; k++){
				ReadUV(mesh, vertex_index, mesh->GetTextureUVIndex(i, j), k, vertex_data[i * 3 + j]);
			}
			ReadNormal(mesh, vertex_index, i * 3 + j, vertex_data[i * 3 + j]);
			ReadTangent(mesh, vertex_index, i * 3 + j, vertex_data[i * 3 + j]);
		}
	}

	return true;
}

void FbxImporterTool::ReadVertex(FbxMesh* mesh, int index, MeshRes::Vertex& vertex){
	FbxVector4* ctrl_point = mesh->GetControlPoints();
	vertex.position.x_ = ctrl_point[index][0];
	vertex.position.y_ = ctrl_point[index][1];
	vertex.position.z_ = ctrl_point[index][2];
}

void FbxImporterTool::ReadColor(FbxMesh* mesh, int vertex_index, int index, MeshRes::Vertex& vertex){

	if (mesh->GetElementVertexColor() == NULL){
		return;
	}

	FbxGeometryElementVertexColor* vertex_color = mesh->GetElementVertexColor(0);
	switch (vertex_color->GetMappingMode())
	{
		case FbxGeometryElement::eByControlPoint:
		{
			switch (vertex_color->GetReferenceMode())
			{
				case FbxGeometryElement::eDirect:
				{
					vertex.color.x_ = vertex_color->GetDirectArray().GetAt(vertex_index).mRed;
					vertex.color.y_ = vertex_color->GetDirectArray().GetAt(vertex_index).mGreen;
					vertex.color.z_ = vertex_color->GetDirectArray().GetAt(vertex_index).mBlue;
					vertex.color.w_ = vertex_color->GetDirectArray().GetAt(vertex_index).mAlpha;
				}
				break;
				case FbxGeometryElement::eIndexToDirect:
				{
					int id = vertex_color->GetIndexArray().GetAt(vertex_index);
					vertex.color.x_ = vertex_color->GetDirectArray().GetAt(id).mRed;
					vertex.color.y_ = vertex_color->GetDirectArray().GetAt(id).mGreen;
					vertex.color.z_ = vertex_color->GetDirectArray().GetAt(id).mBlue;
					vertex.color.w_ = vertex_color->GetDirectArray().GetAt(id).mAlpha;
				}
				break;
				default:
					break;
			}
		}
		break;
		case FbxGeometryElement::eByPolygonVertex:{
			switch (vertex_color->GetReferenceMode()){
				case FbxGeometryElement::eDirect:{
					vertex.color.x_ = vertex_color->GetDirectArray().GetAt(index).mRed;
					vertex.color.y_ = vertex_color->GetDirectArray().GetAt(index).mGreen;
					vertex.color.z_ = vertex_color->GetDirectArray().GetAt(index).mBlue;
					vertex.color.w_ = vertex_color->GetDirectArray().GetAt(index).mAlpha;
				}
				break;
				case FbxGeometryElement::eIndexToDirect:{
					int id = vertex_color->GetIndexArray().GetAt(index);
					vertex.color.x_ = vertex_color->GetDirectArray().GetAt(id).mRed;
					vertex.color.y_ = vertex_color->GetDirectArray().GetAt(id).mGreen;
					vertex.color.z_ = vertex_color->GetDirectArray().GetAt(id).mBlue;
					vertex.color.w_ = vertex_color->GetDirectArray().GetAt(id).mAlpha;
				}
				break;
				default:
					break;
			}
		}
		break;
		default:
			break;
	}

}

void FbxImporterTool::ReadUV(FbxMesh* mesh, int vertex_index, int uv_index, int index, MeshRes::Vertex& vertex){
	if (index >=2 || mesh->GetElementUVCount() <= index)
	{
		return;
	}

	FbxGeometryElementUV* element_uv = mesh->GetElementUV(index);
	switch (element_uv->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:{
		switch (element_uv->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			vertex.uv.x_ = element_uv->GetDirectArray().GetAt(vertex_index)[0];
			vertex.uv.x_ = element_uv->GetDirectArray().GetAt(vertex_index)[1];
		}
		break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int id = element_uv->GetIndexArray().GetAt(vertex_index);
			vertex.uv.x_ = element_uv->GetDirectArray().GetAt(id)[0];
			vertex.uv.y_ = element_uv->GetDirectArray().GetAt(id)[1];
		}
		break;
		default:
		break;
		}
	}
		break;
	case FbxGeometryElement::eByPolygonVertex:{
		switch (element_uv->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		case FbxGeometryElement::eIndexToDirect:
		{
			vertex.uv.x_ = element_uv->GetDirectArray().GetAt(uv_index)[0];
			vertex.uv.x_ = element_uv->GetDirectArray().GetAt(uv_index)[1];
		}
		break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
}
void FbxImporterTool::ReadNormal(FbxMesh* mesh, int vertex_index, int index, MeshRes::Vertex& vertex){
	if (mesh->GetElementNormalCount() < 1)
	{
		return;
	}

	FbxGeometryElementNormal* normal_element = mesh->GetElementNormal(0);
	switch (normal_element->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:{
		switch (normal_element->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			vertex.normal.x_ = normal_element->GetDirectArray().GetAt(vertex_index)[0];
			vertex.normal.y_ = normal_element->GetDirectArray().GetAt(vertex_index)[1];
			vertex.normal.z_ = normal_element->GetDirectArray().GetAt(vertex_index)[2];
		}
			break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int id = normal_element->GetIndexArray().GetAt(vertex_index);
			vertex.normal.x_ = normal_element->GetDirectArray().GetAt(id)[0];
			vertex.normal.y_ = normal_element->GetDirectArray().GetAt(id)[1];
			vertex.normal.z_ = normal_element->GetDirectArray().GetAt(id)[2];
		}
			break;
		default:
			break;
		}
	}
		break;
	case FbxGeometryElement::eByPolygonVertex:{
		switch (normal_element->GetReferenceMode()){
		case FbxGeometryElement::eDirect:{
			vertex.normal.x_ = normal_element->GetDirectArray().GetAt(index)[0];
			vertex.normal.y_ = normal_element->GetDirectArray().GetAt(index)[0];
			vertex.normal.z_ = normal_element->GetDirectArray().GetAt(index)[0];
		}
			break;
		case FbxGeometryElement::eIndexToDirect:{
			int id = normal_element->GetIndexArray().GetAt(index);
			vertex.normal.x_ = normal_element->GetDirectArray().GetAt(id)[0];
			vertex.normal.y_ = normal_element->GetDirectArray().GetAt(id)[0];
			vertex.normal.z_ = normal_element->GetDirectArray().GetAt(id)[0];
		}
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
}



void FbxImporterTool::ReadTangent(FbxMesh* mesh, int vertex_index, int index, MeshRes::Vertex& vertex){
	if (mesh->GetElementTangentCount() < 1)
	{
		return;
	}

	FbxGeometryElementTangent* tangent_element = mesh->GetElementTangent(0);
	switch (tangent_element->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:{
		switch (tangent_element->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			vertex.normal.x_ = tangent_element->GetDirectArray().GetAt(vertex_index)[0];
			vertex.normal.y_ = tangent_element->GetDirectArray().GetAt(vertex_index)[1];
			vertex.normal.z_ = tangent_element->GetDirectArray().GetAt(vertex_index)[2];
		}
			break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int id = tangent_element->GetIndexArray().GetAt(vertex_index);
			vertex.normal.x_ = tangent_element->GetDirectArray().GetAt(id)[0];
			vertex.normal.y_ = tangent_element->GetDirectArray().GetAt(id)[1];
			vertex.normal.z_ = tangent_element->GetDirectArray().GetAt(id)[2];
		}
			break;
		default:
			break;
		}
	}
		break;
	case FbxGeometryElement::eByPolygonVertex:{
		switch (tangent_element->GetReferenceMode()){
		case FbxGeometryElement::eDirect:{
			vertex.normal.x_ = tangent_element->GetDirectArray().GetAt(index)[0];
			vertex.normal.y_ = tangent_element->GetDirectArray().GetAt(index)[0];
			vertex.normal.z_ = tangent_element->GetDirectArray().GetAt(index)[0];
		}
			break;
		case FbxGeometryElement::eIndexToDirect:{
			int id = tangent_element->GetIndexArray().GetAt(index);
			vertex.normal.x_ = tangent_element->GetDirectArray().GetAt(id)[0];
			vertex.normal.y_ = tangent_element->GetDirectArray().GetAt(id)[0];
			vertex.normal.z_ = tangent_element->GetDirectArray().GetAt(id)[0];
		}
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
}