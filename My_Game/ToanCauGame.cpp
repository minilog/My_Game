#include "ToanCauGame.h"

HINSTANCE ToanCauGame::mTruongHopXuLy = NULL;
HWND ToanCauGame::mCuaSoXuLy = NULL;
LPD3DXSPRITE ToanCauGame::mXuLyHinhAnh = NULL;
LPDIRECT3DDEVICE9 ToanCauGame::mThietBi = NULL;
int ToanCauGame::mChieuRong = 600;
int ToanCauGame::mChieuCao = 600;
IDirect3DSurface9* ToanCauGame::matSau = nullptr;
bool ToanCauGame::gameDangChay = true;
