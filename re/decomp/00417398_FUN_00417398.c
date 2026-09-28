// FUN_00417398 @ 00417398 size=57 sig=undefined FUN_00417398() cc=unknown
// callers: FUN_00419710
// callees: 

undefined4 FUN_00417398(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar2 = 0;
  iVar5 = 0;
  piVar4 = &DAT_005332d8;
  do {
    iVar3 = 0;
    piVar1 = piVar4;
    do {
      if ((*piVar1 == 1) && (iVar2 = iVar2 + 1, 1 < iVar2)) {
        return CONCAT31((int3)((uint)piVar1 >> 8),1);
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 8;
    } while (iVar3 < 10);
    iVar5 = iVar5 + 1;
    piVar4 = (int *)((int)piVar4 + 0x146);
    if (99 < iVar5) {
      return 0;
    }
  } while( true );
}

