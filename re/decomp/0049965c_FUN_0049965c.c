// FUN_0049965c @ 0049965c size=72 sig=undefined FUN_0049965c() cc=unknown
// callers: 
// callees: FUN_00498a30,FUN_00493522

int FUN_0049965c(undefined4 param_1,undefined4 param_2,short param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if ((param_3 == 0) && (param_3 = FUN_00493522(param_1), param_3 == 0)) {
    iVar1 = 0;
  }
  else {
    switch(param_3) {
    case 1:
      iVar1 = FUN_0049b6a0(param_1,param_2);
      break;
    case 2:
      iVar1 = FUN_004995ab(param_1,param_2);
      break;
    case 3:
      iVar1 = FUN_004995ab(param_1,param_2);
      break;
    case 4:
      iVar1 = FUN_00498196(param_1,param_2);
      break;
    case 5:
      iVar1 = FUN_00499227(param_1,param_2);
    }
    if (iVar1 != 0) {
      FUN_00498a30(iVar1,0);
    }
  }
  return iVar1;
}

