// FUN_00474e48 @ 00474e48 size=28 sig=undefined FUN_00474e48() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: 

void FUN_00474e48(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  puVar1 = &DAT_0059f168;
  do {
    *puVar1 = 1;
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 0x2d8;
  } while (iVar2 < 7);
  return;
}

