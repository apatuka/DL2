// FUN_00492146 @ 00492146 size=178 sig=undefined FUN_00492146() cc=unknown
// callers: 
// callees: FUN_00492083

int FUN_00492146(byte *param_1)

{
  byte bVar1;
  short sVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  short sVar6;
  
  if (DAT_0065ebf8 == 0) {
    iVar5 = 0;
  }
  else if (param_1 == (byte *)0x0) {
    iVar5 = 0;
  }
  else {
    iVar5 = DAT_0065ec4c + DAT_0065ec38;
    bVar1 = *param_1;
    sVar4 = 0;
    sVar6 = 0;
    if (bVar1 != 0) {
      do {
        param_1 = param_1 + 1;
        sVar2 = FUN_00492083(*param_1);
        uVar3 = *(ushort *)(iVar5 + ((int)sVar2 - (int)DAT_0065ec20) * 2);
        if (uVar3 == 0xffff) {
          uVar3 = *(ushort *)(iVar5 + DAT_0065ec70 * 2);
        }
        sVar4 = (short)DAT_0065ec2c;
        if (sVar2 != 0x20) {
          sVar4 = (short)DAT_0065ec28 + (short)DAT_0065ec24;
        }
        sVar4 = (uVar3 & 0xff) + sVar4;
        sVar6 = sVar6 + 1;
      } while (sVar6 < (short)(ushort)bVar1);
    }
    iVar5 = (int)sVar4;
  }
  return iVar5;
}

