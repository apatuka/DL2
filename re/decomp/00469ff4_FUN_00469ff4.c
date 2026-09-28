// FUN_00469ff4 @ 00469ff4 size=43 sig=undefined FUN_00469ff4() cc=unknown
// callers: FUN_0046a844
// callees: 

void FUN_00469ff4(void)

{
  undefined1 *puVar1;
  int iVar2;
  short *psVar3;
  
  puVar1 = DAT_0058f134;
  psVar3 = DAT_0058f138;
  for (iVar2 = 0; iVar2 < DAT_0058f144; iVar2 = iVar2 + 1) {
    if (*psVar3 < 1) {
      *puVar1 = 0x40;
    }
    else {
      *puVar1 = 0x30;
    }
    psVar3 = psVar3 + 1;
    puVar1 = puVar1 + 1;
  }
  return;
}

