// FUN_0048b48b @ 0048b48b size=351 sig=undefined FUN_0048b48b() cc=unknown
// callers: FUN_0048b5ea
// callees: CreateCompatibleBitmap,ReleaseDC,GetDIBits,GetDC,DeleteObject

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048b48b(void)

{
  HDC hdc;
  HBITMAP hbm;
  tagBITMAPINFO local_430;
  int local_404;
  int local_400;
  undefined1 local_8 [4];
  
  hdc = GetDC((HWND)0x0);
  hbm = CreateCompatibleBitmap(hdc,1,1);
  if (hbm != (HBITMAP)0x0) {
    local_430.bmiHeader.biSize = 0x28;
    local_430.bmiHeader.biBitCount = 0;
    GetDIBits(hdc,hbm,0,0,(LPVOID)0x0,&local_430,0);
    DAT_0065e590 = (uint)local_430.bmiHeader.biBitCount;
    if (((local_430.bmiHeader.biBitCount == 0x10) || (local_430.bmiHeader.biBitCount == 0x18)) ||
       (local_430.bmiHeader.biBitCount == 0x20)) {
      local_430.bmiHeader.biSize = 0x28;
      local_430.bmiHeader.biWidth = 1;
      local_430.bmiHeader.biHeight = 1;
      local_430.bmiHeader.biPlanes = 1;
      local_430.bmiHeader.biCompression = 3;
      GetDIBits(hdc,hbm,1,1,local_8,&local_430,0);
      if (local_430.bmiHeader.biBitCount == 0x10) {
        if (((local_430.bmiColors[0] == (RGBQUAD)0x7c00) && (local_404 == 0x3e0)) &&
           (local_400 == 0x1f)) {
          _DAT_0065e5a4 = 2;
        }
        else {
          _DAT_0065e5a4 = 3;
        }
      }
      else if (local_430.bmiHeader.biBitCount == 0x18) {
        _DAT_0065e5a4 = 4;
      }
      else {
        _DAT_0065e5a4 = 4;
      }
    }
    else {
      _DAT_0065e5a4 = 1;
      DAT_0065e590 = 8;
    }
    DeleteObject(hbm);
  }
  ReleaseDC((HWND)0x0,hdc);
  return;
}

