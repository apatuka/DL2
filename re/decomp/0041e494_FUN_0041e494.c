// FUN_0041e494 @ 0041e494 size=60 sig=undefined FUN_0041e494() cc=unknown
// callers: 
// callees: FUN_00464cbc,FUN_004593a4

void FUN_0041e494(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if ((0 < param_2) && (param_2 < 0x27)) {
    uVar1 = FUN_004593a4((int)(char)*PTR_DAT_004d5988,param_2);
    FUN_00464cbc(param_1,*(undefined4 *)(param_1 + 0x10),uVar1,param_3,0x20,0x20,1);
  }
  return;
}

