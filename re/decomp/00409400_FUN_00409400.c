// FUN_00409400 @ 00409400 size=114 sig=undefined FUN_00409400() cc=unknown
// callers: FUN_004094d8
// callees: FUN_0044d0ac,FUN_0044d1a4

undefined4 FUN_00409400(byte param_1,int param_2)

{
  int iVar1;
  
  if ((*(char *)(param_2 + 0x21) == '\0') && (iVar1 = FUN_0044d1a4(param_2,0x14,0), iVar1 != -1)) {
    if (((1 << (param_1 & 0x1f) & (int)DAT_004fc250) != 0) &&
       (iVar1 = FUN_0044d0ac(param_2,0x2b), iVar1 < 1)) {
      return 0x2b;
    }
    if (((1 << (param_1 & 0x1f) & (int)DAT_004fc3e0) != 0) &&
       (iVar1 = FUN_0044d0ac(param_2,0x2c), iVar1 < 1)) {
      return 0x2c;
    }
  }
  return 0;
}

