// FUN_004316d8 @ 004316d8 size=91 sig=undefined FUN_004316d8() cc=unknown
// callers: 
// callees: FUN_004a43da,FUN_0049eb44,FUN_00431534

undefined4 FUN_004316d8(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0x3b) {
    FUN_004a43da(param_1,0x3b,param_3,param_4);
    if (param_4 != 0) {
      iVar1 = FUN_0049eb44(DAT_004c42dc,0x14,1,0x22,0,0);
      FUN_00431534((&DAT_00558de0)[iVar1 * 2]);
    }
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar2;
}

