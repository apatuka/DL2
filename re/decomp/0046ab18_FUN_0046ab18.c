// FUN_0046ab18 @ 0046ab18 size=297 sig=undefined FUN_0046ab18() cc=unknown
// callers: FUN_00414b64,FUN_0046ac44,FUN_0041f7f0,FUN_00442184,FUN_0041b330
// callees: FUN_0046b958,FUN_0046b910,FUN_0046aa10,FUN_0044f3f0,memset,FUN_0046ae1c

void FUN_0046ab18(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = DAT_0058f1f4;
  if (*(char *)(param_1 + 0x20) != -1) {
    iVar1 = (int)*(char *)(param_1 + 0x20);
  }
  memset(param_1 + 0xa7e,0,0x2c);
  memset(param_1 + 0xaaa,0,0x2c);
  *param_2 = *param_2 + 1;
  param_2[1] = param_2[1] + (int)*(short *)(param_1 + 0x30);
  iVar1 = FUN_0046ae1c(&DAT_0059f160 + iVar1 * 0x2d8,param_1);
  param_2[2] = param_2[2] + iVar1;
  iVar1 = FUN_0046b958(param_1);
  param_2[0x14] = param_2[0x14] - iVar1;
  iVar1 = FUN_0046b910(param_1);
  param_2[0x15] = param_2[0x15] - iVar1;
  FUN_0044f3f0(param_1,0,1);
  FUN_0044f3f0(param_1,0,2);
  FUN_0046aa10(param_1);
  param_2[3] = param_2[3] + (int)*(short *)(param_1 + 0x2a);
  param_2[4] = param_2[4] + (int)*(short *)(param_1 + 0x2e);
  iVar1 = 1;
  param_2 = param_2 + 9;
  piVar2 = (int *)(param_1 + 0x3e);
  do {
    *param_2 = *param_2 + *piVar2;
    param_2[0xb] = param_2[0xb] + piVar2[0x29c];
    param_2[0xb] = param_2[0xb] - piVar2[0x291];
    if ((((iVar1 != 3) && (iVar1 != 5)) && (iVar1 != 6)) &&
       (((iVar1 != 7 && (iVar1 != 10)) &&
        ((*(short *)(param_1 + 0x30) != 0 &&
         ((1 << (*(byte *)(param_1 + 0x20) & 0x1f) & (int)DAT_004fc4da) != 0)))))) {
      param_2[0xb] = param_2[0xb] + 100;
    }
    iVar1 = iVar1 + 1;
    param_2 = param_2 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0xb);
  return;
}

