#include "ManGioiThieu.h"
#include "KieuDuLieu.h"
#include "Camera.h"
#include "VaChamGame.h"
#include "ToanCauGame.h"
#include "GameLog.h"

#include "Sound.h"

ManGioiThieu::ManGioiThieu() {
	TaiDuLieu();
	mMario = new Mario(Vec2(210, 850));
}

ManGioiThieu::~ManGioiThieu()
{
// XOA_BAN_DO
	if (mBanDo)
	{
		delete mBanDo;
	}

// XOA_DS_TILESET
	for (int i = 0; i < int(ManGame::mDanhSachTileset.size()); i++)
	{
		if (ManGame::mDanhSachTileset[i])
		{
			delete ManGame::mDanhSachTileset[i];
		}
	}
	ManGame::mDanhSachTileset.clear();

// XOA_DS_GACH_BINH_THUONG
	for (size_t i = 0; i < mDanhSachGachBinhThuong.size(); i++)
	{
		if (mDanhSachGachBinhThuong[i])
		{
			delete mDanhSachGachBinhThuong[i];
		}
	}
	mDanhSachGachBinhThuong.clear();

// XOA_DS_GACH_VANG
	for (size_t i = 0; i < mDanhSachGachVang.size(); i++)
	{
		if (mDanhSachGachVang[i])
		{
			delete mDanhSachGachVang[i];
		}
	}
	mDanhSachGachVang.clear();

// XOA_DS_DOI_TUONG_TINH
	for (size_t i = 0; i < mDanhSachDoiTuongTinh.size(); i++)
	{
		if (mDanhSachDoiTuongTinh[i])
		{
			delete mDanhSachDoiTuongTinh[i];
		}
	}
	mDanhSachDoiTuongTinh.clear();

// XOA_MARIO
	if (mMario)
	{
		delete mMario;
	}
}

void ManGioiThieu::TaiDuLieu()
{
	ManGame::mMauNen = 0x54acd2;

	TaoBanDoVaCamera();

	TaoDanhSachTileset();

	TaoDanhSachDoiTuong();

	GAMELOG("So Luong Gach: %d", mDanhSachGachBinhThuong.size());

	mDebugDraw = new GameDebugDraw();

	Sound::getInstance()->loadSound("Resources/man2_1.wav", "man1");
	Sound::getInstance()->play("man1", true, 1);
}

void ManGioiThieu::CapNhat(float in_tg)
{
	// cập nhật
	mMario->CapNhat(in_tg);
	CapNhatDanhSachDoiTuong(in_tg);

	// xử lý va chạm
	for (auto lDTT : mDanhSachDoiTuongTinh)
	{
		// các đối tượng nằm trong Camera thì mới xét Xử Lý Va Chạm
		const eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(Camera::get_HCNGioiHan(), lDTT->get_HCNGioiHan());
		if (lKQVC.eKQVC_DaVaCham)
		{ 
			mMario->XuLyVaCham(lDTT);
		}
	}
	for (auto lGBT : mDanhSachGachBinhThuong)
	{
		const eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(Camera::get_HCNGioiHan(), lGBT->get_HCNGioiHan());
		if (lKQVC.eKQVC_DaVaCham && !lGBT->get_BiPhaHuy())
		{
			// xét va chạm Gạch Bình Thường trước, vì sau khi Mario xử lý va chạm thì
			// tọa độ của nó sẽ thay đổi
			lGBT->XuLyVaCham(mMario);
			mMario->XuLyVaCham(lGBT);
		}
	}



	// xử lý bàn phím
	mMario->XuLyBanPhim(mKeys);

	// điều khiển Camera
	Camera::set_ToaDo(mMario->get_ToaDo());
}

void ManGioiThieu::Ve()
{
	Vec2 lDoDoi (ToanCauGame::get_ChieuRong() / 2 - Camera::get_ToaDo().x,
		ToanCauGame::get_ChieuCao() / 2 - Camera::get_ToaDo().y);

	VeHinhAnhBanDoGame(lDoDoi);

	VeDanhSachDoiTuong(lDoDoi);

	mMario->Ve(lDoDoi);

	//RECT lHCN;
	//lHCN.left = mMario->get_HCNGioiHan().Trai;
	//lHCN.right = mMario->get_HCNGioiHan().Phai;
	//lHCN.top = mMario->get_HCNGioiHan().Tren;
	//lHCN.bottom = mMario->get_HCNGioiHan().Duoi;
	//mDebugDraw->DrawRect(lHCN);
}

void ManGioiThieu::OnKeyDown(int in_Keys)
{
	mKeys[in_Keys] = true;


	if (in_Keys == VK_ESCAPE)
	{
		ToanCauGame::mGameDangChay = false;
	}
}

void ManGioiThieu::OnKeyUp(int in_Keys)
{
	mKeys[in_Keys] = false;
}

void ManGioiThieu::TaoBanDoVaCamera()
{
	// TAO_BAN_DO
	ManGame::mBanDo = new Tmx::Map();
	ManGame::mBanDo->ParseFile("TheGioiMario.tmx");

	ManGame::mChieuRong = ManGame::mBanDo->GetWidth() * ManGame::mBanDo->GetTileWidth();
	ManGame::mChieuCao = ManGame::mBanDo->GetHeight() * ManGame::mBanDo->GetTileHeight();

	ManGame::mChieuRongTile = ManGame::mBanDo->GetTileWidth();
	ManGame::mChieuCaoTile = ManGame::mBanDo->GetTileHeight();

	// TAO_CAMERA
	Camera::set_ToaDo(Vec2(
		ToanCauGame::get_ChieuRong() / 2.0f,
		mChieuCao - ToanCauGame::get_ChieuCao() / 2.0f));
	Camera::set_KichThuoc(800, 700);
	Camera::set_GioiHan(0, ManGame::mChieuRong, 0, ManGame::mChieuCao);
}

