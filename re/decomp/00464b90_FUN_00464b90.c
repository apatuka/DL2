// FUN_00464b90 @ 00464b90 size=297 sig=undefined FUN_00464b90() cc=unknown
// callers: FUN_00465070,FUN_00464cbc,FUN_00465164
// callees: FUN_00463bcc,FUN_00463e04,FUN_00463aec,BlitSprite8,RealizePalette,GetDCOrgEx,OffsetRect,FUN_00463da8,SelectPalette,FUN_0048bdb0,FUN_0048c85e

void FUN_00464b90(HDC param_1,LONG *param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  BOOL BVar2;
  HPALETTE hPal;
  int iVar3;
  LONG *pLVar4;
  tagRECT *ptVar5;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  tagRECT local_1c;
  tagPOINT local_c;
  
  iVar1 = FUN_00463e04();
  BVar2 = GetDCOrgEx(param_1,&local_c);
  if (BVar2 != 0) {
    pLVar4 = param_2;
    ptVar5 = &local_1c;
    for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
      ptVar5->left = *pLVar4;
      pLVar4 = pLVar4 + 1;
      ptVar5 = (tagRECT *)&ptVar5->top;
    }
    OffsetRect(&local_1c,local_c.x,local_c.y);
    FUN_00463bcc(iVar1,param_4,param_5,0);
    FUN_00463da8(iVar1);
    BlitSprite8(param_3,0,0,param_4,param_5,param_4,1);
    local_2c = 0;
    local_28 = 0;
    local_24 = param_4;
    local_20 = param_5;
    local_1c.right = param_4 + local_1c.left;
    local_1c.bottom = param_5 + local_1c.top;
    if (*(short *)(*(int *)(&DAT_0058de34 + iVar1 * 0x1c) + 0x2a) == 1) {
      hPal = SelectPalette(param_1,DAT_004d2360,0);
      RealizePalette(param_1);
      FUN_0048bdb0(*(undefined4 *)(*(int *)(&DAT_0058de34 + iVar1 * 0x1c) + 0x40),param_1,&local_2c,
                   param_2,0xcc0020);
      SelectPalette(param_1,hPal,1);
    }
    else {
      FUN_0048c85e(*(undefined4 *)(&DAT_0058de34 + iVar1 * 0x1c),&DAT_0065e644,&local_2c,&local_1c,0
                   ,&DAT_0065e580,0);
    }
    FUN_00463aec(iVar1);
    FUN_00463da8(1);
  }
  return;
}

