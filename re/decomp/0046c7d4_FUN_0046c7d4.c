// FUN_0046c7d4 @ 0046c7d4 size=502 sig=undefined FUN_0046c7d4() cc=unknown
// callers: WinMain
// callees: FUN_0046bc28,FUN_0046c780,FUN_00471b20,FUN_0046c49c,FUN_0046b9a0,FUN_00484114,FUN_004455fc,FUN_0044f110,FUN_0044fcd4,ConsumeFood,FUN_00472bf0,FUN_00471bec,FUN_0046b818,memset,FUN_0046b1ac,FUN_0046c1a8,FUN_0046c728,FUN_004589a0

void FUN_0046c7d4(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  short *psVar4;
  
  FUN_004455fc(8);
  DAT_004d5804 = 1;
  FUN_004589a0(&DAT_004d58d4);
  FUN_00471b20();
  FUN_004589a0(&DAT_004d58d8);
  FUN_00471bec();
  puVar1 = &DAT_0059f1a0;
  for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 0x16c;
  }
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    *(undefined2 *)((int)puVar3 + 0x9b2) = 0;
    memset((undefined *)((int)puVar3 + 0xaaa),0,0x2c);
    memset((undefined *)((int)puVar3 + 0xa7e),0,0x2c);
  }
  FUN_004589a0(&DAT_004d58dc);
  FUN_0046c728();
  FUN_004589a0(&DAT_004d58e0);
  FUN_0044fcd4(1,1);
  FUN_004589a0(&DAT_004d58e4);
  FUN_0046b9a0();
  FUN_004589a0(&DAT_004d58e8);
  FUN_00472bf0();
  FUN_004589a0(&DAT_004d58ec);
  ConsumeFood();
  FUN_004589a0(&DAT_004d58f0);
  FUN_0046bc28();
  FUN_004589a0(&DAT_004d58f4);
  FUN_0046b818();
  FUN_004589a0(&DAT_004d58f7);
  FUN_0044fcd4(2,1);
  FUN_004589a0(&DAT_004d58fb);
  FUN_0044f110();
  FUN_004589a0(&DAT_004d5900);
  FUN_0046b1ac(1);
  FUN_004589a0(&DAT_004d5905);
  FUN_0046c1a8(1);
  FUN_004589a0(&DAT_004d590a);
  psVar4 = &DAT_0059f1a0;
  for (iVar2 = 0; iVar2 < DAT_004d5aec; iVar2 = iVar2 + 1) {
    FUN_00484114(&DAT_0059f160 + iVar2 * 0x2d8,(int)*psVar4);
    psVar4 = psVar4 + 0x16c;
  }
  FUN_004589a0(&DAT_004d590f);
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    FUN_0046c49c(puVar3);
  }
  FUN_004589a0(&DAT_004d5914);
  FUN_0046c780();
  FUN_004589a0(&DAT_004d5919);
  FUN_004455fc(9);
  DAT_004d5804 = 0;
  return;
}

