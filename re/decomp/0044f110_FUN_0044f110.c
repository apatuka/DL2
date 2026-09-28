// FUN_0044f110 @ 0044f110 size=214 sig=undefined FUN_0044f110() cc=unknown
// callers: FUN_0046c7d4
// callees: memset,FUN_004720f4,FUN_0046f908,FUN_0044df30,FUN_0044de9c

void FUN_0044f110(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined1 local_44 [52];
  
  FUN_0046f908();
  iVar3 = 0;
  piVar5 = &DAT_0058f21c;
  do {
    iVar1 = *piVar5;
    iVar2 = iVar1 * 0x122;
    if ((((&DAT_005f0414)[iVar2] != '\0') && (((&DAT_005f0412)[iVar1 * 0x91] & 2) == 0)) &&
       (((&DAT_005f0412)[iVar1 * 0x91] & 4) != 0)) {
      iVar4 = (short)(&DAT_005f0418)[iVar1 * 0x91] * 0xadc;
      if ((&DAT_005a43f0)[iVar4] != -1) {
        if ((&DAT_005f0414)[iVar2] == '%') {
          FUN_0044df30(&DAT_005f0410 + iVar1 * 0x91,local_44);
        }
        else {
          FUN_0044de9c(&DAT_0059f160 + (char)(&DAT_005a43f0)[iVar4] * 0x2d8,
                       (int)(char)(&DAT_005f0414)[iVar2],(int)(char)(&DAT_005a43f1)[iVar4],local_44)
          ;
        }
        iVar4 = FUN_004720f4(&DAT_005a43d0 + iVar4,local_44,(int)&DAT_005f044e + iVar2);
        if (iVar4 == 0) {
          (&DAT_005f0412)[iVar1 * 0x91] = (&DAT_005f0412)[iVar1 * 0x91] | 2;
          memset((int)&DAT_005f044e + iVar2,0,0x2c);
        }
      }
    }
    iVar3 = iVar3 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar3 < 0x4b0);
  return;
}

