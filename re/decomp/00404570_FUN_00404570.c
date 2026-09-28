// FUN_00404570 @ 00404570 size=95 sig=undefined FUN_00404570() cc=unknown
// callers: FUN_00408a88
// callees: FUN_004765a8,FUN_0047654c

void FUN_00404570(int param_1)

{
  int *piVar1;
  
  if (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) == 0) {
    FUN_0047654c(param_1,5);
  }
  else {
    FUN_0047654c(param_1,2);
    piVar1 = &DAT_00521bb4;
    do {
      FUN_004765a8(param_1,(int)*(short *)(*piVar1 + 0x1a),0);
      piVar1 = (int *)piVar1[1];
    } while (piVar1 != &DAT_00521bb4);
  }
  return;
}

