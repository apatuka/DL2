// FUN_004094d8 @ 004094d8 size=108 sig=undefined FUN_004094d8() cc=unknown
// callers: FUN_00409914
// callees: FUN_00409400,FUN_0044d034,FUN_00407d60

void FUN_004094d8(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = &DAT_00521bb4;
  do {
    iVar1 = *piVar4;
    iVar2 = FUN_00409400(param_1,iVar1);
    if (iVar2 != 0) {
      iVar3 = FUN_0044d034(iVar1,0x10);
      if (iVar3 < 2) {
        FUN_00407d60(param_1,0,(int)(char)(&DAT_0059f1bf)[param_1 * 0x2d8],iVar2,
                     (int)*(short *)(iVar1 + 0x1a),1,0);
      }
    }
    piVar4 = (int *)piVar4[1];
  } while (piVar4 != &DAT_00521bb4);
  return;
}

