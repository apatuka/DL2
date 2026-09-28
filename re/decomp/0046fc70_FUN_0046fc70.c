// FUN_0046fc70 @ 0046fc70 size=51 sig=undefined FUN_0046fc70() cc=unknown
// callers: InitCYGame
// callees: FUN_0049539b,FUN_00490bca
// strings: \"Unable to load needed CAM, %s\"

undefined4 FUN_0046fc70(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00490bca(param_1);
  if (iVar1 == 0) {
    if (param_2 != 0) {
      FUN_0049539b(s_Unable_to_load_needed_CAM___s_004d5d68,param_1);
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

