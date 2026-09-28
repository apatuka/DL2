// FUN_004583ac @ 004583ac size=134 sig=undefined FUN_004583ac() cc=unknown
// callers: FUN_0042662c
// callees: CGNetService_FindSessions,CGNetSession_GetName

void FUN_004583ac(void)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_10;
  
  iVar2 = CGNetService_FindSessions(DAT_00583b74,&local_10);
  if (iVar2 < 1) {
    iVar2 = 0;
    puVar3 = &DAT_0058389c;
    do {
      *puVar3 = 0;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 0x20;
    } while (iVar2 < 0x14);
  }
  else {
    iVar4 = 0;
    puVar5 = &DAT_00583b1c;
    if (0 < iVar2) {
      do {
        CGNetSession_GetName
                  (*(undefined4 *)(local_10 + iVar4 * 4),&DAT_0058389c + iVar4 * 0x20,0x20);
        iVar1 = iVar4 * 4;
        iVar4 = iVar4 + 1;
        *puVar5 = *(undefined4 *)(local_10 + iVar1);
        puVar5 = puVar5 + 1;
      } while (iVar4 < iVar2);
    }
    puVar3 = &DAT_0058389c + iVar2 * 0x20;
    for (; iVar2 < 0x14; iVar2 = iVar2 + 1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 0x20;
    }
  }
  return;
}

