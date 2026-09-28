// FUN_00454d04 @ 00454d04 size=57 sig=undefined FUN_00454d04() cc=unknown
// callers: FUN_00454d94
// callees: 

void FUN_00454d04(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = DAT_0057f250 * 8;
  *(undefined4 *)(&DAT_0057e24c + iVar1) = param_1;
  *(undefined4 *)(&DAT_0057e250 + iVar1) = param_2;
  DAT_0057f250 = DAT_0057f250 + 1 & 0x800001ff;
  if ((int)DAT_0057f250 < 0) {
    DAT_0057f250 = (DAT_0057f250 - 1 | 0xfffffe00) + 1;
  }
  return;
}

