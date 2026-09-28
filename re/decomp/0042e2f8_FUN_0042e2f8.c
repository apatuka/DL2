// FUN_0042e2f8 @ 0042e2f8 size=234 sig=undefined FUN_0042e2f8() cc=unknown
// callers: FUN_0043bd5c,FUN_0043bdf4
// callees: FUN_0042dee0,FUN_0042e3e4,FUN_0042e434,FUN_0042e4c0,FUN_0042df6c,FUN_0042e080,FUN_0042e054

int FUN_0042e2f8(int *param_1,int param_2)

{
  bool bVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  
  FUN_0042e434();
  FUN_0042e3e4();
  if (param_2 == -1) {
    DAT_00557c74 = 0;
    for (DAT_004c366c = 0; DAT_004c366c < 7; DAT_004c366c = DAT_004c366c + 1) {
      bVar1 = false;
      iVar3 = 0;
      pcVar2 = &DAT_0059f162;
      do {
        if (*pcVar2 == DAT_004c366c) {
          bVar1 = true;
          break;
        }
        iVar3 = iVar3 + 1;
        pcVar2 = pcVar2 + 0x2d8;
      } while (iVar3 < 7);
      if (!bVar1) break;
    }
    DAT_004c3670 = DAT_004d5b0c;
  }
  else {
    DAT_00557c74 = 1;
    DAT_004c366c = (int)(char)(&DAT_0059f162)[param_2 * 0x2d8];
    DAT_004c3670 = (int)(char)(&DAT_005a0548)[param_2];
  }
  iVar3 = FUN_0042df6c();
  if (iVar3 == 0) {
    iVar4 = -1;
  }
  else {
    FUN_0042dee0();
    do {
      iVar3 = FUN_0042e080();
    } while (iVar3 == 0);
    FUN_0042e054();
    *param_1 = DAT_004c3670;
    FUN_0042e4c0();
    iVar4 = DAT_004c366c;
    if (iVar3 != 0xf) {
      iVar4 = -1;
    }
  }
  return iVar4;
}

