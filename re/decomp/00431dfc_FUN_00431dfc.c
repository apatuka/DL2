// FUN_00431dfc @ 00431dfc size=92 sig=undefined FUN_00431dfc() cc=unknown
// callers: 
// callees: FUN_004a43da,FUN_0049eb44,FUN_00431734

undefined4 FUN_00431dfc(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  
  if (param_2 == 0x3b) {
    FUN_004a43da(param_1,0x3b,param_3,param_4);
    if (param_4 != 0) {
      DAT_004c4508 = FUN_0049eb44(DAT_004c42e0,0xe,1,0x22,0,0);
      FUN_00431734(DAT_004c4508);
    }
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

