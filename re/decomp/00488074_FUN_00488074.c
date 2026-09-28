// FUN_00488074 @ 00488074 size=105 sig=undefined FUN_00488074() cc=unknown
// callers: FUN_00487a00,FUN_0043611c,LoadPrefsAndInit
// callees: FUN_0048796c,MessagePump,FUN_00487e34,FUN_004879b0

undefined4 FUN_00488074(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  DAT_004d59a0 = 1;
  iVar1 = FUN_00487e34(param_1,0,param_2,1,param_3,0,param_4);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    while (((DAT_0058f1f0 == 0 && (DAT_004d59a0 != 0)) && (iVar1 = FUN_0048796c(), iVar1 != 0))) {
      FUN_004879b0();
      MessagePump();
    }
    DAT_004d59a0 = 0;
    uVar2 = 1;
  }
  return uVar2;
}

