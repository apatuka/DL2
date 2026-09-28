// FUN_00447f44 @ 00447f44 size=195 sig=undefined FUN_00447f44() cc=unknown
// callers: FUN_004556b0,FUN_00447b54,FUN_00451b68,FUN_00456e44
// callees: FUN_004482cc,FUN_00447f1c

int FUN_00447f44(int param_1)

{
  int iVar1;
  int *piVar2;
  int local_14 [3];
  int local_8;
  
  local_8 = (int)(char)(&DAT_004faf91)[*(int *)(param_1 + 4) * 0x24] +
            (int)*(short *)(&DAT_0055a084 +
                           (char)(&DAT_0059f162)[(uint)*(byte *)(param_1 + 0x1e) * 0x2d8] * 2);
  if (*(char *)(param_1 + 9) == '\x04') {
    local_8 = local_8 * 2;
  }
  iVar1 = FUN_004482cc(param_1);
  if (iVar1 != 0) {
    local_8 = local_8 / 2;
  }
  iVar1 = FUN_00447f1c(param_1);
  if (iVar1 != 0) {
    local_14[2] = (local_8 * 0x19) / 100;
    local_14[1] = 1;
    if (local_14[2] < 1) {
      piVar2 = local_14 + 1;
    }
    else {
      piVar2 = local_14 + 2;
    }
    local_8 = local_8 - *piVar2;
  }
  local_14[0] = 0;
  if (local_8 < 0) {
    piVar2 = local_14;
  }
  else {
    piVar2 = &local_8;
  }
  return *piVar2;
}

