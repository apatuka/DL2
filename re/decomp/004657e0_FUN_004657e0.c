// FUN_004657e0 @ 004657e0 size=200 sig=undefined FUN_004657e0() cc=unknown
// callers: FUN_00423960
// callees: thunk_FUN_004ad1a4,GetHighScores,fclose,fopen,FUN_004aa518,memcpy
// strings: \"hiscore.dat\"

undefined4 FUN_004657e0(void)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  undefined8 in_stack_00000028;
  
  iVar1 = GetHighScores();
  if (iVar1 != 0) {
    iVar3 = 0;
    puVar2 = (uint *)(iVar1 + 0x26);
    do {
      if (*puVar2 < in_stack_00000028._2_4_) break;
      iVar3 = iVar3 + 1;
      puVar2 = (uint *)((int)puVar2 + 0x2a);
    } while (iVar3 < 10);
    if (iVar3 < 10) {
      iVar4 = 9;
      if (iVar3 < 9) {
        do {
          memcpy(iVar4 * 0x2a + iVar1,iVar4 * 0x2a + iVar1 + -0x2a,0x2a);
          iVar4 = iVar4 + -1;
        } while (iVar3 < iVar4);
      }
      memcpy(iVar3 * 0x2a + iVar1,&stack0x00000004,0x2a);
      iVar3 = fopen(s_hiscore_dat_004d4db0,&DAT_004d4dcd);
      if (iVar3 == 0) {
        return 0;
      }
      iVar1 = FUN_004aa518(iVar1,0x2a,10,iVar3);
      fclose(iVar3);
      if (iVar1 != 10) {
        thunk_FUN_004ad1a4(s_hiscore_dat_004d4db0);
      }
    }
  }
  return 1;
}

