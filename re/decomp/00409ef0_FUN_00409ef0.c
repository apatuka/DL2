// FUN_00409ef0 @ 00409ef0 size=122 sig=undefined FUN_00409ef0() cc=unknown
// callers: FUN_0040a098
// callees: FUN_0040d338,FUN_0044d034,FUN_00407d60

void FUN_00409ef0(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_00521bb4;
  do {
    iVar1 = *piVar3;
    FUN_0040d338(param_1,5,8000,(int)*(short *)(iVar1 + 0x1a),1);
    if ((*(char *)(iVar1 + 0x21) != '\0') && (*(short *)(iVar1 + 0x30) != 0)) {
      iVar2 = FUN_0044d034(iVar1,6);
      if (iVar2 < 2) {
        FUN_00407d60(param_1,5,(int)(char)(&DAT_0059f381)[param_1 * 0x2d8],0x15,
                     (int)*(short *)(iVar1 + 0x1a),7,0);
      }
    }
    piVar3 = (int *)piVar3[1];
  } while (piVar3 != &DAT_00521bb4);
  return;
}

