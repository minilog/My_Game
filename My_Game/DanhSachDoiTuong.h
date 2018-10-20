#pragma once

#include <vector>

class DanhSachDoiTuong
{
// chỉ có một Danh Sách Thực Thể duy nhất
public:
	static DanhSachDoiTuong *DuyNhat();
private:
	DanhSachDoiTuong();
	static DanhSachDoiTuong *mDuyNhat;

private:

};

