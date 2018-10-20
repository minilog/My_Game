//#include "CayBonNhanh.h"
//
//CayBonNhanh::CayBonNhanh(int in_CapDo, RECT in_HCNGioiHan)
//{
//	mCapDo = in_CapDo;
//	mHCNGioiHan = in_HCNGioiHan;
//}
//
//void CayBonNhanh::ThemThucThe(ThucThe * in_ThucThe)
//{
//	int lViTri = iViTriIndex(in_ThucThe->rHCNGioiHan());
//	
//	// in_Thực Thể không thuộc Nhánh con
//	if (lViTri == -1)
//	{
//		mDanhSachThucThe.push_back(in_ThucThe);
//	}
//	else // in_Thực Thể thuộc 1 Nhánh con
//	{
//		if (mCacNhanhCon == NULL)
//		{
//			PhanChia();
//		}
//		mCacNhanhCon[lViTri]->ThemThucThe(in_ThucThe);
//	}
//}
//
//void CayBonNhanh::LayTatCaThucTheCoKhaNangVaCham(std::vector<ThucThe*>& out_DanhSachThucThe, ThucThe * in_ThucThe)
//{
//	int lViTri = iViTriIndex(in_ThucThe->rHCNGioiHan());
//
//	if (lViTri == -1)
//	{
//		LayTatCaThucThe(out_DanhSachThucThe);
//	}
//	else
//	{
//		// lấy danh sách Thực Thể thuộc Nhánh cha này
//		for (auto _lThucThe : mDanhSachThucThe)
//		{
//			out_DanhSachThucThe.push_back(_lThucThe);
//		}
//
//		// Lấy danh sách Thực Thể trong Nhánh con có _lViTri này
//		if (mCacNhanhCon != NULL)
//		{
//			mCacNhanhCon[lViTri]->LayTatCaThucTheCoKhaNangVaCham(out_DanhSachThucThe, in_ThucThe);
//		}
//	}
//}
//
//void CayBonNhanh::PhanChia()
//{
//	mCacNhanhCon = new CayBonNhanh*[4]; // tạo con trỏ - mảng Cây Bốn Nhánh con chưa có thông số
//
//	int lChieuRong = (mHCNGioiHan.right - mHCNGioiHan.left) / 2;
//	int lChieuCao = (mHCNGioiHan.bottom - mHCNGioiHan.top) / 2;
//	
//	RECT lHCN;
//	 // phần gốc Trái bên Trên
//	lHCN.left = mHCNGioiHan.left;
//	lHCN.right = lHCN.left + lChieuRong;
//	lHCN.top = mHCNGioiHan.top;
//	lHCN.bottom = lHCN.top + lChieuCao;
//	mCacNhanhCon[0] = new CayBonNhanh(mCapDo + 1, lHCN);
//
//	// phần gốc Phải bên Trên
//	lHCN.left = mHCNGioiHan.left + lChieuRong;
//	lHCN.right = lHCN.left + lChieuRong;
//	lHCN.top = mHCNGioiHan.top;
//	lHCN.bottom = lHCN.top + lChieuCao;
//	mCacNhanhCon[1] = new CayBonNhanh(mCapDo + 1, lHCN);
//
//	// phần gốc Trái bên Dưới
//	lHCN.left = mHCNGioiHan.left;
//	lHCN.right = lHCN.left + lChieuRong;
//	lHCN.top = mHCNGioiHan.top + lChieuCao;
//	lHCN.bottom = lHCN.top + lChieuCao;
//	mCacNhanhCon[2] = new CayBonNhanh(mCapDo + 1, lHCN);
//
//	// phần gốc Phải bên Dưới
//	lHCN.left = mHCNGioiHan.left + lChieuRong;
//	lHCN.right = lHCN.left + lChieuRong;
//	lHCN.top = mHCNGioiHan.top + lChieuCao;
//	lHCN.bottom = lHCN.top + lChieuCao;
//	mCacNhanhCon[3] = new CayBonNhanh(mCapDo + 1, lHCN);
//}
//
//void CayBonNhanh::DonDep()
//{
//	if (mCacNhanhCon)
//	{
//		for (size_t i = 0; i < 4; i++)
//		{
//			if (mCacNhanhCon[i])
//			{
//				mCacNhanhCon[i]->DonDep();
//				delete mCacNhanhCon[i];
//				mCacNhanhCon[i] = nullptr;
//			}
//		}
//
//		delete[] mCacNhanhCon;
//	}
//}
//
//
//
//
//
//













///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

int CayBonNhanh::iViTriIndex(RECT in_HCNGioiHanThucThe)
{
	float lDuongDocChinhGiua = float(mHCNGioiHan.left + mHCNGioiHan.right) / 2.0f;
	float lDuongNgangChinhGiua = float(mHCNGioiHan.top + mHCNGioiHan.bottom) / 2.0f;

	// nằm phía Trên
	if (in_HCNGioiHanThucThe.top > mHCNGioiHan.top &&
		in_HCNGioiHanThucThe.bottom < lDuongNgangChinhGiua)
	{
		if (in_HCNGioiHanThucThe.left > mHCNGioiHan.left &&
			in_HCNGioiHanThucThe.right < lDuongDocChinhGiua) // nằm phía bên Trái
		{
			return 0;
		}
		else if (in_HCNGioiHanThucThe.left > lDuongDocChinhGiua &&
			in_HCNGioiHanThucThe.right < mHCNGioiHan.right) // nằm phía bên Phải
		{
			return 1;
		}
	}// nằm phía dưới
	else if (in_HCNGioiHanThucThe.top > lDuongNgangChinhGiua)
	{
		if (in_HCNGioiHanThucThe.left > mHCNGioiHan.left &&
			in_HCNGioiHanThucThe.right < lDuongDocChinhGiua) // nằm phía bên Trái
		{
			return 2;
		}
		else if (in_HCNGioiHanThucThe.left > lDuongDocChinhGiua &&
			in_HCNGioiHanThucThe.right < mHCNGioiHan.right) // nằm phía bên Phải
		{
			return 3;
		}
	}

	// không thuộc Nhánh con
	return -1;

}

bool CayBonNhanh::bBaoGom(ThucThe * in_ThucThe)
{
	RECT _lHCN = in_ThucThe->rHCNGioiHan();

	if (_lHCN.left >= mHCNGioiHan.left && _lHCN.right <= mHCNGioiHan.right &&
		_lHCN.top >= mHCNGioiHan.top && _lHCN.bottom <= mHCNGioiHan.bottom)
	{
		return true;
	}

	return false;
}

int CayBonNhanh::iTongSoThucThe()
{
	int _lTong = mDanhSachThucThe.size();

	if (mCacNhanhCon)
	{
		for (size_t i = 0; i < 4; i++)
		{
			_lTong += mCacNhanhCon[i]->iTongSoThucThe();
		}
	}

	return _lTong;
}

void CayBonNhanh::LayTatCaThucThe(std::vector<ThucThe*>& out_DanhSachThucThe)
{
	for (auto _lThucThe : mDanhSachThucThe)
	{
		out_DanhSachThucThe.push_back(_lThucThe);
	}

	if (mCacNhanhCon != NULL)
	{
		for (size_t i = 0; i < 4; i++)
		{
			mCacNhanhCon[i]->LayTatCaThucThe(out_DanhSachThucThe);
		}
	}
}