// FUN_00492498 @ 00492498 size=224 sig=undefined FUN_00492498() cc=unknown
// callers: 
// callees: FUN_00492083

void FUN_00492498(undefined1 *param_1,int *param_2)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  short local_a;
  
  if (DAT_0065ebf8 != 0) {
    iVar3 = DAT_0065ec4c + DAT_0065ec38;
    local_a = 0;
    sVar5 = 0;
    while (sVar2 = FUN_00492083(*param_1), sVar2 != 0) {
      uVar1 = *(ushort *)(iVar3 + ((int)sVar2 - (int)DAT_0065ec20) * 2);
      if (uVar1 == 0xffff) {
        uVar1 = *(ushort *)(iVar3 + DAT_0065ec70 * 2);
      }
      sVar4 = (char)(uVar1 >> 8) + sVar5 + (short)DAT_0065ec24;
      if (sVar4 < local_a) {
        local_a = sVar4;
      }
      sVar5 = (short)DAT_0065ec28;
      if (sVar2 == 0x20) {
        sVar5 = (short)DAT_0065ec2c;
      }
      sVar5 = (uVar1 & 0xff) + sVar4 + sVar5;
      param_1 = param_1 + 1;
    }
    *param_2 = (int)local_a;
    param_2[2] = (int)sVar5;
    param_2[1] = -DAT_0065ebfc;
    param_2[3] = DAT_0065ec00;
  }
  return;
}

