// FUN_0042edc4 @ 0042edc4 size=81 sig=undefined FUN_0042edc4() cc=unknown
// callers: FUN_0042ee18,FUN_0042f0c4
// callees: FUN_004a68dc

undefined * FUN_0042edc4(void)

{
  int iVar1;
  int iVar2;
  
  DAT_00557cd4 = 0;
  iVar2 = 0;
  iVar1 = DAT_004c3818;
  do {
    iVar1 = iVar1 + 1;
    if (0x93 < iVar1) {
      iVar1 = 0;
    }
    FUN_004a68dc(&DAT_00557cd4,(&PTR_DAT_004c38e4)[iVar1]);
    FUN_004a68dc(&DAT_00557cd4,&DAT_004c421b);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x15);
  return &DAT_00557cd4;
}

