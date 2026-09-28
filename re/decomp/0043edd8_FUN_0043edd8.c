// FUN_0043edd8 @ 0043edd8 size=101 sig=undefined FUN_0043edd8() cc=unknown
// callers: FUN_0045ca3c,FUN_0045d89c,FUN_0045c27c,FUN_0045dc48,FUN_0045cff4,FUN_0045c704,FUN_00481da0,FUN_00458f14,FUN_0045d984,FUN_0045dd18
// callees: 

void FUN_0043edd8(int param_1,int param_2,int *param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = DAT_004c4a58 * 0x20 + param_1;
  param_2 = DAT_004c4a5c * 0x20 + param_2;
  iVar2 = (int)uVar1 >> 1;
  if (iVar2 < 0) {
    iVar2 = iVar2 + (uint)((uVar1 & 1) != 0);
  }
  iVar3 = iVar2 + param_2;
  iVar4 = iVar3 + 0x500;
  if (iVar4 < 0) {
    iVar4 = iVar3 + 0x51f;
  }
  iVar2 = (param_2 + 0x500) - iVar2;
  *param_3 = (iVar4 >> 5) + -0x28;
  if (iVar2 < 0) {
    iVar2 = iVar2 + 0x1f;
  }
  *param_4 = (iVar2 >> 5) + -0x28;
  return;
}

