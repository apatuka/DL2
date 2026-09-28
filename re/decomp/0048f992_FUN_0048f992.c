// FUN_0048f992 @ 0048f992 size=256 sig=undefined FUN_0048f992() cc=unknown
// callers: FUN_0048fcc3,FUN_00497bea,FUN_004a65e0,FUN_00497d40,FUN_0048fd19,FUN_0048fcf8,FUN_00497eea,FUN_0049164f,FUN_004995ab,FUN_0048fcde,FUN_00497fa4,FUN_00491200,FUN_0048fc05,FUN_00497b55,FUN_0049b6a0,FUN_0048fd38,FUN_004911cc,FUN_004a4e8e,FUN_00498196,FUN_00497c92,FUN_0048a145,FUN_004917e6
// callees: FUN_0048f7f1,FUN_00488ba3

uint FUN_0048f992(int *param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint local_8;
  
  if ((param_1[2] == 1) || (param_1[2] == 2)) {
    if (param_1[6] == 0) {
      param_3 = FUN_00488ba3(*param_1,param_2,param_3);
      if ((int)param_3 < 0) {
        param_1[1] = param_3;
      }
    }
    else {
      local_8 = 0;
      uVar1 = local_8;
      uVar2 = param_3;
      while (param_3 = uVar1, uVar2 != 0) {
        if (param_1[3] == 0) {
          if (0x2000 < uVar2) {
            uVar2 = FUN_00488ba3(*param_1,param_2,uVar2);
            if ((int)uVar2 < 0) {
              param_1[1] = uVar2;
              return uVar2;
            }
            return uVar2 + param_3;
          }
          uVar1 = FUN_00488ba3(*param_1,param_1[6],0x2000);
          if ((int)uVar1 < 1) {
            if (uVar1 == 0) {
              return param_3;
            }
            param_1[1] = uVar1;
            return uVar1;
          }
          param_1[7] = param_1[6];
          param_1[3] = uVar1;
          uVar1 = param_3;
        }
        else {
          uVar1 = uVar2;
          if ((uint)param_1[3] < uVar2) {
            uVar1 = param_1[3];
          }
          FUN_0048f7f1(param_1[7],param_2,uVar1);
          uVar2 = uVar2 - uVar1;
          param_1[3] = param_1[3] - uVar1;
          param_2 = param_2 + uVar1;
          param_1[7] = param_1[7] + uVar1;
          uVar1 = param_3 + uVar1;
        }
      }
    }
  }
  else {
    FUN_0048f7f1(*param_1 + param_1[3],param_2,param_3);
    param_1[3] = param_1[3] + param_3;
  }
  return param_3;
}

