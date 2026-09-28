// FUN_0040bfb4 @ 0040bfb4 size=99 sig=undefined FUN_0040bfb4() cc=unknown
// callers: FUN_0040dbc4,FUN_0040ec04,FUN_0040e8ac,FUN_0040e050,FUN_0040f2e0,FUN_00407594,FUN_0040e994,FUN_0040e384,FUN_0040f478
// callees: FUN_00476f24,FUN_00416e70

void FUN_0040bfb4(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar3 = (int *)(param_1 + 0x44);
  do {
    iVar1 = *piVar3;
    if ((iVar1 != 0) && (iVar1 != 0)) {
      iVar2 = FUN_00416e70(iVar1,param_2,
                           (int)(char)(&DAT_0059f162)[*(short *)(param_1 + 10) * 0x2d8]);
      if (iVar2 != 0) {
        *(undefined1 *)(iVar1 + 0x25) = (undefined1)param_2;
        FUN_00476f24(iVar1,0);
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 0x10);
  return;
}

