//#pragma once
//
//
//// CModel box�ŕ\�����Ă����̂��A�v���C���[�ɕ����悤�Ƃ��Ă���Ƃ���i�G���[����j
//
//
//class CPlayer
//{
//protected:
//	CModel*		m_p_model;		// CModel�C���X�^���X�|�C���^
//	VECTOR3D	m_position;	// �\�����W
//	VECTOR3D	m_rotation;	// ��]�p�x�i�x�j
//
//public:
//	CPlayer() {};
//	CPlayer(CModel* pmodel) { m_p_model = pmodel; };
//	virtual ~CPlayer() {};
//
//	void		SetModel(CModel* pmodel) { m_p_model = pmodel; };	//CModel�C���X�^���X�Z�b�g
//	CModel*		GetModel() { return m_p_model; };	// CModel�C���X�^���X�Q�b�g
//	void		SetPosition(float x, float y, float z)	// �\�����W�Z�b�g
//	{
//		m_position.x = x;
//		m_position.y = y;
//		m_position.z = z;
//	};
//	VECTOR3D	GetPosition() { return m_position; };	// �\�����W�Q�b�g
//	void		SetRotation(float x, float y, float z)	// ��]�p�x�Z�b�g
//	{
//		m_rotation.x = x;
//		m_rotation.y = y;
//		m_rotation.z = z;
//	};
//	VECTOR3D	GetRotation() { return m_rotation; };	// ��]�p�x�Q�b�g
//
//public:
//	void	Init();
//	void	Uninit();
//	void	Update();
//	void	Draw();	
//};