// FUN_00496bae @ 00496bae size=85 sig=undefined FUN_00496bae() cc=unknown
// callers: 
// callees: FUN_00496a97

int FUN_00496bae(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                int *param_6)

{
  int iVar1;
  
  iVar1 = FUN_00496a97(param_1,param_2,param_3);
  if (((iVar1 == 0) || ((int)(uint)*(ushort *)(iVar1 + 0x1e) <= param_5)) ||
     ((int)(uint)*(ushort *)(iVar1 + 0x1c) <= param_4)) {
    iVar1 = 0;
  }
  else {
    if (param_6 != (int *)0x0) {
      *param_6 = iVar1;
    }
    iVar1 = (uint)*(ushort *)(iVar1 + 0x1e) * 8 * param_4 + iVar1 + param_5 * 8 + 0x20;
  }
  return iVar1;
}

