#include "ManGioiThieu.h"
#include "KieuDuLieuEnum.h"

ManGioiThieu::ManGioiThieu()
{
	TaiDuLieu();
}

void ManGioiThieu::TaiDuLieu()
{
	// thiết lập màu nền cho Màn Game
	mMauNen = 0x54acd2;

	mBanDoGame = new BanDoGame("TheGioiMario.tmx");
	mCamera = new Camera(ToanCauGame::iChieuRong(), ToanCauGame::iChieuCao());
	mBanDoGame->ThietLapCamera(mCamera);
}

void ManGioiThieu::CapNhat(float in_tg)
{
	KiemTraVaCham();
	mBanDoGame->CapNhat(in_tg);

	DieuKhienCamera();
}

void ManGioiThieu::Ve()
{
	mBanDoGame->Ve();
}

void ManGioiThieu::KiemTraVaCham()
{
	//int lChieuRongDay = 0;

	//// lấy ra các Thực Thể có khả năng va chạm với Người Chơi
	//vector<ThucThe*> lDanhSachThucThe;
	//mBanDoGame->cbnCayBonNhanh()->LayTatCaThucTheCoKhaNangVaCham(lDanhSachThucThe, mNguoiChoi);

	//for (int i = 0; i < int(lDanhSachThucThe.size()); i++)
	//{
	//	eKetQuaVaCham lKetQuaVaCham = VaChamGame::kqvcHCNVaHCN(mNguoiChoi->rHCNGioiHan(), 
	//			lDanhSachThucThe.at(i)->rHCNGioiHan());

	//	if (lKetQuaVaCham.DaVaCham)
	//	{
	//		ePhiaVaCham lPhiaVaChamNguoiChoi = VaChamGame::pvcPhiaVaCham(mNguoiChoi, lKetQuaVaCham);
	//		ePhiaVaCham lPhiaVaChamThucThe = VaChamGame::pvcPhiaVaCham(lDanhSachThucThe.at(i), lKetQuaVaCham);

	//		// sau khi có phía va chạm thì gọi đến hàm xử lý va chạm của Người Chơi và Thực Thể
	//		mNguoiChoi->XuLyVaCham(lDanhSachThucThe.at(i), lKetQuaVaCham, lPhiaVaChamNguoiChoi);
	//		lDanhSachThucThe.at(i)->XuLyVaCham(mNguoiChoi, lKetQuaVaCham, lPhiaVaChamThucThe);

	//		// kiểm tra va chạm phía dưới của Người Chơi
	//		if (lPhiaVaChamNguoiChoi == ePhiaVaCham::eDuoi ||
	//			lPhiaVaChamNguoiChoi == ePhiaVaCham::eTraiBenDuoi ||
	//			lPhiaVaChamNguoiChoi == ePhiaVaCham::ePhaiBenDuoi)
	//		{
	//			int lHCNVaCham = lKetQuaVaCham.VungVaCham.right - lKetQuaVaCham.VungVaCham.left;
	//			if (lHCNVaCham > lChieuRongDay)
	//			{
	//				lChieuRongDay = lHCNVaCham;
	//			}
	//		}
	//	}
	//}

	//// nếu Mario đứng ngoài mép thì Mario sẽ rơi xuống đất
}

// thiết lập Camera theo Tạo độ của Người Chơi
void ManGioiThieu::DieuKhienCamera()
{
}

void ManGioiThieu::OnKeyDown(int in_Keys)
{
	mKeys[in_Keys] = true;
}

void ManGioiThieu::OnKeyUp(int in_Keys)
{
	mKeys[in_Keys] = false;
}