// FUN_00411ab0 @ 00411ab0 size=43 sig=undefined FUN_00411ab0() cc=unknown
// callers: OpenDataFiles
// callees: FUN_00411808,FUN_00411adc

undefined4 FUN_00411ab0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_8 [4];
  
  iVar1 = FUN_00411adc(param_1,param_2,local_8);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00411808(param_1,iVar1);
  }
  return uVar2;
}

