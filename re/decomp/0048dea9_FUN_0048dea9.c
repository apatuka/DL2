// FUN_0048dea9 @ 0048dea9 size=58 sig=undefined FUN_0048dea9() cc=unknown
// callers: FUN_0048df30
// callees: 

int FUN_0048dea9(void)

{
  int iVar1;
  
  iVar1 = 0;
  if (DAT_0065e7ac != DAT_0065e7b0) {
    iVar1 = (int)*(short *)(&DAT_0065e7b4 + DAT_0065e7b0 * 4);
    DAT_0065e7b0 = DAT_0065e7b0 + 1;
    if (DAT_0065e7b0 == 0x14) {
      DAT_0065e7b0 = 0;
    }
  }
  return iVar1;
}

