// FUN_004043e4 @ 004043e4 size=95 sig=undefined FUN_004043e4() cc=unknown
// callers: @DebugMinisterDialog$qqspvuiuil
// callees: FUN_00404048

void FUN_004043e4(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = DAT_004b5380;
  while( true ) {
    DAT_004b5380 = DAT_004b5380 + 1;
    if (DAT_004d5aec <= DAT_004b5380) {
      DAT_004b5380 = 0;
    }
    if ('\x02' < (char)(&DAT_0059f161)[DAT_004b5380 * 0x2d8]) break;
    if (iVar1 == DAT_004b5380) {
      return;
    }
  }
  FUN_00404048(param_1);
  return;
}

