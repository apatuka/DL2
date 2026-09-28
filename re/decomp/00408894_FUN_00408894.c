// FUN_00408894 @ 00408894 size=269 sig=undefined FUN_00408894() cc=unknown
// callers: FUN_004089a4
// callees: FUN_00408838

void FUN_00408894(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint local_8;
  
  (&DAT_0052254c)[param_2] = 0;
  *(undefined4 *)(&DAT_00522568 + param_2 * 4) = 0xffffffff;
  local_8 = 0;
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    if ((*(char *)((int)puVar2 + 0x7e) != '\0') && (*(char *)(puVar2 + 8) == param_2)) {
      uVar3 = 0;
      iVar1 = FUN_00408838(puVar2,param_1);
      if (*(char *)((int)puVar2 + 0x21) == '\0') {
        if (iVar1 < 2) {
          uVar3 = 2;
        }
      }
      else if ((iVar1 < 2) &&
              (5 < *(int *)(&DAT_0055a838 + *(char *)((int)puVar2 + 0x22) * 0x1a2 + param_1 * 4))) {
        uVar3 = 4;
      }
      else if ((iVar1 < 3) &&
              (1 < *(int *)(&DAT_0055a838 + *(char *)((int)puVar2 + 0x22) * 0x1a2 + param_1 * 4))) {
        uVar3 = 1;
      }
      (&DAT_0052254c)[param_2] = (&DAT_0052254c)[param_2] | uVar3;
      if (local_8 < uVar3) {
        *(int *)(&DAT_00522568 + param_2 * 4) = (int)*(short *)((int)puVar2 + 0x1a);
        local_8 = uVar3;
      }
    }
  }
  return;
}

