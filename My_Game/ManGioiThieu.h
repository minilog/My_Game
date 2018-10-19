#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>
#include "ManGame.h"
#include "HinhAnh.h"
#include "HoatHinh.h"
#include "BanDoGame.h"
#include "Camera.h"

class ManGioiThieu : public ManGame
{
public:
	ManGioiThieu();
	void TaiDuLieu();
	void CapNhat(float in_tg);
	void Ve();
	void OnKeyDown(int in_Keys);
	void OnKeyUp(int in_Keys);
	void OnMouseDown(float in_X, float in_Y) {}
protected:
	void KiemTraVaCham();
	void DieuKhienCamera();

protected:
	BanDoGame *mBanDoGame;
	//Camera *mCamera;
	std::map<int, bool> mKeys;
};

