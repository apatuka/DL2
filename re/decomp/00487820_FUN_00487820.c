// FUN_00487820 @ 00487820 size=124 sig=undefined FUN_00487820() cc=unknown
// callers: FUN_00487e34
// callees: FUN_0048463c,FUN_004a6b48,FUN_0048447c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00487820(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  _DAT_005126c4 = 1;
  if (DAT_004d63d4 == 0) {
    if (param_2 != 0) {
      FUN_004a6b48(&DAT_0065e448,param_2,0xff);
      DAT_0065e547 = 0;
      FUN_0048463c(0);
      FUN_0048447c(&DAT_0065e448,(*(int *)(DAT_005126dc + 4) + -0x19) / DAT_005126cc);
      FUN_0048463c(DAT_0058f1d0);
    }
    _DAT_005126c4 = 0;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

