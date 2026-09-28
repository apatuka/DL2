// FUN_00409270 @ 00409270 size=121 sig=undefined FUN_00409270() cc=unknown
// callers: FUN_004096a8,FUN_00402548
// callees: FUN_0044d034

int FUN_00409270(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int local_c;
  int local_8;
  
  iVar1 = *(int *)(&DAT_0052206c + param_1 * 4);
  if (iVar1 == -1) {
    local_8 = 1;
  }
  else if (iVar1 == 0) {
    local_8 = 2;
  }
  else if (iVar1 == 1) {
    local_8 = 3;
  }
  local_c = FUN_0044d034(param_2,0x12);
  if (local_c < local_8) {
    piVar2 = &local_8;
  }
  else {
    piVar2 = &local_c;
  }
  local_8 = *piVar2;
  if (*(int *)(param_2 + 0xa12) < *(int *)(param_2 + 0xa60)) {
    local_8 = local_8 + 1;
  }
  return local_8;
}

