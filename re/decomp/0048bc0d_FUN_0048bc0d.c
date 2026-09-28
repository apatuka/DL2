// FUN_0048bc0d @ 0048bc0d size=419 sig=undefined FUN_0048bc0d() cc=unknown
// callers: FUN_0048bf93
// callees: FUN_0048f774,FUN_0048bb80,ReleaseDC,CreateDIBSection,FUN_0048bbe2,GetDC

undefined4 FUN_0048bc0d(undefined4 *param_1,LONG param_2,int param_3,uint param_4)

{
  BYTE BVar1;
  int iVar2;
  undefined4 uVar3;
  BITMAPINFO local_43c;
  undefined4 local_410;
  undefined4 local_40c;
  int local_14;
  void *local_10;
  HDC local_c;
  HBITMAP local_8;
  
  if (param_4 == 0) {
    param_4 = DAT_0065e5a8;
  }
  local_c = GetDC((HWND)0x0);
  iVar2 = 0;
  do {
    BVar1 = (BYTE)iVar2;
    local_43c.bmiColors[iVar2].rgbBlue = BVar1;
    local_43c.bmiColors[iVar2].rgbRed = BVar1;
    local_43c.bmiColors[iVar2].rgbGreen = BVar1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x100);
  local_43c.bmiHeader.biSize = 0x28;
  local_43c.bmiHeader.biWidth = param_2;
  local_43c.bmiHeader.biHeight = -param_3;
  local_43c.bmiHeader.biPlanes = 1;
  local_43c.bmiHeader.biBitCount = (WORD)param_4;
  local_43c.bmiHeader.biCompression = 0;
  if (param_4 == 8) {
    local_14 = 1;
  }
  else if (param_4 == 0x10) {
    local_43c.bmiHeader.biCompression = 3;
    local_14 = DAT_0065e5ac;
    if (DAT_0065e5a8 != 0x10) {
      local_14 = 2;
    }
    if (local_14 == 2) {
      local_43c.bmiColors[0].rgbBlue = '\0';
      local_43c.bmiColors[0].rgbGreen = '|';
      local_43c.bmiColors[0].rgbRed = '\0';
      local_43c.bmiColors[0].rgbReserved = '\0';
      local_410 = 0x3e0;
      local_40c = 0x1f;
    }
    else {
      local_43c.bmiColors[0].rgbBlue = '\0';
      local_43c.bmiColors[0].rgbGreen = 0xf8;
      local_43c.bmiColors[0].rgbRed = '\0';
      local_43c.bmiColors[0].rgbReserved = '\0';
      local_410 = 0x7e0;
      local_40c = 0x1f;
    }
  }
  else if (param_4 == 0x18) {
    local_14 = 4;
  }
  else if (param_4 == 0x20) {
    local_14 = 4;
  }
  local_43c.bmiHeader.biSizeImage = 0;
  local_43c.bmiHeader.biXPelsPerMeter = 1;
  local_43c.bmiHeader.biYPelsPerMeter = 1;
  local_43c.bmiHeader.biClrUsed = 0;
  if ((int)param_4 < 0x18) {
    local_43c.bmiHeader.biClrUsed = param_4 ^ 2;
  }
  local_43c.bmiHeader.biClrImportant = 0;
  local_8 = CreateDIBSection(local_c,&local_43c,0,&local_10,(HANDLE)0x0,0);
  FUN_0048f774(param_1,0xb0,0);
  param_1[1] = param_2;
  param_1[2] = param_3;
  *param_1 = local_10;
  param_1[3] = param_4;
  *(undefined2 *)(param_1 + 10) = 0;
  *(undefined2 *)(param_1 + 9) = 0;
  uVar3 = FUN_0048bbe2(&local_43c);
  param_1[4] = uVar3;
  *(undefined2 *)((int)param_1 + 0x2a) = 1;
  param_1[0x10] = local_8;
  param_1[0xf] = 0;
  *(undefined2 *)((int)param_1 + 0x26) = (undefined2)local_14;
  FUN_0048bb80(param_1,0);
  ReleaseDC((HWND)0x0,local_c);
  return 1;
}

