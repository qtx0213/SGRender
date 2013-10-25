/*****************************************************
	D3D9Render.h
******************************************************/
#pragma once

class D3D9Render:public SRenderBase
{
public:
	D3D9Render(void);
	virtual ~D3D9Render(void);

public:
	virtual bool CreateDevice(uint wnd, bool fullscreen, uint multiSampleQuality);
};
