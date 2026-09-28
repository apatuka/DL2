// FUN_00409d9c @ 00409d9c size=142 sig=undefined FUN_00409d9c() cc=unknown
// callers: FUN_0040a098
// callees: FUN_00407d60,FUN_0044d1a4

void FUN_00409d9c(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = &DAT_00521bb4;
  cVar1 = (&DAT_0059f381)[param_1 * 0x2d8];
  do {
    iVar2 = *piVar4;
    if ((*(char *)(iVar2 + 0x21) != '\0') && (*(short *)(iVar2 + 0x30) != 0)) {
      iVar3 = FUN_0044d1a4(iVar2,0xe,0);
      if (iVar3 == -1) {
        if ((*(byte *)(iVar2 + 0x1c) & 0x20) == 0) {
          FUN_00407d60(param_1,5,(int)cVar1,0x11,(int)*(short *)(iVar2 + 0x1a),0x13,0);
        }
        else {
          FUN_00407d60(param_1,5,50000,0x11,(int)*(short *)(iVar2 + 0x1a),0x13,1);
        }
      }
    }
    piVar4 = (int *)piVar4[1];
  } while (piVar4 != &DAT_00521bb4);
  return;
}

