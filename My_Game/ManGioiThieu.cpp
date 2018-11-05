#include "ManGioiThieu.h"
#include "KieuDuLieuEnum.h"
#include "Camera.h"
#include "VaChamGame.h"

ManGioiThieu::ManGioiThieu()
{
	TaiDuLieu();
}


void ManGioiThieu::TaiDuLieu()
{
	// thiết lập màu nền cho Màn Game
	mMauNen = 0x54acd2;

#pragma region khởi tạo Bản Đồ, chiều rộng, chiều cao Bản Đồ, chiều rộng, chiều cao của 1 Tile nhỏ = 32 bit
	mBanDo = new Tmx::Map();
	mBanDo->ParseFile("TheGioiMario.tmx");

	mChieuRong = mBanDo->GetWidth() * mBanDo->GetTileWidth();
	mChieuCao = mBanDo->GetHeight() * mBanDo->GetTileHeight();

	mChieuRongTile = mBanDo->GetTileWidth();
	mChieuCaoTile = mBanDo->GetTileHeight();
#pragma endregion

	// thiết lập Camera để có thể di chuyển trong màn Game Giới Thiệu
	Camera::CungCapDuLieu(D3DXVECTOR3(ToanCauGame::iChieuRong() / 2.0f,
		mChieuCao - ToanCauGame::iChieuCao() / 2.0f, 0.0f),
		ToanCauGame::iChieuRong(), ToanCauGame::iChieuCao());

#pragma region khởi tạo danh sách TileSet để vẽ hình ảnh Bản Đồ
	for (int i = 0; i < mBanDo->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *lTileset = mBanDo->GetTileset(i);
		HinhAnh *lHinhAnh = new HinhAnh(lTileset->GetImage()->GetSource().c_str());
		mDanhSachTileset.insert(pair<int, HinhAnh*>(i, lHinhAnh));
	}
#pragma endregion

#pragma region khởi tạo danh sách Gạch Bình Thường, Gạch Vàng, Đối Tượng Tĩnh
	// khởi tạo danh sách Gạch Vàng, Gạch Bình Thường
	for (int i = 0; i < mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomObject = mBanDo->GetObjectGroup(i);

		// đưa các Object trong Bản Đồ vào trong các danh sách
		for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
		{
			// lấy Object trong Bản Đồ
			const Tmx::Object *lObject = lNhomObject->GetObjects().at(j);

			// lấy toạ độ
			const D3DXVECTOR3 lToaDo(lObject->GetX() + lObject->GetWidth() / 2.0f,
				lObject->GetY() - lObject->GetHeight() / 2.0f,
				0.0f);

			if (lNhomObject->GetName() == "GachBinhThuong")
			{
				GachBinhThuong *lGachBinhThuong = new GachBinhThuong(lToaDo);
				lGachBinhThuong->mLoaiDoiTuong = eLoaiDoiTuong::eVienGachVangBinhThuong;

				mDanhSachGachBinhThuong.push_back(lGachBinhThuong);
			}
			else if (lNhomObject->GetName() == "GachVang")
			{
				GachVang *lGachVang = new GachVang(lToaDo);
				lGachVang->mLoaiDoiTuong = eLoaiDoiTuong::eVienGachVangAnDuoc;

				mDanhSachGachVang.push_back(lGachVang);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh")
			{
				// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy
				const D3DXVECTOR3 lToaDoDoiTuongTinh(lObject->GetX() + lObject->GetWidth() / 2.0f,
					lObject->GetY() + lObject->GetHeight() / 2.0f,
					0.0f);

				DoiTuong *lDoiTuong = new DoiTuong(lToaDoDoiTuongTinh, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					lObject->GetWidth(), lObject->GetHeight());
				lDoiTuong->mLoaiDoiTuong = eLoaiDoiTuong::eThucTheTinh;

				mDanhSachDoiTuong.push_back(lDoiTuong);
			}
		}
	}
#pragma endregion

}




void ManGioiThieu::CapNhat(float in_tg)
{
	//KiemTraVaCham();

	for (int i = 0; i < int(mDanhSachGachBinhThuong.size()); i++)
	{
		mDanhSachGachBinhThuong[i]->CapNhat(in_tg);
	}

	for (int i = 0; i < int(mDanhSachGachVang.size()); i++)
	{
		mDanhSachGachVang[i]->CapNhat(in_tg);
	}

	//DieuKhienCamera();
}

void ManGioiThieu::Ve()
{
	D3DXVECTOR2 lDoDoi = D3DXVECTOR2(ToanCauGame::iChieuRong() / 2.0f - Camera::vToaDo().x,
		ToanCauGame::iChieuCao() / 2.0f - Camera::vToaDo().y);

	// Copy Code
#pragma region vẽ hình ảnh Bản Đồ Game
	for (size_t i = 0; i < mBanDo->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mBanDo->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		for (size_t j = 0; j < mBanDo->GetNumTilesets(); j++)
		{
			const Tmx::Tileset *tileSet = mBanDo->GetTileset(j);

			RECT sourceRECT;

			int tileWidth = mBanDo->GetTileWidth();
			int tileHeight = mBanDo->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (size_t m = 0; m < layer->GetHeight(); m++)
			{
				for (size_t n = 0; n < layer->GetWidth(); n++)
				{
					//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

					{
						RECT objRECT;
						objRECT.left = position.x - tileWidth / 2;
						objRECT.top = position.y - tileHeight / 2;
						objRECT.right = objRECT.left + tileWidth;
						objRECT.bottom = objRECT.top + tileHeight;

						if (!VaChamGame::kqvcHCNVaHCN(Camera::rHCNGioiHan(), objRECT).DaVaCham)
							continue;
					}

					if (layer->GetTileTilesetIndex(n, m) == j)
					{
						int tileID = layer->GetTileId(n, m);

						int y = tileID / tileSetWidth;
						int x = tileID - y * tileSetWidth;

						sourceRECT.top = y * tileHeight;
						sourceRECT.bottom = sourceRECT.top + tileHeight;
						sourceRECT.left = x * tileWidth;
						sourceRECT.right = sourceRECT.left + tileWidth;

						HinhAnh* lHinhAnh = mDanhSachTileset[j];

						lHinhAnh->ThietLapToaDo(position);
						lHinhAnh->ThietLapChieuRong(mChieuRongTile);
						lHinhAnh->ThietLapChieuCao(mChieuCaoTile);
						lHinhAnh->ThietLapHCN(sourceRECT);
						lHinhAnh->ThietLapDoDoi(lDoDoi);
						lHinhAnh->Ve();
					}
				}
			}
		}
	}
#pragma endregion

#pragma region Ve Cac Vien Gach

	for (int i = 0; i < int(mDanhSachGachBinhThuong.size()); i++)
	{
		mDanhSachGachBinhThuong[i]->Ve(lDoDoi);
	}

	for (int i = 0; i < int(mDanhSachGachVang.size()); i++)
	{
		mDanhSachGachVang[i]->Ve(lDoDoi);
	}

#pragma endregion
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
	//mKeys[in_Keys] = true;
	if (in_Keys == VK_LEFT)
	{
		Camera::ThietLapToaDo(D3DXVECTOR3(Camera::vToaDo().x - 10,
			Camera::vToaDo().y, 0.0f));
	}
	if (in_Keys == VK_RIGHT)
	{
		Camera::ThietLapToaDo(D3DXVECTOR3(Camera::vToaDo().x + 10,
			Camera::vToaDo().y, 0.0f));
	}
	if (in_Keys == VK_UP)
	{
		Camera::ThietLapToaDo(D3DXVECTOR3(Camera::vToaDo().x,
			Camera::vToaDo().y - 10, 0.0f));
	}
	if (in_Keys == VK_DOWN)
	{
		Camera::ThietLapToaDo(D3DXVECTOR3(Camera::vToaDo().x,
			Camera::vToaDo().y + 10, 0.0f));
	}
}

void ManGioiThieu::OnKeyUp(int in_Keys)
{
	mKeys[in_Keys] = false;
}

ManGioiThieu::~ManGioiThieu()
{
	delete mBanDo;

	for (int i = 0; i < int(mDanhSachTileset.size()); i++)
	{
		if (mDanhSachTileset[i])
			delete mDanhSachTileset[i];		
	}
	mDanhSachTileset.clear();

	for (size_t i = 0; i < mDanhSachGachBinhThuong.size(); i++)
	{
		if (mDanhSachGachBinhThuong[i])
			delete mDanhSachGachBinhThuong[i];
	}
	mDanhSachGachBinhThuong.clear();

	for (size_t i = 0; i < mDanhSachGachVang.size(); i++)
	{
		if (mDanhSachGachVang[i])
			delete mDanhSachGachVang[i];
	}
	mDanhSachGachVang.clear();

	for (size_t i = 0; i < mDanhSachDoiTuong.size(); i++)
	{
		if (mDanhSachDoiTuong[i])
			delete mDanhSachDoiTuong[i];
	}
	mDanhSachDoiTuong.clear();
}