// FUN_00492391 @ 00492391 size=263 sig=undefined FUN_00492391() cc=unknown
// callers: 
// callees: FUN_00492083

void FUN_00492391(byte *param_1,int *param_2)

{
  byte bVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  short local_e;
  short local_c;
  
  if (DAT_0065ebf8 != 0) {
    iVar4 = DAT_0065ec4c + DAT_0065ec38;
    bVar1 = *param_1;
    local_e = 0;
    sVar6 = 0;
    local_c = 0;
    if (bVar1 != 0) {
      do {
        param_1 = param_1 + 1;
        sVar2 = FUN_00492083(*param_1);
        uVar3 = *(ushort *)(iVar4 + ((int)sVar2 - (int)DAT_0065ec20) * 2);
        if (uVar3 == 0xffff) {
          uVar3 = *(ushort *)(iVar4 + DAT_0065ec70 * 2);
        }
        sVar5 = (char)(uVar3 >> 8) + sVar6 + (short)DAT_0065ec24;
        if (sVar5 < local_e) {
          local_e = sVar5;
        }
        sVar6 = (short)DAT_0065ec28;
        if (sVar2 == 0x20) {
          sVar6 = (short)DAT_0065ec2c;
        }
        sVar6 = (uVar3 & 0xff) + sVar5 + sVar6;
        local_c = local_c + 1;
      } while (local_c < (short)(ushort)bVar1);
    }
    *param_2 = (int)local_e;
    param_2[2] = (int)sVar6;
    param_2[1] = -DAT_0065ebfc;
    param_2[3] = DAT_0065ec00;
  }
  return;
}

