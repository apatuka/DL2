// FUN_0046e374 @ 0046e374 size=38 sig=undefined FUN_0046e374() cc=unknown
// callers: FUN_00486b74,FUN_004780e4,FUN_00478090
// callees: FUN_00476ffc

void FUN_0046e374(void)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = 0;
  pcVar2 = &DAT_0059f161;
  do {
    if ('\x02' < *pcVar2) {
      FUN_00476ffc(iVar1);
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x2d8;
  } while (iVar1 < 7);
  return;
}

