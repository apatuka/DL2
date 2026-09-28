// FUN_00407794 @ 00407794 size=208 sig=undefined FUN_00407794() cc=unknown
// callers: FUN_00407be8
// callees: FUN_00476cc0,FUN_00430b94

void FUN_00407794(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  char cVar4;
  int local_8;
  
  if (0 < param_3) {
    local_8 = FUN_00430b94(param_2);
    local_8 = (DAT_00522520 + -100) / local_8;
    if (param_3 < local_8) {
      piVar2 = &param_3;
    }
    else {
      piVar2 = &local_8;
    }
    param_3 = *piVar2;
    if (0 < param_3) {
      iVar3 = 0;
      piVar2 = &DAT_00521bb4;
      cVar4 = '\0';
      do {
        iVar1 = *piVar2;
        if (((*(short *)(iVar1 + 0x9c2) != 0) ||
            (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) == 0)) &&
           (cVar4 <= *(char *)(iVar1 + 0x27))) {
          cVar4 = *(char *)(iVar1 + 0x27);
          iVar3 = iVar1;
        }
        piVar2 = (int *)piVar2[1];
      } while (piVar2 != &DAT_00521bb4);
      if (iVar3 != 0) {
        FUN_00476cc0(&DAT_0059f160 + param_1 * 0x2d8,param_2,param_3,(int)*(short *)(iVar3 + 0x1a));
      }
    }
  }
  return;
}

