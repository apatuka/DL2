// FUN_00492307 @ 00492307 size=138 sig=undefined FUN_00492307() cc=unknown
// callers: FUN_00492d67
// callees: FUN_00492083

void FUN_00492307(undefined4 param_1,int *param_2)

{
  short sVar1;
  short sVar2;
  int iVar3;
  
  if (DAT_0065ebf8 != 0) {
    iVar3 = DAT_0065ec4c + DAT_0065ec38;
    sVar1 = FUN_00492083(param_1);
    sVar2 = *(short *)(iVar3 + (short)(sVar1 - DAT_0065ec20) * 2);
    if (sVar2 == -1) {
      sVar2 = *(short *)(iVar3 + DAT_0065ec70 * 2);
    }
    iVar3 = DAT_0065ec24;
    if ((short)(sVar1 - DAT_0065ec20) == 0x20) {
      iVar3 = 0;
    }
    *param_2 = (char)((ushort)sVar2 >> 8) + iVar3;
    param_2[2] = (int)sVar2 & 0xff;
    param_2[1] = -DAT_0065ebfc;
    param_2[3] = DAT_0065ec00;
  }
  return;
}

