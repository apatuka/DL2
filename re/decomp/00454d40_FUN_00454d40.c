// FUN_00454d40 @ 00454d40 size=82 sig=undefined FUN_00454d40() cc=unknown
// callers: FUN_00454d94
// callees: 

undefined4 FUN_00454d40(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_0057f24c == DAT_0057f250) {
    uVar1 = 0;
  }
  else {
    iVar2 = DAT_0057f24c * 8;
    *param_1 = *(undefined4 *)(&DAT_0057e24c + iVar2);
    *param_2 = *(undefined4 *)(&DAT_0057e250 + iVar2);
    DAT_0057f24c = DAT_0057f24c + 1 & 0x800001ff;
    if ((int)DAT_0057f24c < 0) {
      DAT_0057f24c = (DAT_0057f24c - 1 | 0xfffffe00) + 1;
    }
    uVar1 = 1;
  }
  return uVar1;
}

