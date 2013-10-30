#include "StdAfx.h"
#include "D3D9Render.h"

D3D9Render::D3D9Render(uint wnd, bool fullscreen, uint multiSampleQuality, SREM_CULLMODE emcullmode):
	m_hwnd(wnd),
	m_emCullMode(emcullmode),
	m_fullscreen(fullscreen),
	m_multiSampleQuality(m_multiSampleQuality)
{
	HRESULT hresult;

	m_pd3d9 = Direct3DCreate9(D3D_SDK_VERSION);


	UINT defaultadapter = D3DADAPTER_DEFAULT;
	D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;
	D3DFORMAT	defualtFormat = D3DFORMAT::D3DFMT_A8R8G8B8;

	D3DPRESENT_PARAMETERS d3dparams;
	ZeroMemory(&d3dparams, sizeof(D3DPRESENT_PARAMETERS));

	//get dpi
	if(m_fullscreen)
	{
		RECT fullwndRect;
		::GetWindowRect(::GetDesktopWindow(), &fullwndRect);
		m_wndWidth = fullwndRect.right - fullwndRect.left;
		m_wndHeight = fullwndRect.bottom - fullwndRect.top;

		uint maxRefreshRate = 0;
		uint modeCount = m_pd3d9->GetAdapterModeCount(defaultadapter, defualtFormat);

		D3DDISPLAYMODE d3dMode;
		for(uint mode = 0; mode < modeCount; ++mode)
		{
			m_pd3d9->EnumAdapterModes(defaultadapter, defualtFormat, mode, &d3dMode);
			if(d3dMode.Width == m_wndWidth && d3dMode.Height == m_wndHeight)
			{
				if(d3dMode.RefreshRate > maxRefreshRate)
					maxRefreshRate = d3dMode.RefreshRate;
			}
		}

		d3dparams.BackBufferFormat = defualtFormat;
		d3dparams.BackBufferHeight = m_wndWidth;
		d3dparams.BackBufferWidth = m_wndHeight;
		d3dparams.FullScreen_RefreshRateInHz = maxRefreshRate;
		d3dparams.Windowed = false;
	}
	else
	{
		RECT wndRect;
		GetWindowRect(m_hwnd, &wndRect);
		m_wndHeight = wndRect.bottom - wndRect.top;
		m_wndWidth =   wndRect.right =wndRect.left;

		d3dparams.BackBufferFormat = defualtFormat;
		d3dparams.BackBufferWidth = m_wndWidth;
		d3dparams.BackBufferHeight = m_wndHeight;
		d3dparams.FullScreen_RefreshRateInHz = 0;
	}
	
	d3dparams.BackBufferCount = 2;

	//查看多重采样的支持
	D3DMULTISAMPLE_TYPE maxMultiSampleLevel = 0;
	hresult = m_pd3d9->CheckDeviceMultiSampleType(defaultadapter, deviceType, d3dparams.BackBufferFormat
		, !m_fullscreen, D3DMULTISAMPLE_NONMASKABLE, &maxMultiSampleLevel);

	if(SUCCEEDED(hresult) && maxMultiSampleLevel > 0 && multiSampleQuality > 0)
	{
		if(multiSampleQuality >= maxMultiSampleLevel)
			multiSampleQuality = maxMultiSampleLevel - 1;
		d3dparams.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
		d3dparams.MultiSampleQuality = multiSampleQuality;
	}
	else
	{
		d3dparams.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dparams.MultiSampleQuality = 0;
	}

	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = m_hwnd;
	d3dparams.EnableAutoDepthStencil = true;
	d3dparams.AutoDepthStencilFormat = D3DFMT_D24FS8;
	d3dparams.Flags = D3DPRESENTFLAG_DEVICECLIP | D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	d3dparams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	DWORD behaviorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	hresult = m_pd3d9->CreateDevice(defaultadapter, deviceType, (HWND)m_hwnd, behaviorFlag, &d3dparams, &m_pd3d9Device);
	if(FAILED(hresult))
	{
		RELEASE(m_pd3d9Device);
		behaviorFlag = D3DCREATE_MIXED_VERTEXPROCESSING;
		hresult =m_pd3d9->CreateDevice(defaultadapter, deviceType, (HWND)m_hwnd, behaviorFlag, &d3dparams, &m_pd3d9Device);
		if(FAILED(hr))
		{
			RELEASE(m_pd3d9Device);
			behaviorFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			hresult = mD3D9->CreateDevice(defaultadapter, deviceType, (HWND)m_hwnd, behaviorFlag, &d3dparams, &m_pd3d9Device);
			if(FAILED(hr))
			{
				RELEASE(mD3DDevice);
			}
		}
	}



}

D3D9Render::~D3D9Render(void)
{
}

void D3D9Render::CreateDevice(uint wnd, bool fullscreen, uint multiSampleQuality)
{

}
