// FUN_004a9e50 @ 004a9e50 size=100 sig=undefined FUN_004a9e50() cc=unknown
// callers: FUN_004a9c80
// callees: FUN_004ac4cc,FUN_004ab628,FUN_004ab638

int FUN_004a9e50(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  FUN_004ab628();
  iVar3 = 0;
  puVar2 = &DAT_0051fce4;
  iVar5 = DAT_00520194;
  while (iVar5 != 0) {
    if ((int)puVar2[2] < 0) {
      iVar4 = puVar2[3] + puVar2[2] + 1;
      puVar2[2] = puVar2[2] - iVar4;
      *puVar2 = puVar2[1];
      iVar1 = FUN_004ac4cc((int)*(char *)((int)puVar2 + 0x16),puVar2[1],iVar4);
      if ((iVar4 != iVar1) && ((*(byte *)((int)puVar2 + 0x13) & 2) == 0)) {
        *(ushort *)((int)puVar2 + 0x12) = *(ushort *)((int)puVar2 + 0x12) | 0x10;
      }
      iVar3 = iVar3 + 1;
    }
    puVar2 = puVar2 + 6;
    iVar5 = iVar5 + -1;
  }
  FUN_004ab638();
  return iVar3;
}

