// FUN_004a0e79 @ 004a0e79 size=119 sig=undefined FUN_004a0e79() cc=unknown
// callers: FUN_0043b040,FUN_0043aed0,FUN_004a43da,FUN_004a0f18
// callees: FUN_004a03cf,FUN_004a016e,FUN_004a060f,FUN_004a034a,FUN_0049e47a,FUN_004a08c5,FUN_0049da81,FUN_0049c710

undefined4 FUN_004a0e79(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  switch(*(undefined4 *)(param_2 + 0x1c)) {
  case 0:
    uVar1 = FUN_004a016e(param_1,param_2);
    break;
  case 1:
    uVar1 = FUN_004a03cf(param_1,param_2);
    break;
  case 2:
    uVar1 = FUN_004a060f(param_1,param_2);
    break;
  case 3:
    uVar1 = FUN_004a034a(param_1,param_2);
    break;
  case 4:
    uVar1 = FUN_004a08c5(param_1,param_2);
    break;
  case 5:
    uVar1 = FUN_0049e47a(param_1,param_2);
    break;
  case 6:
    uVar1 = FUN_0049da81(param_1,param_2);
    break;
  default:
    uVar1 = 0;
    break;
  case 9:
    uVar1 = FUN_0049c710(param_1,param_2);
  }
  return uVar1;
}

