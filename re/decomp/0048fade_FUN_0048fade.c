// FUN_0048fade @ 0048fade size=116 sig=undefined FUN_0048fade() cc=unknown
// callers: FUN_00497bea,FUN_004a65e0,FUN_0048a53c,FUN_00499227,FUN_00497eea,FUN_00497fa4,FUN_00491200,FUN_00491748,FUN_0048fc05,FUN_004911cc,FUN_0048a8c3,FUN_00498196,FUN_00497c92,FUN_00498f8c,FUN_004917e6,FUN_004a4c92
// callees: FUN_00488c95,FUN_0048fa92,FUN_0048e656
// strings: \"..\\\\src\\\\bread.c\"

undefined4 FUN_0048fade(undefined4 *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1[2] == 1) || (param_1[2] == 2)) {
    if (param_3 == 1) {
      iVar1 = FUN_0048fa92(param_1);
      param_2 = param_2 + iVar1;
      param_3 = 0;
    }
    param_1[3] = 0;
    uVar2 = FUN_00488c95(*param_1,param_2,param_3);
  }
  else {
    if (param_3 == 1) {
      param_1[3] = param_1[3] + param_2;
    }
    else if (param_3 == 2) {
      if (param_1[3] == 0x7fffffff) {
        FUN_0048e656(0xcd,s____src_bread_c_0051d6e4);
      }
      param_1[3] = param_2 + param_1[4];
    }
    else {
      param_1[3] = param_2;
    }
    uVar2 = param_1[3];
  }
  return uVar2;
}

