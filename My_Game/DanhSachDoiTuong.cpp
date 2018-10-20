#include "DanhSachDoiTuong.h"

// bắt buộc cung cấp cho Compiler 1 static DanhSachDoiTuong
DanhSachDoiTuong *DanhSachDoiTuong::mDuyNhat = new DanhSachDoiTuong();

DanhSachDoiTuong * DanhSachDoiTuong::DuyNhat()
{
	return mDuyNhat;
}

void DanhSachDoiTuong::ThemDoiTuong(DoiTuong * in_DoiTuong)
{
	mDanhSach.push_back(in_DoiTuong);
}

void DanhSachDoiTuong::DonDep()
{
	// chỉ làm trống Danh Sách, chứ không xóa các con trỏ Đối Tượng trong đó
	// việc xóa các con trỏ Đối Tượng do Lớp khác quyết định
	// mà việc xóa con trỏ đối tượng sẽ dẫn đến phần tử trong Danh Sách có giá trị (gần như) NULL
	mDanhSach.clear();
}
