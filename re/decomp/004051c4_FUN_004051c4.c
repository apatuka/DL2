// FUN_004051c4 @ 004051c4 size=168 sig=undefined FUN_004051c4() cc=unknown
// callers: FUN_0040526c
// callees: 

undefined4 FUN_004051c4(int param_1,int param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  if ((&DAT_005a0548)[param_1] == '\x04') {
    uVar1 = 1;
  }
  else {
    if (DAT_004d5a94 != 0) {
      iVar3 = 0;
      piVar2 = (int *)(&DAT_004b57c0 + DAT_004d5a94 * 0x30);
      do {
        if (((((int)(char)(&DAT_0059f162)[param_1 * 0x2d8] == *piVar2) || (*piVar2 == 7)) &&
            (((int)(char)(&DAT_0059f162)[param_2 * 0x2d8] == piVar2[1] || (piVar2[1] == 7)))) &&
           (piVar2[3] != 0)) {
          return 1;
        }
        iVar3 = iVar3 + 1;
        piVar2 = piVar2 + 4;
      } while (iVar3 < 3);
    }
    uVar1 = 0;
  }
  return uVar1;
}

