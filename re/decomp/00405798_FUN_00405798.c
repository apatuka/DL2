// FUN_00405798 @ 00405798 size=43 sig=undefined FUN_00405798() cc=unknown
// callers: FUN_0046c9f8,FUN_0045ff94,FUN_004057c4
// callees: memset

void FUN_00405798(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  memset(&DAT_00522280,0,0x1dc);
  iVar2 = 0;
  puVar1 = &DAT_00522280;
  do {
    *puVar1 = 1;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x11;
  } while (iVar2 < 7);
  return;
}

