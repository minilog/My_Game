#pragma once

#include <math.h>
#include <vector>
#include "ManGame.h"
#include "HoatHinh.h"
#include "Camera.h"
#include "GachVang.h"
#include "GachBinhThuong.h"
#include "DoiTuongTinh.h"
#include "Mario.h"
#include "KieuDuLieu.h"

#include "GameDebugDraw.h"

class ManGioiThieu : public ManGame
{
public:
	ManGioiThieu();
	~ManGioiThieu();
	void TaiDuLieu();
	void CapNhat(float in_tg);
	void Ve();
	void OnKeyDown(int in_Keys);
	void OnKeyUp(int in_Keys);
	void OnMouseDown(float in_X, float in_Y) {}

private:
	std::map<int, bool> mKeys;
	std::vector<GachVang*> mDanhSachGachVang;
	std::vector<GachBinhThuong*> mDanhSachGachBinhThuong;
	std::vector<DoiTuongTinh*> mDanhSachDoiTuongTinh; //tạm thời thay thế cho Danh Sách Đối Tượng Tĩnh,
											  // sau này sẽ tạo thêm Đối Tượng Tĩnh để thay vào
	Mario *mMario;




// Các hàm dùng để đơn giản hóa thuật toán :V
private:
	void TaoBanDoVaCamera();
	void TaoDanhSachTileset(); // Dùng để vẽ Bản Đồ
	void TaoDanhSachDoiTuong();
	void VeHinhAnhBanDoGame(const Vec2& in_DoDoi);
	void CapNhatDanhSachDoiTuong(float in_tg);
	void VeDanhSachDoiTuong(const Vec2& in_DoDoi);

	GameDebugDraw *mDebugDraw;
	

};

