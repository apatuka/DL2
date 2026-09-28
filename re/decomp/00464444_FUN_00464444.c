// FUN_00464444 @ 00464444 size=82 sig=undefined FUN_00464444() cc=unknown
// callers: FUN_0047f23c,FUN_00440694,FUN_0047f1d8,FUN_00481da0
// callees: FUN_0049b3c9,FUN_00493b24

void FUN_00464444(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 uVar1;
  
  if (*(int *)(DAT_0051bddc + 0xc) == 8) {
    FUN_00493b24(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    uVar1 = FUN_0049b3c9(DAT_0058df44,param_5);
    FUN_00493b24(param_1,param_2,param_3,param_4,uVar1);
  }
  return;
}

