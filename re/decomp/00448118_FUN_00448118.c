// FUN_00448118 @ 00448118 size=137 sig=undefined FUN_00448118() cc=unknown
// callers: FUN_00447bc0,FUN_00455a04
// callees: FUN_004482cc,FUN_00447a40

int FUN_00448118(int param_1)

{
  int iVar1;
  int *piVar2;
  int local_c;
  int local_8;
  
  iVar1 = FUN_004482cc(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_00447a40((int)*(short *)(param_1 + 10));
    local_8 = iVar1 * 0xf +
              (int)*(short *)(&DAT_0055a076 +
                             (char)(&DAT_0059f162)[(uint)*(byte *)(param_1 + 0x1e) * 0x2d8] * 2) +
              *(int *)(&DAT_004c52c8 + (char)(&DAT_005a0548)[*(byte *)(param_1 + 0x1e)] * 4) + 0x32;
    local_c = 100;
    if (local_8 < 0x65) {
      piVar2 = &local_8;
    }
    else {
      piVar2 = &local_c;
    }
    iVar1 = *piVar2;
  }
  else {
    iVar1 = 100;
  }
  return iVar1;
}

