//
//#include "player.h"
//#include "model.h"
//
//
//void CPlayer::Init()
//{
//	m_p_model = new CModel();
//	m_p_model->Load("asset\\model\\cube.obj");
//
//	m_position = VECTOR3D(0.0f, 0.0f, 0.0f);
//	m_rotation = VECTOR3D(0.0f, 0.0f, 0.0f);
//}
//
//
//void CPlayer::Uninit()
//{
//	m_p_model->Unload();
//	delete m_p_model;
//}
//
//
//void CPlayer::Update()
//{
//
//}
//
//
//void CPlayer::Draw()
//{
//	m_p_model->Draw();
//
//	//// この辺で行列を作ったりPushしたり…
//	//if (m_p_model != NULL) { m_p_model->Draw(); }	// CModelインスタンスがあれば表示
//	//// この辺でPopしたり
//}