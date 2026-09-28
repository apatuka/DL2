// FUN_00419d94 @ 00419d94 size=46 sig=undefined FUN_00419d94() cc=unknown
// callers: FUN_0041a204,FUN_0041a470,FUN_0041a518
// callees: 

void FUN_00419d94(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar2 = &DAT_005332d8;
  do {
    iVar3 = 0;
    piVar1 = piVar2;
    do {
      if (*piVar1 == 1) {
        *piVar1 = 2;
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 8;
    } while (iVar3 < 10);
    iVar4 = iVar4 + 1;
    piVar2 = (int *)((int)piVar2 + 0x146);
  } while (iVar4 < 100);
  return;
}

