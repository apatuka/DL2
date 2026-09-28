// FUN_00402d58 @ 00402d58 size=155 sig=undefined FUN_00402d58() cc=unknown
// callers: FUN_00407e78
// callees: FUN_00402548,FUN_0047597c

undefined4 FUN_00402d58(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int local_18;
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  uVar3 = 0;
  local_c = -1000000;
  if (param_2 == 0) {
    piVar2 = &DAT_00521bb4;
    param_2 = 0;
    do {
      local_14 = *piVar2;
      iVar1 = FUN_00402548(local_14,param_3,param_4,&local_18,local_10);
      if ((local_18 != -1) && (local_c < iVar1)) {
        local_8 = local_18;
        param_2 = local_14;
        local_c = iVar1;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != &DAT_00521bb4);
  }
  else {
    FUN_00402548(param_2,param_3,param_4,&local_8,local_10);
  }
  if (param_2 != 0) {
    uVar3 = FUN_0047597c(param_2,param_3,local_8);
  }
  return uVar3;
}

