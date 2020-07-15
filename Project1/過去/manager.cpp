
#include "main.h"
#include "manager.h"
#include "renderer.h"





void CManager::Init()
{

	CRenderer::Init();



}

void CManager::Uninit()
{


	CRenderer::Uninit();

}

void CManager::Update()
{


}

void CManager::Draw()
{

	CRenderer::Begin();



	CRenderer::End();

}
