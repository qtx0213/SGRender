/*****************************************************
	D3D9Render.h
******************************************************/
#pragma once
#include "d3d9.h"
#include "rendercommon/rendercommon.h"
class D3D9Render:public SRenderBase
{
public:
	D3D9Render(uint wnd, bool fullscreen, uint multiSampleQuality, SREM_CULLMODE emcullmode);
	virtual ~D3D9Render(void);

public:
	 bool CreateDevice();

private:
	
	IDirect3D9 *m_pd3d9;
	IDirect3DDevice9 *m_pd3d9Device;

	HWND			m_hwnd;
	bool			m_fullscreen;
	uint			m_multiSampleQuality;
	SREM_CULLMODE	m_emCullMode;
	uint			m_wndWidth;
	uint			m_wndHeight;
};
