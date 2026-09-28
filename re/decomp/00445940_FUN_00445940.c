// FUN_00445940 @ 00445940 size=123 sig=undefined FUN_00445940() cc=unknown
// callers: FUN_00445b94,FUN_00445a04
// callees: 

int FUN_00445940(int param_1)

{
  int iVar1;
  int *piVar2;
  
  do {
    if (param_1 == 0) {
      return 0;
    }
    if ((*(char *)(param_1 + 6) == '\f') &&
       ((((DAT_004c5140 == 0 ||
          ((char)(&DAT_0059f161)[*(char *)(DAT_004c5140 + 8) * 0x2d8] < '\x03')) ||
         (*(short *)(DAT_004c5140 + 0x36) == *(short *)(param_1 + 0x36))) ||
        (DAT_0058f1f4 != DAT_004d5a58)))) {
      iVar1 = 0;
      piVar2 = (int *)(param_1 + 0x48);
      do {
        if (*piVar2 == 0) {
          return param_1;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar1 < 3);
    }
    param_1 = *(int *)(param_1 + 0x54);
  } while( true );
}

