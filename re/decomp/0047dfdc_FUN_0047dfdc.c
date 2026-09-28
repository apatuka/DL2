// FUN_0047dfdc @ 0047dfdc size=117 sig=undefined FUN_0047dfdc() cc=unknown
// callers: FUN_0044f3f0,FUN_0044db50,_DemolishBuilding,FUN_0044dcf4
// callees: FUN_0044d1a4,FUN_0047de94,FUN_0047ded8

void FUN_0047dfdc(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  puVar2 = (undefined1 *)(param_1 + 0x150);
  do {
    *puVar2 = 0;
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 0x34;
  } while (iVar3 < 0x24);
  if (*(char *)(param_1 + 0x21) != '\0') {
    iVar3 = FUN_0044d1a4(param_1,0x11,0);
    if (iVar3 != -1) {
      iVar4 = 0;
      do {
        iVar1 = *(int *)(iVar4 * 0x34 + param_1 + 0x154);
        if (((iVar1 != 0) && (*(char *)(iVar1 + 4) != '\0')) && (iVar3 != iVar4)) {
          FUN_0047de94(param_1,iVar3,iVar4);
          FUN_0047ded8(param_1,iVar4);
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x24);
    }
  }
  return;
}

