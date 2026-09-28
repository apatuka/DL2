// FUN_00444398 @ 00444398 size=1454 sig=undefined FUN_00444398() cc=unknown
// callers: @WinGWndProc$qqspvuiuil,FUN_0044a474,FUN_00469284
// callees: FUN_0048bdb0,FUN_0048c85e,EndPaint,FUN_0049483f,SelectPalette,BeginPaint,FUN_004943ab,GdiFlush,GetWindowRect,EnterCriticalSection,RealizePalette,GetWindowLongA,OffsetRect,LeaveCriticalSection

void FUN_00444398(HWND param_1)

{
  HDC hdc;
  LONG LVar1;
  int iVar2;
  RECT *pRVar3;
  int *piVar4;
  undefined1 local_8c [16];
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  tagRECT local_6c;
  int local_5c [4];
  tagPAINTSTRUCT local_4c;
  int local_c;
  HPALETTE local_8;
  
  hdc = BeginPaint(param_1,&local_4c);
  LVar1 = GetWindowLongA(param_1,0xc);
  if (LVar1 != 0) {
    pRVar3 = &local_4c.rcPaint;
    piVar4 = local_5c;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar4 = pRVar3->left;
      pRVar3 = (RECT *)&pRVar3->top;
      piVar4 = piVar4 + 1;
    }
    GetWindowRect(param_1,&local_6c);
    OffsetRect(&local_6c,local_5c[0],local_5c[1]);
    local_6c.right = (local_5c[2] - local_5c[0]) + local_6c.left;
    local_6c.bottom = (local_5c[3] - local_5c[1]) + local_6c.top;
    if (DAT_0051b83c != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
    }
    FUN_0049483f(DAT_004d5c28,local_5c,&local_c,local_8c);
    if (*(short *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0x2a) == 1) {
      if (*(int *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0xc) == 8) {
        local_8 = SelectPalette(hdc,DAT_004d2360,0);
        RealizePalette(hdc);
      }
      if (DAT_004c5b74 == 0) {
        FUN_0048bdb0(*(undefined4 *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0x40),hdc,local_5c,
                     local_5c,0xcc0020);
      }
      else {
        if (local_5c[1] < DAT_004c5b74) {
          local_78 = local_5c[1];
          local_70 = DAT_004c5b74 + -1;
          local_7c = local_5c[0];
          local_74 = local_5c[2];
          FUN_0048bdb0(*(undefined4 *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0x40),hdc,&local_7c,
                       &local_7c,0xcc0020);
        }
        if (DAT_004c5b7c < local_5c[3]) {
          local_78 = DAT_004c5b7c + 1;
          local_70 = local_5c[3];
          local_7c = local_5c[0];
          local_74 = local_5c[2];
          FUN_0048bdb0(*(undefined4 *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0x40),hdc,&local_7c,
                       &local_7c,0xcc0020);
        }
        if (local_5c[0] < DAT_004c5b70) {
          local_7c = local_5c[0];
          local_74 = DAT_004c5b70 + -1;
          local_78 = local_5c[1];
          if (local_5c[1] < DAT_004c5b74) {
            local_78 = DAT_004c5b74;
          }
          local_70 = DAT_004c5b7c;
          if (local_5c[3] < DAT_004c5b7c) {
            local_70 = local_5c[3];
          }
          FUN_0048bdb0(*(undefined4 *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0x40),hdc,&local_7c,
                       &local_7c,0xcc0020);
        }
        if (DAT_004c5b78 < local_5c[2]) {
          local_7c = DAT_004c5b78 + 1;
          local_74 = local_5c[2];
          local_78 = local_5c[1];
          if (local_5c[1] < DAT_004c5b74) {
            local_78 = DAT_004c5b74;
          }
          local_70 = DAT_004c5b7c;
          if (local_5c[3] < DAT_004c5b7c) {
            local_70 = local_5c[3];
          }
          FUN_0048bdb0(*(undefined4 *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0x40),hdc,&local_7c,
                       &local_7c,0xcc0020);
        }
      }
      if (*(int *)(*(int *)(&DAT_0058de34 + LVar1 * 0x1c) + 0xc) == 8) {
        SelectPalette(hdc,local_8,1);
      }
    }
    else if (DAT_004c5b74 == 0) {
      FUN_0048c85e(*(undefined4 *)(&DAT_0058de34 + LVar1 * 0x1c),&DAT_0065e644,local_5c,&local_6c,0,
                   &DAT_0065e580,0);
    }
    else {
      if (local_5c[1] < DAT_004c5b74) {
        local_78 = local_5c[1];
        local_70 = DAT_004c5b74 + -1;
        local_7c = local_5c[0];
        local_74 = local_5c[2];
        GetWindowRect(param_1,&local_6c);
        OffsetRect(&local_6c,local_7c,local_78);
        local_6c.right = (local_74 - local_7c) + local_6c.left;
        local_6c.bottom = (local_70 - local_78) + local_6c.top;
        FUN_0048c85e(*(undefined4 *)(&DAT_0058de34 + LVar1 * 0x1c),&DAT_0065e644,&local_7c,&local_6c
                     ,0,&DAT_0065e580,0);
      }
      if (DAT_004c5b7c < local_5c[3]) {
        local_78 = DAT_004c5b7c + 1;
        local_70 = local_5c[3];
        local_7c = local_5c[0];
        local_74 = local_5c[2];
        GetWindowRect(param_1,&local_6c);
        OffsetRect(&local_6c,local_7c,local_78);
        local_6c.right = (local_74 - local_7c) + local_6c.left;
        local_6c.bottom = (local_70 - local_78) + local_6c.top;
        FUN_0048c85e(*(undefined4 *)(&DAT_0058de34 + LVar1 * 0x1c),&DAT_0065e644,&local_7c,&local_6c
                     ,0,&DAT_0065e580,0);
      }
      if (local_5c[0] < DAT_004c5b70) {
        local_7c = local_5c[0];
        local_74 = DAT_004c5b70 + -1;
        local_78 = local_5c[1];
        if (local_5c[1] < DAT_004c5b74) {
          local_78 = DAT_004c5b74;
        }
        local_70 = DAT_004c5b7c;
        if (local_5c[3] < DAT_004c5b7c) {
          local_70 = local_5c[3];
        }
        GetWindowRect(param_1,&local_6c);
        OffsetRect(&local_6c,local_7c,local_78);
        local_6c.right = (local_74 - local_7c) + local_6c.left;
        local_6c.bottom = (local_70 - local_78) + local_6c.top;
        FUN_0048c85e(*(undefined4 *)(&DAT_0058de34 + LVar1 * 0x1c),&DAT_0065e644,&local_7c,&local_6c
                     ,0,&DAT_0065e580,0);
      }
      if (DAT_004c5b78 < local_5c[2]) {
        local_7c = DAT_004c5b78 + 1;
        local_74 = local_5c[2];
        local_78 = local_5c[1];
        if (local_5c[1] < DAT_004c5b74) {
          local_78 = DAT_004c5b74;
        }
        local_70 = DAT_004c5b7c;
        if (local_5c[3] < DAT_004c5b7c) {
          local_70 = local_5c[3];
        }
        GetWindowRect(param_1,&local_6c);
        OffsetRect(&local_6c,local_7c,local_78);
        local_6c.right = (local_74 - local_7c) + local_6c.left;
        local_6c.bottom = (local_70 - local_78) + local_6c.top;
        FUN_0048c85e(*(undefined4 *)(&DAT_0058de34 + LVar1 * 0x1c),&DAT_0065e644,&local_7c,&local_6c
                     ,0,&DAT_0065e580,0);
      }
    }
    if (local_c != 0) {
      FUN_0048c85e(local_c,DAT_004d5c28,local_c + 0x2c,local_8c,0,0,0);
    }
    FUN_004943ab(DAT_004d5c28,0);
    if (DAT_0051b83c != 0) {
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
    }
    GdiFlush();
  }
  EndPaint(param_1,&local_4c);
  return;
}

