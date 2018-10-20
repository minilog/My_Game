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
	static DanhSachDoiTuong *DuyNhat() {
		if (mDuyNhat == NULL)
		{
			mDuyNhat = new DanhSachDoiTuong();
		}
		return mDuyNhat;
	}

	std::vector<DoiTuong*>& DanhSach() { // đưa con trỏ & vào để thực thi trên chính Danh Sách
		return mDanhSach;
	}

private:
	std::vector<DoiTuong*> mDanhSach;
};

