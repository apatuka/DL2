// FUN_0040c3b8 @ 0040c3b8 size=283 sig=undefined FUN_0040c3b8() cc=unknown
// callers: FUN_0040c8c8,FUN_00410164,FUN_0040febc,FUN_0040b994,FUN_0040f2e0,FUN_0040b968,FUN_0040f478
// callees: FUN_00401108,FUN_0040c260

longlong FUN_0040c3b8(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  FUN_0040c260(param_1,&local_10,&local_14,&local_18,&local_1c);
  iVar3 = 0;
  piVar2 = param_1 + 0x11;
  do {
    iVar1 = *piVar2;
    if ((iVar1 != 0) &&
       ((*param_1 != 9 || ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] != '\x01')))) {
      iVar1 = FUN_00401108(iVar1,local_10,local_14,local_18,local_1c);
      local_c = local_c + iVar1;
      local_8 = local_8 + 1;
    }
    iVar3 = iVar3 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar3 < 0x10);
  local_20 = 1;
  local_24 = param_1 + 0x22;
  do {
    if (*local_24 != 0) {
      iVar3 = 0;
      piVar2 = (int *)(&DAT_00522504 + *(short *)((int)param_1 + 10) * 0x2648 + *local_24 * 0xc4);
      do {
        iVar1 = *piVar2;
        if ((iVar1 != 0) && ((&DAT_004faf8d)[*(char *)(iVar1 + 6) * 0x24] == '\x01')) {
          iVar1 = FUN_00401108(iVar1,local_10,local_14,local_18,local_1c);
          local_c = local_c + iVar1;
          local_8 = local_8 + 1;
        }
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar3 < 0x10);
    }
    local_20 = local_20 + 1;
    local_24 = local_24 + 1;
  } while (local_20 < 0x10);
  return (longlong)local_c * (longlong)local_8;
}

