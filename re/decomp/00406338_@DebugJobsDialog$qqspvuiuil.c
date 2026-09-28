// @DebugJobsDialog$qqspvuiuil @ 00406338 size=103 sig=undefined @DebugJobsDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_00405d54,FUN_00465540,FUN_004062b8,FUN_004655b0

undefined4
_DebugJobsDialog_qqspvuiuil(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
                    /* 0x6338  4  @DebugJobsDialog$qqspvuiuil */
  if (param_2 == 0x14) {
    uVar1 = FUN_004655b0(param_1);
  }
  else if (param_2 == 0x110) {
    FUN_00405d54(param_1);
    uVar1 = 1;
  }
  else if (param_2 == 0x111) {
    FUN_004062b8(param_1,param_3);
    uVar1 = 1;
  }
  else if (param_2 == 0x138) {
    uVar1 = FUN_00465540(param_3,param_4,DAT_0058f1b4);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

