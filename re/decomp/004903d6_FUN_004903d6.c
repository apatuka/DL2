// FUN_004903d6 @ 004903d6 size=233 sig=undefined FUN_004903d6() cc=unknown
// callers: 
// callees: FUN_0048f7f1,FUN_00490384

undefined4 FUN_004903d6(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int *piVar1;
  short *psVar2;
  int iVar3;
  int local_c;
  
  local_c = 0;
  if (DAT_0051daf8 == (short *)0x0) {
    return 0;
  }
  if (param_1 == 0) {
    psVar2 = DAT_0051daf8 + 2;
    for (iVar3 = (int)*DAT_0051daf8; 0 < iVar3; iVar3 = iVar3 + -1) {
      if ((*(undefined4 **)(psVar2 + 1) != (undefined4 *)0x0) &&
         (piVar1 = (int *)FUN_00490384(**(undefined4 **)(psVar2 + 1),param_2), piVar1 != (int *)0x0)
         ) {
        if (param_3 < *piVar1 + local_c) {
          if (param_4 != 0) {
            FUN_0048f7f1(piVar1 + param_3 * 10 + 2,param_4,0x14);
          }
          return 1;
        }
        local_c = local_c + *piVar1;
      }
      psVar2 = psVar2 + 0x85;
    }
  }
  else {
    piVar1 = (int *)FUN_00490384(param_1,param_2);
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    if (param_3 < *piVar1) {
      if (param_4 != 0) {
        FUN_0048f7f1(piVar1 + param_3 * 10 + 2,param_4,0x14);
      }
      return 1;
    }
  }
  return 0;
}

