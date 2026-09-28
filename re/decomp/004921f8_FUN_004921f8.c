// FUN_004921f8 @ 004921f8 size=152 sig=undefined FUN_004921f8() cc=unknown
// callers: FUN_00419110,FUN_0049ebfb
// callees: FUN_00492083

int FUN_004921f8(char *param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  short sVar4;
  short local_6;
  
  if (DAT_0065ebf8 == 0) {
    iVar3 = 0;
  }
  else if (param_1 == (char *)0x0) {
    iVar3 = 0;
  }
  else {
    iVar3 = DAT_0065ec4c + DAT_0065ec38;
    local_6 = 0;
    for (; *param_1 != '\0'; param_1 = param_1 + 1) {
      sVar1 = FUN_00492083(*param_1);
      uVar2 = *(ushort *)(iVar3 + ((int)sVar1 - (int)DAT_0065ec20) * 2);
      if (uVar2 == 0xffff) {
        uVar2 = *(ushort *)(iVar3 + DAT_0065ec70 * 2);
      }
      sVar4 = (short)DAT_0065ec2c;
      if (sVar1 != 0x20) {
        sVar4 = (short)DAT_0065ec28 + (short)DAT_0065ec24;
      }
      local_6 = local_6 + (uVar2 & 0xff) + sVar4;
    }
    iVar3 = (int)local_6;
  }
  return iVar3;
}

