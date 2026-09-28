// FUN_0049eb9f @ 0049eb9f size=92 sig=undefined FUN_0049eb9f() cc=unknown
// callers: FUN_0043b2c4,FUN_004a03cf,FUN_0043b040,FUN_0043b8b0,FUN_0043b50c,FUN_0049ff48,FUN_0041e4d0,FUN_004a016e,FUN_004a060f,FUN_0042b99c,FUN_0049e3d7,FUN_0049e47a,FUN_0049d7f4,FUN_0041bfc0,FUN_00427198,FUN_0043aed0,FUN_0049d58b,FUN_0049ebfb,FUN_0041f7f0,FUN_004a08c5,FUN_0041b330
// callees: FUN_0049ea99,FUN_00495162,FUN_00491bf7
// strings: \"Could not set font for item ID %d\\r\\n\"

undefined4 FUN_0049eb9f(int param_1,int param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x3c) == 0) {
    iVar1 = FUN_0049ea99(param_1);
    if (*(int *)(iVar1 + 0x38) == 0) {
      if (param_2 == 0) {
        FUN_00495162(s_Could_not_set_font_for_item_ID___0051e390,*(undefined4 *)(param_1 + 0x30));
        return 0;
      }
      FUN_00491bf7(param_2);
    }
    else {
      FUN_00491bf7(*(undefined4 *)(iVar1 + 0x38));
    }
  }
  else {
    FUN_00491bf7(*(undefined4 *)(param_1 + 0x3c));
  }
  return 1;
}

