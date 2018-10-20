#pragma once

#include <vector>
#include "DoiTuong.h"

// chỉ có một Camera duy nhất: lớp Single Ton
class DanhSachDoiTuong
{
private:
	static DanhSachDoiTuong *mDuyNhat;
	DanhSachDoiTuong() 
	{	// vì là lớp Single Ton nên chưa thể cung cấp dữ liệu ở Constructure, 
		// dữ liệu sẽ được thêm ở hàm Thêm Thực Thể
	}
public:
	static DanhSachDoiTuong *DuyNhat();

	void ThemDoiTuong(DoiTuong *in_DoiTuong);
	// lúc tạo Màn Game mới, tức là Bản Đồ mới sẽ cần dọn dẹp Màn Game Cũ
	void DonDep();

private:
	std::vector<DoiTuong*> mDanhSach;
};

