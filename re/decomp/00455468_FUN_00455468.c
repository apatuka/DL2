// FUN_00455468 @ 00455468 size=125 sig=undefined FUN_00455468() cc=unknown
// callers: FUN_004556b0
// callees: FUN_00450e04,FUN_00453210

undefined4 FUN_00455468(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x3c) == 0) {
    if (*(int *)(param_1 + 0x40) == 0) {
      if (DAT_0057e248 == 3) {
        iVar1 = FUN_00450e04(param_1);
        if (iVar1 == 0) {
          uVar2 = 0x1b;
        }
        else {
          uVar2 = 0;
        }
        *param_2 = uVar2;
        *param_3 = 9;
      }
      else {
        *param_2 = 9;
        *param_3 = 9;
      }
    }
    else {
      FUN_00453210(*(int *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x20),
                   *(undefined4 *)(param_1 + 0x24),param_2,param_3);
    }
  }
  else {
    *param_2 = *(undefined4 *)(*(int *)(param_1 + 0x3c) + 0x20);
    *param_3 = *(undefined4 *)(*(int *)(param_1 + 0x3c) + 0x24);
  }
  return 1;
}

