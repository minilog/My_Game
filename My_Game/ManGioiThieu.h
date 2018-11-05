#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>
#include "ManGame.h"
#include "HinhAnh.h"
#include "HoatHinh.h"
#include "Camera.h"
#include "GachVang.h"
#include "GachBinhThuong.h"

class ManGioiThieu : public ManGame
{
public:
	ManGioiThieu();
	~ManGioiThieu();
	virtual void TaiDuLieu();
	void CapNhat(float in_tg);
	void Ve();
	void OnKeyDown(int in_Keys);
	void OnKeyUp(int in_Keys);
	void OnMouseDown(float in_X, float in_Y) {}
private:
	void KiemTraVaCham();
	void DieuKhienCamera();

private:
	std::map<int, bool> mKeys;
	std::vector<GachVang*> mDanhSachGachVang;
	std::vector<GachBinhThuong*> mDanhSachGachBinhThuong;
	std::vector<DoiTuong*> mDanhSachDoiTuong; //tạm thời thay thế cho Danh Sách Đối Tượng Tĩnh,
											  // sau này sẽ tạo thêm Đối Tượng Tĩnh để thay vào
};

