// FUN_0048d391 @ 0048d391 size=446 sig=undefined FUN_0048d391() cc=unknown
// callers: FUN_0048d205,FUN_004916e9,FUN_004a52db,FUN_00463bcc
// callees: GlobalLock,FUN_0048d364,GlobalUnlock,ReleaseDC,CreateCompatibleDC,DeleteDC,SelectObject,SetDIBColorTable,GetDC

void FUN_0048d391(int param_1,HGLOBAL param_2)

{
  LPVOID pvVar1;
  int iVar2;
  RGBQUAD local_818 [256];
  undefined1 local_418 [1020];
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  HGDIOBJ local_18;
  HDC local_14;
  HDC local_10;
  int *local_c;
  int local_8;
  
  if (param_2 != (HGLOBAL)0x0) {
    if (*(short *)(param_1 + 0x2a) == 0) {
      pvVar1 = GlobalLock(param_2);
      for (iVar2 = 0; iVar2 < *(short *)((int)pvVar1 + 2); iVar2 = iVar2 + 1) {
        local_418[iVar2 * 4] = *(undefined1 *)((int)pvVar1 + iVar2 * 4 + 8);
        local_418[iVar2 * 4 + 1] = *(undefined1 *)((int)pvVar1 + iVar2 * 4 + 9);
        local_418[iVar2 * 4 + 2] = *(undefined1 *)((int)pvVar1 + iVar2 * 4 + 10);
        local_418[iVar2 * 4 + 3] = 4;
      }
      if (DAT_0051b82c == 0) {
        local_418[0] = 0;
        local_418[1] = 0;
        local_418[2] = 0;
        local_418[3] = 0;
        local_1c = 0xff;
        local_1b = 0xff;
        local_1a = 0xff;
        local_19 = 0;
      }
      GlobalUnlock(param_2);
      (**(code **)(*DAT_0051b810 + 0x14))(DAT_0051b810,0x44,local_418,&local_8,0);
      if (local_8 != 0) {
        iVar2 = (**(code **)(**(int **)(param_1 + 0x40) + 0x50))(*(int **)(param_1 + 0x40),&local_c)
        ;
        if (iVar2 != 0) {
          local_c = (int *)0x0;
        }
        (**(code **)(**(int **)(param_1 + 0x40) + 0x7c))(*(int **)(param_1 + 0x40),local_8);
        if (local_c != (int *)0x0) {
          (**(code **)(*local_c + 8))(local_c);
        }
        FUN_0048d364(param_1,param_2);
      }
    }
    else if (*(short *)(param_1 + 0x2a) == 1) {
      local_10 = GetDC((HWND)0x0);
      local_14 = CreateCompatibleDC(local_10);
      local_18 = SelectObject(local_14,*(HGDIOBJ *)(param_1 + 0x40));
      pvVar1 = GlobalLock(param_2);
      for (iVar2 = 0; iVar2 < *(short *)((int)pvVar1 + 2); iVar2 = iVar2 + 1) {
        local_818[iVar2].rgbBlue = *(BYTE *)((int)pvVar1 + iVar2 * 4 + 10);
        local_818[iVar2].rgbGreen = *(BYTE *)((int)pvVar1 + iVar2 * 4 + 9);
        local_818[iVar2].rgbRed = *(BYTE *)((int)pvVar1 + iVar2 * 4 + 8);
        local_818[iVar2].rgbReserved = '\0';
      }
      GlobalUnlock(param_2);
      SetDIBColorTable(local_14,0,(int)*(short *)((int)pvVar1 + 2),local_818);
      SelectObject(local_14,local_18);
      DeleteDC(local_14);
      ReleaseDC((HWND)0x0,local_10);
      FUN_0048d364(param_1,param_2);
    }
    else {
      FUN_0048d364(param_1,param_2);
    }
  }
  return;
}

