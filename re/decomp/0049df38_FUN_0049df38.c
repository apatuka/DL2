// FUN_0049df38 @ 0049df38 size=207 sig=undefined FUN_0049df38() cc=unknown
// callers: FUN_0049edb2
// callees: strlen,FUN_0049eb44,FUN_0049ddf8

undefined4 FUN_0049df38(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if ((((*(int *)(param_2 + 0x1c) == 5) && ((*(byte *)(param_2 + 0x24) & 0x80) != 0)) &&
      (piVar1 = (int *)FUN_0049ddf8(param_2), piVar1 != (int *)0x0)) && (*piVar1 != 0)) {
    iVar2 = strlen(*piVar1);
    if ((param_5 == 0) || (param_5 == 5)) {
      iVar3 = iVar2;
      if (param_3 < iVar2) {
        iVar3 = param_3;
      }
      if (iVar3 < 1) {
        iVar3 = 0;
      }
      else {
        iVar3 = iVar2;
        if (param_3 < iVar2) {
          iVar3 = param_3;
        }
      }
      piVar1[6] = iVar3;
      iVar3 = iVar2;
      if (param_4 < iVar2) {
        iVar3 = param_4;
      }
      if (iVar3 < 1) {
        iVar2 = 0;
      }
      else if (param_4 < iVar2) {
        iVar2 = param_4;
      }
      piVar1[7] = iVar2;
    }
    else if (param_5 == 3) {
      piVar1[6] = iVar2;
      piVar1[7] = iVar2;
    }
    else {
      if (param_5 != 4) {
        return 1;
      }
      piVar1[6] = 0;
      piVar1[7] = iVar2;
    }
    FUN_0049eb44(param_1,param_2,2,8,0,0);
  }
  return 0;
}

