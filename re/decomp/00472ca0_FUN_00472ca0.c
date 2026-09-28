// FUN_00472ca0 @ 00472ca0 size=183 sig=undefined FUN_00472ca0() cc=unknown
// callers: WriteUnitData,SetItemStats,FUN_00408310,FUN_00471e58,FUN_00407e78,FUN_0041026c
// callees: FUN_00472018,FUN_00471bec,FUN_00471fec,FUN_00472974

int FUN_00472ca0(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  local_8 = 0;
  FUN_00471bec();
  iVar2 = 1;
  piVar3 = (int *)(param_1 + 0x3e);
  do {
    param_2 = param_2 + 1;
    local_c = 0;
    if (iVar2 == 4) {
      iVar1 = FUN_00471fec(param_1);
      if ((0 < *param_2 - iVar1) &&
         (local_c = FUN_00472018(param_1,*param_2 - iVar1,0), local_c == -1)) {
        return -1;
      }
    }
    else if ((*piVar3 < *param_2) &&
            (local_c = FUN_00472974(param_1,(int)*(char *)(param_1 + 0x20),iVar2,*param_2 - *piVar3,
                                    0,local_10,local_10), local_c == -1)) {
      return -1;
    }
    local_8 = local_8 + local_c;
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
    if (10 < iVar2) {
      return local_8;
    }
  } while( true );
}

