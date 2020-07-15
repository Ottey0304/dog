#pragma once


class CField
{

private:
	int m_Texture;

	//CModel* m_Model;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};