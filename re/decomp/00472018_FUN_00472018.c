// FUN_00472018 @ 00472018 size=219 sig=undefined FUN_00472018() cc=unknown
// callers: FUN_00472ca0,FUN_004720f4
// callees: FUN_00472974

int FUN_00472018(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_14 = 0;
  piVar3 = &DAT_004d6344;
  local_24 = &DAT_004d6334;
  for (; (local_14 < 4 && (0 < param_2)); param_2 = param_2 - local_18 * iVar1) {
    iVar1 = *local_24;
    local_18 = (*piVar3 + param_2 + -1) / *piVar3;
    local_1c = *(int *)(param_1 + 0x3a + iVar1 * 4);
    if (0 < local_18) {
      FUN_00472974(param_1,(int)*(char *)(param_1 + 0x20),iVar1,local_18,param_3,&local_10,&local_c)
      ;
    }
    if (param_3 == 0) {
      local_18 = local_18 - local_10;
      local_8 = local_8 + local_c;
    }
    else {
      local_20 = *(int *)(param_1 + 0x3a + iVar1 * 4) - local_1c;
      if (local_20 < local_18) {
        piVar2 = &local_20;
      }
      else {
        piVar2 = &local_18;
      }
      local_18 = *piVar2;
    }
    iVar1 = *piVar3;
    local_14 = local_14 + 1;
    piVar3 = piVar3 + 1;
    local_24 = local_24 + 1;
  }
  if (0 < param_2) {
    local_8 = -1;
  }
  return local_8;
}

