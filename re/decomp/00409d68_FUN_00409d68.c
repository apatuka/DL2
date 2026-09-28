// FUN_00409d68 @ 00409d68 size=52 sig=undefined FUN_00409d68() cc=unknown
// callers: FUN_00409f6c
// callees: FUN_0046b074

undefined4 FUN_00409d68(int param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  
  sVar1 = *(short *)(param_1 + 0x30);
  if (sVar1 != 0) {
    uVar2 = FUN_0046b074(param_1);
    iVar3 = (int)uVar2 >> 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
    }
    if (sVar1 < iVar3) {
      return 0;
    }
  }
  return 1;
}

