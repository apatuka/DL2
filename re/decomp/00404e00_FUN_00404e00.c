// FUN_00404e00 @ 00404e00 size=148 sig=undefined FUN_00404e00() cc=unknown
// callers: FUN_004050ac,FUN_00404f5c
// callees: 

int FUN_00404e00(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(&DAT_004b57c0 + DAT_004d5a94 * 0x30);
  while ((((int)(char)(&DAT_0059f162)[param_1 * 0x2d8] != *piVar1 && (*piVar1 != 7)) ||
         (((int)(char)(&DAT_0059f162)[param_2 * 0x2d8] != piVar1[1] && (piVar1[1] != 7))))) {
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 4;
    if (2 < iVar2) {
      return *(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c);
    }
  }
  return piVar1[2];
}

