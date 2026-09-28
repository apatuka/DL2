// FUN_00409364 @ 00409364 size=156 sig=undefined FUN_00409364() cc=unknown
// callers: FUN_004096a8
// callees: FUN_004092ec

undefined4 FUN_00409364(byte param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  if (*(char *)(param_2 + 0x21) == '\0') {
    if (((1 << (param_1 & 0x1f) & (int)DAT_004fbcd8) != 0) &&
       (iVar1 = FUN_004092ec(param_2), iVar1 != 0)) {
      return 0x1e;
    }
    uVar2 = 0x28;
  }
  else if ((1 << (param_1 & 0x1f) & (int)DAT_004fc2e6) == 0) {
    uVar3 = 1 << (param_1 & 0x1f);
    if (((uVar3 & (int)DAT_004fbcd8) != 0) && (iVar1 = FUN_004092ec(param_2), iVar1 != 0)) {
      return 0x1e;
    }
    if ((uVar3 & (int)DAT_004fc08e) == 0) {
      uVar2 = 0x1d;
    }
    else {
      uVar2 = 0x1f;
    }
  }
  else {
    uVar2 = 0x20;
  }
  return uVar2;
}

