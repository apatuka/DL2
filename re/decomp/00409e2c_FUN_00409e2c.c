// FUN_00409e2c @ 00409e2c size=196 sig=undefined FUN_00409e2c() cc=unknown
// callers: FUN_0040a098
// callees: FUN_00475a60,FUN_0046b0e4,FUN_0044d1a4,FUN_0046b074,FUN_0040cffc

void FUN_00409e2c(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_00521bb4;
  do {
    iVar1 = *piVar3;
    if ((*(char *)(iVar1 + 0x21) != '\0') && (*(short *)(iVar1 + 0x30) != 0)) {
      iVar2 = FUN_0046b0e4(iVar1);
      if (*(short *)(iVar1 + 0x30) < iVar2) {
        iVar2 = FUN_0044d1a4(iVar1,6,0);
        if ((iVar2 != -1) ||
           (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) == 0)) {
          FUN_0040cffc(param_1,5,(int)(char)(&DAT_0059f381)[param_1 * 0x2d8],
                       (int)*(short *)(iVar1 + 0x1a),0);
        }
      }
      else {
        iVar2 = FUN_0046b074(iVar1);
        if (iVar2 == *(short *)(iVar1 + 0x30)) {
          iVar2 = FUN_0044d1a4(iVar1,0xd,0);
          if (iVar2 != -1) {
            FUN_00475a60(iVar1,iVar2,0);
          }
        }
      }
    }
    piVar3 = (int *)piVar3[1];
  } while (piVar3 != &DAT_00521bb4);
  return;
}

