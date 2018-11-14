#include "Man1.h"
#include "Camera.h"
#include "KieuDuLieu.h"
#include "VaChamGame.h"
#include "ToanCauGame.h"
#include "GameLog.h"

#include "Sound.h"
#include <vector>

Man1::Man1()
{
	TaiDuLieu();
}


Man1::~Man1()
{
}

void Man1::TaiDuLieu()
{
	ManGame::mMauNen = 0x54acd2;

	TaoBanDoVaCamera();

	TaoDanhSachTileset();
}

void Man1::CapNhat(float in_tg)
{
	if (mKeys[VK_LEFT])
	{
		Camera::set_ToaDo(Vec2(
			Camera::get_ToaDo().x - 50.0f,
			Camera::get_ToaDo().y));
	}
	if (mKeys[VK_RIGHT])
	{
		Camera::set_ToaDo(Vec2(
			Camera::get_ToaDo().x + 50.0f,
			Camera::get_ToaDo().y));
	}
	if (mKeys[VK_UP])
	{
		Camera::set_ToaDo(Vec2(
			Camera::get_ToaDo().x,
			Camera::get_ToaDo().y - 50.0f));
	}
	if (mKeys[VK_DOWN])
	{
		Camera::set_ToaDo(Vec2(
			Camera::get_ToaDo().x,
			Camera::get_ToaDo().y + 50.0f));
	}
}

void Man1::Ve()
{
	Vec2 lDoDoi(ToanCauGame::get_ChieuRong() / 2 - Camera::get_ToaDo().x,
		ToanCauGame::get_ChieuCao() / 2 - Camera::get_ToaDo().y);

	VeHinhAnhBanDoGame(lDoDoi);
}

void Man1::OnKeyDown(int in_KeyCode)
{
	mKeys[in_KeyCode] = true;
}

void Man1::OnKeyUp(int in_KeyCode)
{
	mKeys[in_KeyCode] = false;
}

void Man1::TaoBanDoVaCamera()
{
	// TAO_BAN_DO
	ManGame::mBanDo = new Tmx::Map();
	ManGame::mBanDo->ParseFile("Map1.tmx");

	ManGame::mChieuRong = ManGame::mBanDo->GetWidth() * ManGame::mBanDo->GetTileWidth();
	ManGame::mChieuCao = ManGame::mBanDo->GetHeight() * ManGame::mBanDo->GetTileHeight();

	//mChieuRongTile = ManGame::mBanDo->GetTileWidth();
	//mChieuCaoTile = ManGame::mBanDo->GetTileHeight();

	// TAO_CAMERA
	Camera::set_ToaDo(Vec2(
		ToanCauGame::get_ChieuRong() / 2.0f,
		2368.0f));
	Camera::set_KichThuoc(ToanCauGame::get_ChieuRong(), ToanCauGame::get_ChieuCao());
	Camera::set_GioiHan(0, ManGame::mChieuRong, 0, ManGame::mChieuCao);
}

void Man1::TaoDanhSachTileset()
{
	//for (int i = 0; i < mBanDo->GetNumTilesets(); i++)
	//{
	//	const Tmx::Tileset *lTileset = mBanDo->GetTileset(i);
	//	HinhAnh *lHinhAnh = new HinhAnh(lTileset->GetImage()->GetSource().c_str());
	//	mDanhSachTileset.insert(pair<int, HinhAnh*>(i, lHinhAnh));
	//}
	mAnhMan1 = new HinhAnh("Resources_X3/Map1/Map1.png");
	mAnhMan1->set_TiLe(Vec2(3.0f, 3.0f));
}

void Man1::TaoDanhSachDoiTuong()
{
}

void Man1::VeHinhAnhBanDoGame(const Vec2 & in_DoDoi)
{
	mAnhMan1->set_ToaDo(Vec2(11904.0f, 3072));
	mAnhMan1->set_DoDoi(in_DoDoi);
	mAnhMan1->Ve();

	//for (int i = 0; i < mBanDo->GetNumTileLayers(); i++)
	//{
	//	const Tmx::TileLayer *layer = mBanDo->GetTileLayer(i);

	//	if (!layer->IsVisible())
	//	{
	//		continue;
	//	}

	//	for (int j = 0; j < mBanDo->GetNumTilesets(); j++)
	//	{
	//		const Tmx::Tileset *tileSet = mBanDo->GetTileset(j);

	//		HCN lHCN_1;

	//		int tileWidth = mBanDo->GetTileWidth();
	//		int tileHeight = mBanDo->GetTileHeight();

	//		int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
	//		int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

	//		for (int m = 0; m < layer->GetHeight(); m++)
	//		{
	//			for (int n = 0; n < layer->GetWidth(); n++)
	//			{
	//				//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
	//				//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
	//				Vec2 position(n * tileWidth + tileWidth / 2.0f,
	//					m * tileHeight + tileHeight / 2.0f);

	//				{
	//					HCN lHCN_2(
	//						int(position.x - tileWidth / 2.0f),
	//						int(position.x + tileWidth / 2.0f),
	//						int(position.y - tileHeight / 2.0f),
	//						int(position.y + tileHeight / 2.0f));

	//					if (!VaChamGame::get_KetQuaVaCham(Camera::get_HCNGioiHan(), lHCN_2).eKQVC_DaVaCham)
	//						continue;
	//				}

	//				if (layer->GetTileTilesetIndex(n, m) == j)
	//				{
	//					int tileID = layer->GetTileId(n, m);

	//					int y = tileID / tileSetWidth;
	//					int x = tileID - y * tileSetWidth;

	//					lHCN_1.Tren = y * tileHeight;
	//					lHCN_1.Duoi = lHCN_1.Tren + tileHeight;
	//					lHCN_1.Trai = x * tileWidth;
	//					lHCN_1.Phai = lHCN_1.Trai + tileWidth;

	//					HinhAnh* lHinhAnh = mDanhSachTileset[j];

	//					lHinhAnh->set_ToaDo(position);
	//					lHinhAnh->set_ChieuRong(mChieuRongTile);
	//					lHinhAnh->set_ChieuCao(mChieuCaoTile);
	//					lHinhAnh->set_HCN(lHCN_1);
	//					lHinhAnh->set_DoDoi(in_DoDoi);
	//					lHinhAnh->Ve();
	//				}
	//			}
	//		}
	//	}
	//}
}

void Man1::CapNhatDanhSachDoiTuong(float in_tg)
{
}

void Man1::VeDanhSachDoiTuong(const Vec2 & in_DoDoi)
{
}
