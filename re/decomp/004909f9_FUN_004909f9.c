// FUN_004909f9 @ 004909f9 size=186 sig=undefined FUN_004909f9() cc=unknown
// callers: 
// callees: FUN_004905e5

int FUN_004909f9(undefined4 *param_1,undefined4 param_2,int *param_3,int param_4,undefined4 *param_5
                )

{
  short *psVar1;
  int iVar2;
  int iVar3;
  
  if (param_4 == 2) {
    if (*param_3 == -1) {
      param_3 = param_3 + 1;
      param_4 = 1;
    }
    else {
      param_3 = (int *)*param_3;
      param_4 = 0;
    }
  }
  if (param_1 == (undefined4 *)0x0) {
    iVar3 = 0;
    if (DAT_0051daf8 != (short *)0x0) {
      psVar1 = DAT_0051daf8 + 2;
      for (iVar2 = (int)*DAT_0051daf8; 0 < iVar2; iVar2 = iVar2 + -1) {
        param_1 = *(undefined4 **)(psVar1 + 1);
        iVar3 = FUN_004905e5(*param_1,param_2,param_3,param_4);
        if (iVar3 != 0) break;
        psVar1 = psVar1 + 0x85;
      }
    }
    if (iVar3 == 0) {
      return 0;
    }
  }
  else {
    iVar3 = FUN_004905e5(*param_1,param_2,param_3,param_4);
    if (iVar3 == 0) {
      return 0;
    }
  }
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = param_1;
  }
  return iVar3;
}

