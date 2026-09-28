// FUN_004920d1 @ 004920d1 size=117 sig=undefined FUN_004920d1() cc=unknown
// callers: FUN_0049f978
// callees: FUN_00492083

int FUN_004920d1(undefined4 param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  short sVar4;
  
  if (DAT_0065ebf8 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = DAT_0065ec4c + DAT_0065ec38;
    sVar1 = FUN_00492083(param_1);
    uVar2 = *(ushort *)(iVar3 + ((int)sVar1 - (int)DAT_0065ec20) * 2);
    if (uVar2 == 0xffff) {
      uVar2 = *(ushort *)(iVar3 + DAT_0065ec70 * 2);
    }
    sVar4 = (short)DAT_0065ec2c;
    if (sVar1 != 0x20) {
      sVar4 = (short)DAT_0065ec28 + (short)DAT_0065ec24;
    }
    iVar3 = (int)(short)((uVar2 & 0xff) + sVar4);
  }
  return iVar3;
}

