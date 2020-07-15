//#pragma once
//
//
//// CModel boxで表示していたのを、プレイヤーに分けようとしているところ（エラーあり）
//
//
//class CPlayer
//{
//protected:
//	CModel*		m_p_model;		// CModelインスタンスポインタ
//	VECTOR3D	m_position;	// 表示座標
//	VECTOR3D	m_rotation;	// 回転角度（度）
//
//public:
//	CPlayer() {};
//	CPlayer(CModel* pmodel) { m_p_model = pmodel; };
//	virtual ~CPlayer() {};
//
//	void		SetModel(CModel* pmodel) { m_p_model = pmodel; };	//CModelインスタンスセット
//	CModel*		GetModel() { return m_p_model; };	// CModelインスタンスゲット
//	void		SetPosition(float x, float y, float z)	// 表示座標セット
//	{
//		m_position.x = x;
//		m_position.y = y;
//		m_position.z = z;
//	};
//	VECTOR3D	GetPosition() { return m_position; };	// 表示座標ゲット
//	void		SetRotation(float x, float y, float z)	// 回転角度セット
//	{
//		m_rotation.x = x;
//		m_rotation.y = y;
//		m_rotation.z = z;
//	};
//	VECTOR3D	GetRotation() { return m_rotation; };	// 回転角度ゲット
//
//public:
//	void	Init();
//	void	Uninit();
//	void	Update();
//	void	Draw();	
//};