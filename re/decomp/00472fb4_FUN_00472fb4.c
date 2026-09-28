// FUN_00472fb4 @ 00472fb4 size=131 sig=undefined FUN_00472fb4() cc=unknown
// callers: ChCht,FUN_0045dfd4,FUN_00474718,FUN_0045d984,FUN_0043be24
// callees: FUN_00482f94,FUN_0044a000

void FUN_00472fb4(int param_1)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = &DAT_0059f161;
  for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
    if (*pcVar1 != '\0') {
      *pcVar1 = '\x01';
    }
    pcVar1 = pcVar1 + 0x2d8;
  }
  if (param_1 == -1) {
    if (DAT_004d5aec + -1 == DAT_0058f1f4) {
      DAT_0058f1f4 = 0;
    }
    else {
      DAT_0058f1f4 = DAT_0058f1f4 + 1;
    }
  }
  else {
    DAT_0058f1f4 = param_1;
  }
  PTR_DAT_004d5988 = &DAT_0059f160 + DAT_0058f1f4 * 0x2d8;
  FUN_00482f94(PTR_DAT_004d5988);
  FUN_0044a000();
  return;
}