void ManGioiThieu::TaoDanhSachTileset()
{
	for (int i = 0; i < mBanDo->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *lTileset = mBanDo->GetTileset(i);
		HinhAnh *lHinhAnh = new HinhAnh(lTileset->GetImage()->GetSource().c_str());
		mDanhSachTileset.insert(pair<int, HinhAnh*>(i, lHinhAnh));
	}
}

void ManGioiThieu::TaoDanhSachDoiTuong()
{
	for (int i = 0; i < ManGame::mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomObject = mBanDo->GetObjectGroup(i);

		// đưa các Object trong Bản Đồ vào trong các danh sách
		for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
		{
			// lấy Object trong Bản Đồ
			const Tmx::Object *lObject = lNhomObject->GetObjects().at(j);

			// lấy toạ độ
			const Vec2 lToaDo(lObject->GetX() + lObject->GetWidth() / 2.0f,
				lObject->GetY() - lObject->GetHeight() / 2.0f);

			// khởi tạo danh sách Gạch Vàng, Gạch Bình Thường
			if (lNhomObject->GetName() == "GachBinhThuong")
			{
				GachBinhThuong *lGachBinhThuong = new GachBinhThuong(lToaDo);
				mDanhSachGachBinhThuong.push_back(lGachBinhThuong);
			}
			else if (lNhomObject->GetName() == "GachVang")
			{
				GachVang *lGachVang = new GachVang(lToaDo);
				mDanhSachGachVang.push_back(lGachVang);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy
				const Vec2 lToaDoDoiTuongTinh(
					lObject->GetX() + lObject->GetWidth() / 2.0f,
					lObject->GetY() + lObject->GetHeight() / 2.0f);

				DoiTuongTinh *lDoiTuongTinh = new DoiTuongTinh(lToaDoDoiTuongTinh,
					lObject->GetWidth(), lObject->GetHeight());

				mDanhSachDoiTuongTinh.push_back(lDoiTuongTinh);
			}
		}
	}
}

void ManGioiThieu::VeHinhAnhBanDoGame(const Vec2& in_DoDoi)
{
	for (int i = 0; i < mBanDo->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mBanDo->GetTileLayer(i);

		if (!layer->IsVisible())
		{
			continue;
		}

		for (int j = 0; j < mBanDo->GetNumTilesets(); j++)
		{
			const Tmx::Tileset *tileSet = mBanDo->GetTileset(j);

			HinhChuNhat lHCN_1;

			int tileWidth = mBanDo->GetTileWidth();
			int tileHeight = mBanDo->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (int m = 0; m < layer->GetHeight(); m++)
			{
				for (int n = 0; n < layer->GetWidth(); n++)
				{
					//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
					//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
					Vec2 position(n * tileWidth + tileWidth / 2.0f,
						m * tileHeight + tileHeight / 2.0f);

					{
						HinhChuNhat lHCN_2(
							int(position.x - tileWidth / 2.0f),
							int(position.x + tileWidth / 2.0f),
							int(position.y - tileHeight / 2.0f),
							int(position.y + tileHeight / 2.0f));

						if (!VaChamGame::get_KetQuaVaCham(Camera::get_HCNGioiHan(), lHCN_2).eKQVC_DaVaCham)
							continue;
					}

					if (layer->GetTileTilesetIndex(n, m) == j)
					{
						int tileID = layer->GetTileId(n, m);

						int y = tileID / tileSetWidth;
						int x = tileID - y * tileSetWidth;

						lHCN_1.Tren = y * tileHeight;
						lHCN_1.Duoi = lHCN_1.Tren + tileHeight;
						lHCN_1.Trai = x * tileWidth;
						lHCN_1.Phai = lHCN_1.Trai + tileWidth;

						HinhAnh* lHinhAnh = mDanhSachTileset[j];

						lHinhAnh->set_ToaDo(position);
						lHinhAnh->set_ChieuRong(mChieuRongTile);
						lHinhAnh->set_ChieuCao(mChieuCaoTile);
						lHinhAnh->set_HCN(lHCN_1);
						lHinhAnh->set_DoDoi(in_DoDoi);
						lHinhAnh->Ve();
					}
				}
			}
		}
	}
}

void ManGioiThieu::CapNhatDanhSachDoiTuong(float in_tg)
{
	for (int i = 0; i < int(mDanhSachGachBinhThuong.size()); i++)
	{
		mDanhSachGachBinhThuong[i]->CapNhat(in_tg);
	}
	for (int i = 0; i < int(mDanhSachGachVang.size()); i++)
	{
		mDanhSachGachVang[i]->CapNhat(in_tg);
	}
}

void ManGioiThieu::VeDanhSachDoiTuong(const Vec2& in_DoDoi)
{
	for (int i = 0; i < int(mDanhSachGachBinhThuong.size()); i++)
	{
		mDanhSachGachBinhThuong[i]->Ve(in_DoDoi);
	}
	for (int i = 0; i < int(mDanhSachGachVang.size()); i++)
	{
		mDanhSachGachVang[i]->Ve(in_DoDoi);
	}
}

