// GetHighScores @ 004656f0 size=155 sig=undefined GetHighScores() cc=unknown
// callers: FUN_0042e8c0,FUN_004657e0
// callees: thunk_FUN_004ad1a4,FUN_004418ec,fclose,fopen,FUN_0046578c,fread
// strings: \"hiscore.dat\"|\"GetHighScores\"

/* auto-named from string evidence: GetHighScores */

int GetHighScores(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar1 = fopen(s_hiscore_dat_004d4db0,&DAT_004d4dbc);
  if (iVar1 == 0) {
    FUN_0046578c();
    iVar1 = fopen(s_hiscore_dat_004d4db0,&DAT_004d4dbc);
    if (iVar1 == 0) {
      return 0;
    }
  }
  iVar2 = FUN_004418ec(s_GetHighScores_004d4dbf,0x1a4);
  if (iVar2 == 0) {
    fclose(iVar1);
    iVar2 = 0;
  }
  else {
    iVar3 = fread(iVar2,0x2a,10,iVar1);
    fclose(iVar1);
    if (iVar3 != 10) {
      iVar1 = 0;
      puVar4 = (undefined4 *)(iVar2 + 0x26);
      do {
        iVar1 = iVar1 + 1;
        *puVar4 = 0;
        puVar4 = (undefined4 *)((int)puVar4 + 0x2a);
      } while (iVar1 < 10);
      thunk_FUN_004ad1a4(s_hiscore_dat_004d4db0);
    }
  }
  return iVar2;
}

