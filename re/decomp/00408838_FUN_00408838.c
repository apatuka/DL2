// FUN_00408838 @ 00408838 size=91 sig=undefined FUN_00408838() cc=unknown
// callers: FUN_00408894
// callees: FUN_004726cc

int FUN_00408838(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 3;
  for (puVar2 = &DAT_005a4eac; puVar2 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar2 = puVar2 + 0x2b7) {
    if ((*(char *)((int)puVar2 + 0x7e) != '\0') && (param_2 == *(char *)(puVar2 + 8))) {
      iVar1 = FUN_004726cc(param_1,puVar2,param_2);
      if (iVar1 < iVar3) {
        iVar3 = iVar1;
      }
    }
  }
  return iVar3;
}

