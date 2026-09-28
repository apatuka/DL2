// FUN_0040fb14 @ 0040fb14 size=154 sig=undefined FUN_0040fb14() cc=unknown
// callers: FUN_0041026c
// callees: FindConstructionSite,FUN_0040f5e0,FUN_0040f794,FUN_0040f700

int FUN_0040fb14(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined *puVar5;
  
  puVar5 = (undefined *)0x0;
  iVar2 = FUN_0040f5e0(param_1);
  iVar2 = *(int *)(&DAT_004b6f74 + iVar2 * 4);
  if (param_2 != -1) {
    puVar5 = &DAT_005a43d0 + param_2 * 0xadc;
  }
  piVar4 = &DAT_00521bb4;
  do {
    iVar1 = *piVar4;
    iVar3 = FindConstructionSite(iVar1,iVar2);
    if (iVar3 != -1) {
      iVar3 = FUN_0040f700(iVar1,puVar5,param_1,param_3);
      if (iVar3 != 0) {
        return iVar1;
      }
      if (((&DAT_004f9dc3)[iVar2 * 0x32] == '\b') &&
         (iVar3 = FUN_0040f794((int)*(char *)(iVar1 + 0x20),iVar1,puVar5,param_1), iVar3 != 0)) {
        return iVar1;
      }
    }
    piVar4 = (int *)piVar4[1];
    if (piVar4 == &DAT_00521bb4) {
      return 0;
    }
  } while( true );
}

