// FUN_00416364 @ 00416364 size=111 sig=undefined FUN_00416364() cc=unknown
// callers: FUN_004163d4
// callees: FUN_00450094

undefined4 FUN_00416364(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  
  if (DAT_004d5b00 == '\x02') {
    iVar2 = 0;
    piVar4 = &DAT_0065e3e8;
    pcVar3 = &DAT_0059f161;
    do {
      if (((((1 << ((byte)iVar2 & 0x1f) & (int)DAT_0059f0fc) != 0) && (*pcVar3 != '\0')) &&
          (DAT_004d5af8 <= *piVar4)) &&
         ((iVar2 != DAT_0058f1f4 || (iVar1 = FUN_00450094(), iVar1 != 0)))) {
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 1;
      pcVar3 = pcVar3 + 0x2d8;
    } while (iVar2 < 7);
  }
  return 0;
}

