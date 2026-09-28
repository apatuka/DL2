// FUN_004062b8 @ 004062b8 size=128 sig=undefined FUN_004062b8() cc=unknown
// callers: @DebugJobsDialog$qqspvuiuil
// callees: EndDialog,FUN_00405d54

void FUN_004062b8(HWND param_1,short param_2)

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
        FUN_00405d54(param_1);
        return;
      }
    } while (iVar1 != DAT_004b5380);
  }
  return;
}

