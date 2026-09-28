// FUN_00448008 @ 00448008 size=159 sig=undefined FUN_00448008() cc=unknown
// callers: FUN_00455c88,FUN_00447b9c,FUN_00456054,FUN_00451b68,FUN_00456e44
// callees: FUN_00448210,FUN_00447f1c,FUN_004481a4

int FUN_00448008(int param_1)

{
  int iVar1;
  int *piVar2;
  int local_14 [3];
  int local_8;
  
  local_8 = (int)(char)(&DAT_004faf92)[*(int *)(param_1 + 4) * 0x24];
  iVar1 = FUN_00448210(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_004481a4(param_1);
    if (iVar1 == 0) goto LAB_0044803f;
  }
  local_8 = local_8 * 2;
LAB_0044803f:
  iVar1 = FUN_00447f1c(param_1);
  if (iVar1 != 0) {
    local_14[2] = (local_8 * 10) / 100;
    local_14[1] = 1;
    if (local_14[2] < 1) {
      piVar2 = local_14 + 1;
    }
    else {
      piVar2 = local_14 + 2;
    }
    local_8 = local_8 - *piVar2;
  }
  if (*(char *)(param_1 + 9) == '\x04') {
    local_8 = local_8 + 1;
  }
  local_14[0] = -1;
  if (local_8 < -1) {
    piVar2 = local_14;
  }
  else {
    piVar2 = &local_8;
  }
  return *piVar2;
}

