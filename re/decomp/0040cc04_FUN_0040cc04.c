// FUN_0040cc04 @ 0040cc04 size=128 sig=undefined FUN_0040cc04() cc=unknown
// callers: @TaskForceDialog$qqspvuiuil
// callees: FUN_0040c8c8,EndDialog

void FUN_0040cc04(HWND param_1,short param_2)

{
  int iVar1;
  
  iVar1 = DAT_004b5380;
  if (param_2 == 2) {
    EndDialog(param_1,0);
  }
  else if (param_2 == 0x15) {
    do {
      DAT_004b5380 = DAT_004b5380 + 1;
      if (DAT_004d5aec <= DAT_004b5380) {
        DAT_004b5380 = 0;
      }
      if ('\x02' < (char)(&DAT_0059f161)[DAT_004b5380 * 0x2d8]) {
        FUN_0040c8c8(param_1);
        return;
      }
    } while (iVar1 != DAT_004b5380);
  }
  return;
}

