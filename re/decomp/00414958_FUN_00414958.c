// FUN_00414958 @ 00414958 size=161 sig=undefined FUN_00414958() cc=unknown
// callers: FUN_00414a30
// callees: FUN_00414f04,FUN_004a3de6,FUN_0049eb44,FUN_004a2004

int FUN_00414958(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = FUN_004a3de6(0,param_1);
  if (iVar1 != 0) {
    if (DAT_004d5978 != 0) {
      uVar2 = *(int *)(DAT_004d5c28 + 4) - *(int *)(iVar1 + 0x14);
      iVar3 = (int)uVar2 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
      }
      *(int *)(iVar1 + 8) = iVar3;
      if (iVar3 < 0) {
        *(undefined4 *)(iVar1 + 8) = 0;
      }
      uVar2 = *(int *)(DAT_004d5c28 + 8) - *(int *)(iVar1 + 0x10);
      iVar3 = (int)uVar2 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
      }
      *(int *)(iVar1 + 0xc) = iVar3;
      if (iVar3 < 0) {
        *(undefined4 *)(iVar1 + 0xc) = 0;
      }
    }
    FUN_00414f04(iVar1);
    FUN_004a2004(iVar1);
    FUN_0049eb44(iVar1,0x3e9,1,0xf,0,param_2);
    FUN_0049eb44(iVar1,0x3ea,1,0xf,0,param_3);
  }
  return iVar1;
}

