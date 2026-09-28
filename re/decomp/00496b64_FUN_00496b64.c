// FUN_00496b64 @ 00496b64 size=74 sig=undefined FUN_00496b64() cc=unknown
// callers: FUN_00496c03
// callees: FUN_00496a97

int FUN_00496b64(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  
  iVar1 = FUN_00496a97(param_1,param_2,param_3);
  if (((iVar1 == 0) || ((int)(uint)*(ushort *)(iVar1 + 0x1e) <= param_5)) ||
     ((int)(uint)*(ushort *)(iVar1 + 0x1c) <= param_4)) {
    iVar1 = 0;
  }
  else {
    iVar1 = (uint)*(ushort *)(iVar1 + 0x1e) * 8 * param_4 + iVar1 + param_5 * 8 + 0x20;
  }
  return iVar1;
}

