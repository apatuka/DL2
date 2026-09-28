// FUN_0040ec50 @ 0040ec50 size=154 sig=undefined FUN_0040ec50() cc=unknown
// callers: FUN_0040ef18
// callees: FUN_00410720,FUN_00401440,FUN_004412d4

undefined4 * FUN_0040ec50(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  iVar4 = -1000000;
  puVar3 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar3) {
      return local_8;
    }
    if (*(char *)((int)puVar3 + 0x7e) != '\0') {
      cVar1 = *(char *)(puVar3 + 8);
      if ((cVar1 != -1) && (cVar1 != *(char *)(param_1 + 8))) {
        iVar2 = FUN_004412d4((int)*(char *)(param_1 + 8),(int)cVar1,2);
        if (iVar2 == 0) goto LAB_0040ecc2;
      }
      iVar2 = FUN_00410720(param_1,puVar3);
      if (iVar2 != 0) {
        iVar2 = FUN_00401440(param_1,puVar3,0);
        if ((iVar2 != 0) && (iVar2 = *(int *)((int)puVar3 + 0xa12) - puVar3[0x298], iVar4 < iVar2))
        {
          iVar4 = iVar2;
          local_8 = puVar3;
        }
      }
    }
LAB_0040ecc2:
    puVar3 = puVar3 + 0x2b7;
  } while( true );
}

