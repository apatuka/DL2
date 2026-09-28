// FUN_00454eec @ 00454eec size=427 sig=undefined FUN_00454eec() cc=unknown
// callers: FUN_004556b0
// callees: FUN_00450f84

void FUN_00454eec(int param_1,uint param_2,uint param_3)

{
  char cVar1;
  int iVar2;
  uint local_8;
  
  if (0x15 < param_2) {
    param_2 = 9;
  }
  if (0x12 < param_3) {
    param_3 = 9;
  }
  param_2 = param_2 - *(int *)(param_1 + 0x20);
  param_3 = param_3 - *(int *)(param_1 + 0x24);
  iVar2 = FUN_00450f84(param_1);
  if (iVar2 != 0) {
    cVar1 = *(char *)(param_1 + 0x14);
    if (cVar1 == '\x01') {
LAB_00454f45:
      param_2 = 0;
    }
    else {
      if (cVar1 != '\x02') {
        if (cVar1 == '\x04') goto LAB_00454f45;
        if (cVar1 != '\b') goto LAB_00454f47;
      }
      param_3 = 0;
    }
  }
LAB_00454f47:
  local_8 = 0;
  if ((int)param_2 < 1) {
    if ((int)param_2 < 0) {
      local_8 = 8;
    }
  }
  else {
    local_8 = 2;
  }
  if ((int)param_3 < 0) {
    local_8 = local_8 | 1;
  }
  else if (0 < (int)param_3) {
    local_8 = local_8 | 4;
  }
  if (1 < (int)(((param_2 ^ (int)param_2 >> 0x1f) - ((int)param_2 >> 0x1f)) +
               ((param_3 ^ (int)param_3 >> 0x1f) - ((int)param_3 >> 0x1f)))) {
    *(undefined *)(param_1 + 0x30) =
         (&DAT_004d0144)[local_8 + (uint)*(byte *)(param_1 + 0x30) * 0xd];
  }
  if (DAT_0057e248 == 3) {
    iVar2 = *(int *)(DAT_0057cdf8 + 0x74);
    while( true ) {
      if ((iVar2 == 0) || (param_1 == iVar2)) goto LAB_0045500f;
      if (((*(char *)(iVar2 + 0x1d) != '\0') &&
          (((*(int *)(iVar2 + 4) == *(int *)(param_1 + 4) &&
            (*(int *)(iVar2 + 0x28) == *(int *)(param_1 + 0x20))) &&
           (*(int *)(iVar2 + 0x2c) == *(int *)(param_1 + 0x24))))) &&
         (*(char *)(iVar2 + 0x30) == *(char *)(param_1 + 0x30))) break;
      iVar2 = *(int *)(iVar2 + 0x44);
    }
    *(undefined *)(param_1 + 0x30) = (&DAT_004d02a2)[*(byte *)(param_1 + 0x30)];
  }
LAB_0045500f:
  if ((*(byte *)(param_1 + 0x30) & 2) == 0) {
    if ((*(byte *)(param_1 + 0x30) & 8) != 0) {
      *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + -1;
    }
  }
  else {
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  }
  if ((*(byte *)(param_1 + 0x30) & 1) == 0) {
    if ((*(byte *)(param_1 + 0x30) & 4) != 0) {
      *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 1;
    }
  }
  else {
    *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + -1;
  }
  iVar2 = FUN_00450f84(param_1);
  if (iVar2 == 0) {
    return;
  }
  cVar1 = *(char *)(param_1 + 0x14);
  if (cVar1 == '\x01') {
LAB_00455073:
    if (*(int *)(param_1 + 0x20) < 0) {
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
    if (0x12 < *(int *)(param_1 + 0x20)) {
      *(undefined4 *)(param_1 + 0x20) = 0x12;
    }
  }
  else {
    if (cVar1 != '\x02') {
      if (cVar1 == '\x04') goto LAB_00455073;
      if (cVar1 != '\b') {
        return;
      }
    }
    if (*(int *)(param_1 + 0x24) < 0) {
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    if (0x12 < *(int *)(param_1 + 0x24)) {
      *(undefined4 *)(param_1 + 0x24) = 0x12;
    }
  }
  return;
}

