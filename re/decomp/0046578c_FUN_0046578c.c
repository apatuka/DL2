// FUN_0046578c @ 0046578c size=84 sig=undefined FUN_0046578c() cc=unknown
// callers: GetHighScores,FUN_0042ebb8
// callees: fclose,fopen,FUN_004aa518,memset
// strings: \"hiscore.dat\"

void FUN_0046578c(void)

{
  int iVar1;
  undefined1 local_1a8 [420];
  
  iVar1 = fopen(s_hiscore_dat_004d4db0,&DAT_004d4dcd);
  if (iVar1 != 0) {
    memset(local_1a8,0,0x1a4);
    FUN_004aa518(local_1a8,0x2a,10,iVar1);
    fclose(iVar1);
  }
  return;
}

