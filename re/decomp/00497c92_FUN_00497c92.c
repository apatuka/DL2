// FUN_00497c92 @ 00497c92 size=174 sig=undefined FUN_00497c92() cc=unknown
// callers: FUN_00497fa4
// callees: FUN_0048f869,FUN_0048fade,FUN_0048f992,FUN_0048f877

void FUN_00497c92(int param_1,undefined4 param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  
  uVar1 = FUN_0048f877(*(undefined4 *)(param_1 + 4));
  if ((uVar1 & 1) != 0) {
    uVar1 = uVar1 + 1;
  }
  iVar2 = FUN_0048f992(param_2,&DAT_0065edf4,0x14);
  if (iVar2 == 0x14) {
    DAT_0065edf4 = FUN_0048f869(DAT_0065edf4);
    DAT_0065edf6 = FUN_0048f869(CONCAT22(extraout_var_01,DAT_0065edf6));
    DAT_0065edf8 = FUN_0048f869(CONCAT22(extraout_var,DAT_0065edf8));
    DAT_0065edfa = FUN_0048f869(DAT_0065edfa);
    DAT_0065ee00 = FUN_0048f869(CONCAT22(extraout_var_02,DAT_0065ee00));
    DAT_0065ee04 = FUN_0048f869(CONCAT22(extraout_var_00,DAT_0065ee04));
    DAT_0065ee06 = FUN_0048f869(DAT_0065ee06);
    if (0 < (int)(uVar1 - 0x14)) {
      FUN_0048fade(param_2,uVar1 - 0x14,0);
    }
  }
  *param_3 = &DAT_0065edf4;
  return;
}

