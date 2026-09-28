// FUN_00473054 @ 00473054 size=82 sig=undefined FUN_00473054() cc=unknown
// callers: FUN_00473324
// callees: FUN_00482f94,FUN_00449fd8

void FUN_00473054(void)

{
  int *piVar1;
  int iVar2;
  
  if (*(short *)(PTR_DAT_004d5988 + 6) != -1) {
    iVar2 = 1;
    piVar1 = &DAT_005a440e + *(short *)(PTR_DAT_004d5988 + 6) * 0x2b7;
    do {
      *piVar1 = *piVar1 + 100;
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < 0xb);
    *(int *)(PTR_DAT_004d5988 + 0xc) = *(int *)(PTR_DAT_004d5988 + 0xc) + 5000;
    FUN_00482f94(PTR_DAT_004d5988);
    FUN_00449fd8();
  }
  return;
}

