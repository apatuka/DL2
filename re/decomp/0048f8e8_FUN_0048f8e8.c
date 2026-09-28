// FUN_0048f8e8 @ 0048f8e8 size=170 sig=undefined FUN_0048f8e8() cc=unknown
// callers: FUN_0049b6a0,FUN_004a65e0,FUN_00498196,FUN_00499227,FUN_0049164f,FUN_004995ab,FUN_00498f8c,FUN_00497fa4,FUN_004a4ffe,FUN_0048fc05
// callees: FUN_0048f774,FUN_00498ba9,FUN_004989cf,FUN_004888ec,FUN_00488c95

int * FUN_0048f8e8(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_00498ba9(0x20);
  if (piVar1 != (int *)0x0) {
    FUN_0048f774(piVar1,0x20,0);
    piVar1[4] = 0x7fffffff;
    if (param_2 == 4) {
      param_2 = *param_1;
      piVar1[4] = param_1[2];
      param_1 = (int *)param_1[1];
    }
    if (param_2 == 1) {
      iVar2 = FUN_004888ec(param_1,0);
      if (iVar2 == -1) {
        FUN_004989cf(piVar1);
        return (int *)0x0;
      }
      *piVar1 = iVar2;
      iVar2 = FUN_00498ba9(0x2000);
      piVar1[6] = iVar2;
    }
    else if (param_2 == 2) {
      *piVar1 = (int)param_1;
      iVar2 = FUN_00498ba9(0x2000);
      piVar1[6] = iVar2;
      iVar2 = FUN_00488c95(*piVar1,0,1);
      piVar1[5] = iVar2;
    }
    else if (param_2 == 3) {
      *piVar1 = (int)param_1;
    }
    piVar1[2] = param_2;
  }
  return piVar1;
}

