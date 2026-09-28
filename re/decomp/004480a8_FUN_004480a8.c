// FUN_004480a8 @ 004480a8 size=112 sig=undefined FUN_004480a8() cc=unknown
// callers: FUN_004556b0,FUN_00451410,FUN_00453954,FUN_00455c88,FUN_00454928,FUN_00447b78,FUN_00453a38,FUN_00453d9c,FUN_00455a04
// callees: FUN_004482cc,FUN_00448210,FUN_004481a4

int FUN_004480a8(int param_1)

{
  int iVar1;
  int *piVar2;
  int local_c;
  int local_8;
  
  iVar1 = FUN_004482cc(param_1);
  if (iVar1 == 0) {
    local_8 = FUN_00448210(param_1);
    if (local_8 == 0) {
      local_8 = (int)(char)(&DAT_004faf93)[*(int *)(param_1 + 4) * 0x24];
    }
    iVar1 = FUN_004481a4(param_1);
    if (iVar1 != 0) {
      local_8 = local_8 * local_8;
    }
    local_c = 0;
    if (local_8 < 0) {
      piVar2 = &local_c;
    }
    else {
      piVar2 = &local_8;
    }
    iVar1 = *piVar2;
  }
  else {
    iVar1 = 2;
  }
  return iVar1;
}

