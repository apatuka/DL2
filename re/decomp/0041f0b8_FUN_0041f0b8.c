// FUN_0041f0b8 @ 0041f0b8 size=222 sig=undefined FUN_0041f0b8() cc=unknown
// callers: FUN_0041f384
// callees: FUN_0049eb44

void FUN_0041f0b8(void)

{
  int iVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_1c = 10000;
  local_18 = 10000;
  local_14 = 0;
  local_10 = 0;
  iVar1 = 0;
  puVar2 = &DAT_004b79f4;
  do {
    FUN_0049eb44(DAT_004b7974,*puVar2,1,0xd,0,&local_1c);
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 7);
  iVar4 = 0;
  iVar1 = 0;
  puVar2 = &DAT_0053b88c;
  do {
    iVar1 = iVar1 + 1;
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 7);
  iVar1 = 0;
  pcVar3 = &DAT_0059f161;
  do {
    if ((*pcVar3 != '\0') && (iVar1 != DAT_0058f1f4)) {
      FUN_0049eb44(DAT_004b7974,(&DAT_004b79f4)[pcVar3[1]],1,0xd,0,&DAT_004b7994 + iVar4 * 0x10);
      FUN_0049eb44(DAT_004b7974,(&DAT_004b79f4)[pcVar3[1]],1,0xb,1,0);
      (&DAT_0053b88c)[pcVar3[1]] = 1;
      iVar4 = iVar4 + 1;
    }
    iVar1 = iVar1 + 1;
    pcVar3 = pcVar3 + 0x2d8;
  } while (iVar1 < 7);
  return;
}

