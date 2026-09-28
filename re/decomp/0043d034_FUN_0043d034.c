// FUN_0043d034 @ 0043d034 size=335 sig=undefined FUN_0043d034() cc=unknown
// callers: FUN_0043d184
// callees: 

int FUN_0043d034(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int local_1c [3];
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8;
  
  local_10 = DAT_004c4958;
  local_c = DAT_004c495c;
  local_8 = DAT_004c4960;
  if ((&DAT_004faf8d)[*(int *)(param_1 + 4) * 0x24] == '\x03') {
    iVar2 = 0x7533;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x20);
    iVar1 = *(int *)(param_1 + 0x24);
    if (iVar2 < 0x12) {
      local_1c[2] = (iVar1 / 3) * 6 + iVar2 / 3;
      local_1c[1] = 0;
      if (local_1c[2] < 0) {
        piVar3 = local_1c + 1;
      }
      else {
        piVar3 = local_1c + 2;
      }
      local_1c[0] = 0x23;
      if (0x23 < *piVar3) {
        piVar3 = local_1c;
      }
      local_1c[2] = *piVar3;
      if ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\n') {
        iVar2 = *(int *)(&DAT_004dcc2c + *piVar3 * 4) * 100 + 0x4b;
      }
      else {
        iVar2 = *(int *)(&DAT_004dcc2c + *piVar3 * 4) * 100 + 0x3c +
                (uint)*(byte *)((int)&local_10 + iVar1 % 3 + (iVar2 % 3) * 3);
      }
    }
    else {
      iVar2 = (iVar1 / 3 + DAT_004dccb8) * 100 + 0xa0 +
              (uint)*(byte *)((int)&local_10 + iVar1 % 3 + (iVar2 % 3) * 3);
    }
  }
  return iVar2;
}

