// FUN_0049331e @ 0049331e size=450 sig=undefined FUN_0049331e() cc=unknown
// callers: FUN_0049e3d7
// callees: FUN_00493149,FUN_00492b0c,FUN_00492290,FUN_00492b47,FUN_00491b5e

undefined4 FUN_0049331e(int *param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined1 local_24 [4];
  short local_20;
  short local_1e;
  short local_1a;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_00491b5e(local_24);
  if ((((param_1 == (int *)0x0) || (param_2 < param_1[1])) || (param_1[3] <= param_2)) ||
     ((param_3 < param_1[2] || (param_1[4] <= param_3)))) {
    return 0;
  }
  local_14 = param_1[3] - param_1[1];
  iVar1 = param_1[1];
  iVar5 = param_1[2];
  if ((*(byte *)(param_1 + 5) & 8) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_00493149(*param_1,local_14,0,0);
    uVar3 = (param_1[4] - param_1[2]) - iVar2 * ((int)local_20 + (int)local_1e + (int)local_1a);
    iVar2 = (int)uVar3 >> 1;
    if (iVar2 < 0) {
      iVar2 = iVar2 + (uint)((uVar3 & 1) != 0);
    }
    if (iVar2 < 0) {
      iVar2 = 0;
    }
  }
  local_10 = 0;
  local_18 = 0;
  if (*param_1 != 0) {
    pcVar6 = (char *)*param_1;
    while (*pcVar6 != '\0') {
      FUN_00492b47(pcVar6,local_14,0xffffffff,&local_c,&local_8,0,&local_10);
      if ((iVar2 <= param_3 - iVar5) && (param_3 - iVar5 < local_20 + iVar2 + (int)local_1e)) {
        if ((*(byte *)(param_1 + 5) & 1) == 0) {
          iVar5 = local_10;
          if ((*(byte *)(param_1 + 5) & 0x20) != 0) {
            iVar5 = (local_14 + local_10) - local_8;
          }
        }
        else {
          iVar5 = ((local_14 - local_10) - local_8 >> 1) + local_10;
        }
        iVar2 = 0;
        if (0 < local_c) {
          do {
            if (*pcVar6 == '\t') {
              iVar4 = (iVar5 / DAT_0051dc18) * DAT_0051dc18 + DAT_0051dc18;
            }
            else {
              iVar4 = FUN_00492290((int)*pcVar6);
            }
            if ((iVar5 <= param_2 - iVar1) && (param_2 - iVar1 < iVar4 + iVar5)) {
              *param_4 = iVar2 + local_18;
              return 1;
            }
            iVar5 = iVar5 + iVar4;
            iVar2 = iVar2 + 1;
            pcVar6 = pcVar6 + 1;
          } while (iVar2 < local_c);
        }
        *param_4 = iVar2 + local_18;
        return 1;
      }
      iVar2 = iVar2 + (int)local_20 + (int)local_1e;
      pcVar6 = (char *)FUN_00492b0c(pcVar6 + local_c);
      local_18 = (int)pcVar6 - *param_1;
    }
  }
  *param_4 = local_18;
  return 1;
}

