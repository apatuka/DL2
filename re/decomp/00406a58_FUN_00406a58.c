// FUN_00406a58 @ 00406a58 size=195 sig=undefined FUN_00406a58() cc=unknown
// callers: FUN_00407030,FUN_004073e4
// callees: FUN_00444274,FUN_0046ca40

undefined4 FUN_00406a58(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  if ((1 << ((byte)param_2 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0) {
    iVar5 = 0;
    if ((param_3 & 2) != 0) {
      iVar5 = -0x14;
    }
    if ((param_3 & 8) != 0) {
      iVar5 = iVar5 + -10;
    }
    if ((param_3 & 4) != 0) {
      iVar5 = iVar5 + -10;
    }
    if ((param_3 & 0x10) != 0) {
      iVar5 = iVar5 + -0x1e;
    }
    iVar2 = FUN_00444274(param_2);
    iVar3 = FUN_00444274(param_1);
    if (iVar3 < iVar2) {
      iVar5 = iVar5 + -10;
    }
    else {
      iVar2 = FUN_00444274(param_2);
      iVar3 = FUN_00444274(param_1);
      if (iVar2 < iVar3) {
        iVar5 = iVar5 + 10;
      }
    }
    iVar2 = *(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c);
    uVar4 = FUN_0046ca40();
    if ((int)(uVar4 % 100) < iVar5 + (iVar2 * -100) / 0x32) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

