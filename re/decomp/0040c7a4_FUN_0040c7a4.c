// FUN_0040c7a4 @ 0040c7a4 size=225 sig=undefined FUN_0040c7a4() cc=unknown
// callers: FUN_00401ac0
// callees: FUN_0040d990,FUN_0047510c,FUN_0040d64c

int * FUN_0040c7a4(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  
  iVar3 = *(char *)(param_1 + 8) * 0x2648 + *(short *)(param_1 + 0x36) * 0xc4;
  iVar7 = 1;
  piVar6 = (int *)(&DAT_00522548 + iVar3);
  do {
    if (*piVar6 != 0) {
      iVar4 = *(short *)(&DAT_005224ca + iVar3) * 0x2648 + *piVar6 * 0xc4;
      piVar5 = (int *)(&DAT_005224c0 + iVar4);
      if ((((*piVar5 == 9) && (*(int *)(&DAT_005224d0 + iVar4) != 0)) &&
          (*(char *)(*(int *)(&DAT_005224d0 + iVar4) + 0x22) == *(char *)(param_2 + 0x22))) &&
         (iVar2 = FUN_0040d990(piVar5), iVar2 == 0)) {
        iVar2 = 0;
        sVar1 = *(short *)(iVar4 + 0x5224e4 + iVar7 * 2);
        if (sVar1 != 0) {
          iVar2 = FUN_0047510c(sVar1);
        }
        if (iVar2 == 0) {
          return piVar5;
        }
        if (*(char *)(iVar2 + 6) != '\f') {
          return piVar5;
        }
        iVar4 = FUN_0040d64c(piVar5,*(undefined4 *)(iVar2 + 0x3c),param_2);
        if (iVar4 != 0) {
          return piVar5;
        }
      }
    }
    iVar7 = iVar7 + 1;
    piVar6 = piVar6 + 1;
    if (0xf < iVar7) {
      return (int *)0x0;
    }
  } while( true );
}

