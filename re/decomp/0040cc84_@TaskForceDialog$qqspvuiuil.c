// @TaskForceDialog$qqspvuiuil @ 0040cc84 size=103 sig=undefined @TaskForceDialog$qqspvuiuil() cc=unknown
// callers: 
// callees: FUN_0040c8c8,FUN_00465540,FUN_0040cc04,FUN_004655b0

undefined4
_TaskForceDialog_qqspvuiuil(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
                    /* 0xcc84  5  @TaskForceDialog$qqspvuiuil */
  if (param_2 == 0x14) {
    uVar1 = FUN_004655b0(param_1);
  }
  else if (param_2 == 0x110) {
    FUN_0040c8c8(param_1);
    uVar1 = 1;
  }
  else if (param_2 == 0x111) {
    FUN_0040cc04(param_1,param_3);
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

