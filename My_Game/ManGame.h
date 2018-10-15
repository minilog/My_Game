#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "ToanCauGame.h"

// Là 1 lớp giao diện, sử dụng để gọi đến Bản Đồ thực sự
class ManGame
{
protected:
	ManGame()
	{
		mMauNen = 0x4866ff;
		TaiDuLieu();
	}
public:
	virtual void CapNhat(float in_tg) {}
	virtual void TaiDuLieu() {}
	virtual void Ve() {}
	virtual void OnKeyDown(int in_KeyCode) {}
	virtual void OnKeyUp(int in_KeyCode) {}
	virtual void OnMouseDown(float in_x, float in_y) {}
	D3DCOLOR NhanMauNen()
	{
		return mMauNen;
	}

protected:
	D3DCOLOR mMauNen;
};


