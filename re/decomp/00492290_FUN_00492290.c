// FUN_00492290 @ 00492290 size=119 sig=undefined FUN_00492290() cc=unknown
// callers: FUN_0048447c,FUN_00492b47,FUN_004844e0,FUN_004931b0,FUN_0049331e
// callees: FUN_00492083

int FUN_00492290(undefined4 param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  
  if (DAT_0065ebf8 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = DAT_0065ec4c + DAT_0065ec38;
    sVar1 = FUN_00492083(param_1);
    sVar3 = *(short *)(iVar2 + ((int)sVar1 - (int)DAT_0065ec20) * 2);
    if (sVar3 == -1) {
      sVar3 = *(short *)(iVar2 + ((int)DAT_0065ec70 - (int)DAT_0065ec20) * 2);
      sVar1 = DAT_0065ec70;
    }
    iVar2 = DAT_0065ec28;
    if (sVar1 == 0x20) {
      iVar2 = DAT_0065ec2c;
    }
    iVar2 = ((int)sVar3 & 0xffU) + iVar2;
  }
  return iVar2;
}

