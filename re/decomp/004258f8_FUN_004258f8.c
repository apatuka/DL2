// FUN_004258f8 @ 004258f8 size=460 sig=undefined FUN_004258f8() cc=unknown
// callers: FUN_0042623c,FUN_00425f58
// callees: LoadStringA,FUN_0049eb44

void FUN_004258f8(int param_1,short *param_2)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  CHAR local_408 [1024];
  int local_8;
  
  local_8 = -1;
  if (*(int *)(param_1 + 0x16) != 0) {
    iVar1 = FUN_0049eb44(DAT_004b7ce4,0xd,1,0x18,0,0);
    iVar2 = 0;
    if (0 < iVar1) {
      do {
        FUN_0049eb44(DAT_004b7ce4,0xd,1,0x27,0,0);
        iVar2 = iVar2 + 1;
      } while (iVar2 < iVar1);
    }
    for (iVar1 = 0; iVar1 < *(short *)(param_1 + 0x1e); iVar1 = iVar1 + 1) {
      psVar3 = (short *)(*(int *)(param_1 + 0x16) + iVar1 * 0x24);
      LoadStringA(DAT_0058f19c,(int)*psVar3,local_408,0x3ff);
      iVar2 = FUN_0049eb44(DAT_004b7ce4,0xd,1,0x26,0xffffffff,local_408);
      FUN_0049eb44(DAT_004b7ce4,0xd,1,0x25,iVar2 + -1,iVar1);
      if (psVar3 == param_2) {
        local_8 = iVar1;
      }
    }
    FUN_0049eb44(DAT_004b7ce4,0xc,1,0x31,0xd,1);
    if ((param_2 != (short *)0x0) && (-1 < local_8)) {
      DAT_004b7d08 = 1;
      FUN_0049eb44(DAT_004b7ce4,0xd,1,0x1b,local_8,0);
      FUN_0049eb44(DAT_004b7ce4,0xd,1,0x21,local_8,0);
      DAT_004b7d08 = 0;
    }
    if ((param_2 == (short *)0x0) || (local_8 < 0)) {
      iVar1 = *(int *)(param_1 + 0x16);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x16) + local_8 * 0x24;
    }
    FUN_0049eb44(DAT_004b7ce4,8,1,10,(*(byte *)(iVar1 + 0x14) & 0x10) == 0,0);
    FUN_0049eb44(DAT_004b7ce4,9,1,10,(*(byte *)(iVar1 + 0x14) & 8) == 0,0);
    FUN_0049eb44(DAT_004b7ce4,7,1,10,(*(byte *)(iVar1 + 0x14) & 2) == 0,0);
    FUN_0049eb44(DAT_004b7ce4,6,1,10,(*(byte *)(param_1 + 0x14) & 4) == 0,0);
  }
  return;
}

