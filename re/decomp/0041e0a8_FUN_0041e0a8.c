// FUN_0041e0a8 @ 0041e0a8 size=338 sig=undefined FUN_0041e0a8() cc=unknown
// callers: FUN_0041e440,FUN_0041e26c
// callees: FUN_0041ba74,FUN_0041b934,FUN_0044ba40,FUN_0044b7d8,FUN_0044c754

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041e0a8(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  cVar1 = FUN_0041b934(param_1,param_2,&local_8,&local_c);
  if (cVar1 != '\0') {
    DAT_004b7848 = local_8;
    DAT_004b784c = local_c;
    if ((&DAT_004b7760)[local_8 * 0xd + local_c] == 1) {
      (&DAT_004b7760)[local_8 * 0xd + local_c] = 2;
    }
    else if ((&DAT_004b7760)[local_8 * 0xd + local_c] == 2) {
      (&DAT_004b7760)[local_8 * 0xd + local_c] = 1;
    }
    if (_DAT_0053b340 < 6) {
      iVar3 = *(int *)(DAT_0053b850 + 0x14 + _DAT_0053b340 * 4);
      iVar2 = FUN_0044ba40(DAT_0053b850);
      iVar2 = iVar2 - *(int *)(DAT_0053b850 + 0x14 + _DAT_0053b340 * 4);
    }
    else {
      iVar3 = FUN_0044c754(DAT_0053b84c);
      iVar2 = FUN_0044b7d8(DAT_0053b84c);
      iVar4 = FUN_0044c754(DAT_0053b84c);
      iVar2 = iVar2 - iVar4;
    }
    FUN_0041ba74((int)(char)(&DAT_0059f162)
                            [(char)(&DAT_005a43f0)[*(short *)(DAT_0053b850 + 8) * 0xadc] * 0x2d8],
                 iVar2 + iVar3,iVar3);
  }
  return;
}

