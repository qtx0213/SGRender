/************************************************
	SRender.h

*************************************************/

#ifndef __SRender__H__
#define __SRender__H__
#include "tool/SRTypes.h"
class SRenderBase
{
public:
	SRenderBase(void){};
	~SRenderBase(void){};

	virtual bool CreateDevice(uint wnd, bool fullscreen = false, uint multiSampleQuality = 0);



protected:
private:
};

#endif