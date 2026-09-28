// FUN_0040ab80 @ 0040ab80 size=126 sig=undefined FUN_0040ab80() cc=unknown
// callers: FUN_0040dbc4,FUN_0040ab80,FUN_0040e050
// callees: FUN_0040ab80

int FUN_0040ab80(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 0;
  piVar3 = (int *)(param_1 + 0x44);
  while ((iVar1 = *piVar3, iVar1 == 0 || (*(char *)(iVar1 + 6) != param_2))) {
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
    if (0xf < iVar2) {
      iVar2 = 1;
      piVar3 = (int *)(param_1 + 0x88);
      while ((*piVar3 == 0 ||
             (iVar1 = FUN_0040ab80(&DAT_005224c0 +
                                   *(short *)(param_1 + 10) * 0x2648 + *piVar3 * 0xc4,param_2),
             iVar1 == 0))) {
        iVar2 = iVar2 + 1;
        piVar3 = piVar3 + 1;
        if (0xf < iVar2) {
          return 0;
        }
      }
      return iVar1;
    }
  }
  return iVar1;
}

