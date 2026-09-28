// FUN_00402438 @ 00402438 size=89 sig=undefined FUN_00402438() cc=unknown
// callers: 
// callees: 

void FUN_00402438(int param_1)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    iVar2 = 0;
    psVar1 = (short *)(&DAT_0059f1d0 + iVar3 * 0x5a + param_1 * 0x2d8);
    do {
      if (psVar1[0xc] < *psVar1) {
        *psVar1 = psVar1[0xc];
      }
      iVar2 = iVar2 + 1;
      psVar1 = psVar1 + 1;
    } while (iVar2 < 0xc);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 6);
  return;
}

