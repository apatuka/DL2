// FUN_0048d5c4 @ 0048d5c4 size=335 sig=undefined FUN_0048d5c4() cc=unknown
// callers: FUN_00491200,FUN_00413348
// callees: GlobalLock,GlobalUnlock,ReleaseDC,CreateCompatibleDC,DeleteDC,SelectObject,SetDIBColorTable,GetDC

void FUN_0048d5c4(int param_1)

{
  int iVar1;
  LPVOID pvVar2;
  HDC hdc;
  RGBQUAD local_810 [256];
  undefined1 local_410 [1024];
  HGDIOBJ local_10;
  HDC local_c;
  int *local_8;
  
  if (*(int *)(param_1 + 0x3c) != 0) {
    if (*(short *)(param_1 + 0x2a) == 0) {
      iVar1 = (**(code **)(**(int **)(param_1 + 0x40) + 0x50))(*(int **)(param_1 + 0x40),&local_8);
      if ((iVar1 == 0) && (local_8 != (int *)0x0)) {
        pvVar2 = GlobalLock(*(HGLOBAL *)(param_1 + 0x3c));
        iVar1 = 0;
        do {
          local_410[iVar1 * 4] = *(undefined1 *)((int)pvVar2 + iVar1 * 4 + 8);
          local_410[iVar1 * 4 + 1] = *(undefined1 *)((int)pvVar2 + iVar1 * 4 + 9);
          local_410[iVar1 * 4 + 2] = *(undefined1 *)((int)pvVar2 + iVar1 * 4 + 10);
          local_410[iVar1 * 4 + 3] = 4;
          iVar1 = iVar1 + 1;
        } while (iVar1 < 0x100);
        GlobalUnlock(*(HGLOBAL *)(param_1 + 0x3c));
        (**(code **)(*local_8 + 0x18))(local_8,0,0,0x100,local_410);
      }
    }
    else if (*(short *)(param_1 + 0x2a) == 1) {
      local_c = GetDC((HWND)0x0);
      hdc = CreateCompatibleDC(local_c);
      local_10 = SelectObject(hdc,*(HGDIOBJ *)(param_1 + 0x40));
      pvVar2 = GlobalLock(*(HGLOBAL *)(param_1 + 0x3c));
      for (iVar1 = 0; iVar1 < *(short *)((int)pvVar2 + 2); iVar1 = iVar1 + 1) {
        local_810[iVar1].rgbBlue = *(BYTE *)((int)pvVar2 + iVar1 * 4 + 10);
        local_810[iVar1].rgbGreen = *(BYTE *)((int)pvVar2 + iVar1 * 4 + 9);
        local_810[iVar1].rgbRed = *(BYTE *)((int)pvVar2 + iVar1 * 4 + 8);
        local_810[iVar1].rgbReserved = '\0';
      }
      GlobalUnlock(*(HGLOBAL *)(param_1 + 0x3c));
      SetDIBColorTable(hdc,0,(int)*(short *)((int)pvVar2 + 2),local_810);
      SelectObject(hdc,local_10);
      DeleteDC(hdc);
      ReleaseDC((HWND)0x0,local_c);
    }
  }
  return;
}

