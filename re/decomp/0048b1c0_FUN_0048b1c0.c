// FUN_0048b1c0 @ 0048b1c0 size=240 sig=undefined FUN_0048b1c0() cc=unknown
// callers: 
// callees: FUN_0048b018,LoadCursorA,FUN_0048b5ea,DefWindowProcA,SetCursor

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

LRESULT FUN_0048b1c0(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  int iVar1;
  HCURSOR hCursor;
  LRESULT LVar2;
  int iVar3;
  tagPAINTSTRUCT tStack_58;
  tagRECT tStack_18;
  LRESULT local_8;
  
  for (iVar3 = DAT_0051b8dc; 0 < iVar3; iVar3 = iVar3 + -1) {
    iVar1 = (**(code **)(&DAT_0065e600 + iVar3 * 4))(param_1,param_2,param_3,param_4,&local_8);
    if (iVar1 != 0) {
      return local_8;
    }
  }
  if ((int)param_2 < 0x15) {
    if (param_2 == 0x14) {
      if (param_1 == DAT_0051b834) {
        return 1;
      }
    }
    else {
      switch(param_2) {
      case 2:
        PostQuitMessage(0);
        break;
      case 3:
        if (param_1 == DAT_0051b834) {
          FUN_0048afe3(param_1,param_4 & 0xffff,param_4 >> 0x10);
        }
        break;
      case 0xf:
        if (param_1 == DAT_0051b834) {
          GetUpdateRect(param_1,&tStack_18,0);
          BeginPaint(param_1,&tStack_58);
          EndPaint(param_1,&tStack_58);
          return 0;
        }
        break;
      case 0x12:
        _DAT_0051b828 = 0;
      }
    }
  }
  else if (param_2 == 0x1c) {
    FUN_0048b018(param_1,param_3);
  }
  else {
    if (param_2 == 0x20) {
      if ((short)param_4 == 1) {
        hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
        SetCursor(hCursor);
        return 0;
      }
      return 1;
    }
    if (param_2 == 0x7e) {
      FUN_0048b5ea();
    }
    else if ((param_2 == 0x112) && (param_3 == 0xf100)) {
      return 0;
    }
  }
  LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar2;
}

