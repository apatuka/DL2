// FUN_00431398 @ 00431398 size=292 sig=undefined FUN_00431398() cc=unknown
// callers: FUN_0043210c,FUN_00431f58
// callees: FUN_0046ca40

void FUN_00431398(void)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  
  bVar1 = *PTR_DAT_004d5988;
  if (DAT_0059f154 != DAT_004c450c) {
    DAT_004c450c = DAT_0059f154;
    DAT_00558e60 = 0;
    iVar4 = 1;
    do {
      if ((((int)(short)(&DAT_004fbbac)[iVar4 * 0x19] & 1 << (bVar1 & 0x1f)) == 0) &&
         (uVar3 = FUN_0046ca40(), (uVar3 & 3) == 0)) {
        bVar2 = false;
        switch((&DAT_004fbbcc)[iVar4 * 0x19]) {
        case 1:
          if (DAT_0059f154 < 0x28) {
            bVar2 = true;
          }
          else {
            bVar2 = false;
          }
          break;
        case 2:
          if (DAT_0059f154 < 10) {
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
          break;
        case 3:
          if (DAT_0059f154 < 0x14) {
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
          break;
        case 4:
          if (DAT_0059f154 < 0x28) {
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
          break;
        case 5:
        case 6:
          if (DAT_0059f154 < 0x3c) {
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
        }
        if (bVar2) {
          (&DAT_00558de0)[DAT_00558e60 * 2] = iVar4;
          (&DAT_00558de4)[DAT_00558e60 * 2] = *(short *)(&DAT_004fbbce + iVar4 * 0x32) * 5;
          DAT_00558e60 = DAT_00558e60 + 1;
          if (0xf < DAT_00558e60) {
            return;
          }
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x30);
  }
  return;
}

