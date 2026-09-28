// FUN_004ac5d8 @ 004ac5d8 size=66 sig=undefined FUN_004ac5d8() cc=unknown
// callers: FUN_004a70ca
// callees: FUN_004a9c80,FUN_004ab628,FUN_004ab638

int FUN_004ac5d8(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  FUN_004ab628();
  iVar3 = 0;
  puVar1 = &DAT_0051fce4;
  iVar2 = DAT_00520194;
  while (iVar2 != 0) {
    if (((*(byte *)((int)puVar1 + 0x12) & 3) != 0) && (puVar1[2] != 0)) {
      FUN_004a9c80(puVar1);
      iVar3 = iVar3 + 1;
    }
    puVar1 = puVar1 + 6;
    iVar2 = iVar2 + -1;
  }
  FUN_004ab638();
  return iVar3;
}

