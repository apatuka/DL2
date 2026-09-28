// FUN_00472da4 @ 00472da4 size=94 sig=undefined FUN_00472da4() cc=unknown
// callers: @MainWndProc$qqspvuiuil
// callees: ChCht,FUN_00423d84,FUN_0042836c
// strings: \"Are you sure you want to exit Deadlock 2?\"|\"Exit Game\"

void FUN_00472da4(void)

{
  int iVar1;
  
  if ((DAT_0059f154 < 1) || ((code *)PTR_FUN_004d02b8 != FUN_00457ac0)) {
    iVar1 = FUN_0042836c(PTR_s_Exit_Game_00509bbc,PTR_s_Are_you_sure_you_want_to_exit_De_00509bc0,
                         0x18,0,4);
    if (iVar1 == 2) {
      return;
    }
  }
  else {
    iVar1 = FUN_00423d84();
    if (iVar1 == 2) {
      return;
    }
    if ((iVar1 == 1) && (iVar1 = ChCht(0,1,0), iVar1 == 0)) {
      return;
    }
  }
  DAT_0058f1ec = 1;
  return;
}

