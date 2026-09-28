// FUN_00491bf7 @ 00491bf7 size=311 sig=undefined FUN_00491bf7() cc=unknown
// callers: FUN_0049eb9f,FUN_004a58ce,FUN_00491a2b,FUN_00491ace,FUN_004a57e0
// callees: FUN_00491b46,FUN_00491b5e,FUN_00491b9c,FUN_00498aab

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00491bf7(int param_1)

{
  int iVar1;
  ushort *puVar2;
  undefined1 local_10 [4];
  short local_c;
  short local_a;
  short local_8;
  short local_6;
  
  if (param_1 != DAT_0051dc10) {
    FUN_00491b9c(0);
  }
  if (param_1 == 0) {
    DAT_0065ebf8 = 0;
  }
  else {
    if (param_1 != DAT_0051dc10) {
      iVar1 = FUN_00498aab(param_1,1);
      DAT_0065ebf8 = iVar1 + 2;
      DAT_0051dc10 = param_1;
    }
    FUN_00491b5e(local_10);
    DAT_0065ebfc = (int)local_c;
    DAT_0065ec00 = (int)local_a;
    _DAT_0065ec04 = (int)local_8;
    _DAT_0065ec08 = (int)local_6;
    DAT_0065ec4c = FUN_00491b46(DAT_0065ebf8);
    DAT_0065ec20 = *(short *)(DAT_0065ec4c + 2);
    DAT_0065ec22 = *(short *)(DAT_0065ec4c + 4);
    DAT_0065ec24 = (int)*(short *)(DAT_0065ec4c + 8);
    DAT_0065ec30 = (uint)*(ushort *)(DAT_0065ec4c + 0x18) * 2;
    DAT_0065ec0c = (uint)*(ushort *)(DAT_0065ec4c + 0xe);
    DAT_0065ec70 = (DAT_0065ec22 - DAT_0065ec20) + 1;
    DAT_0065ec38 = (uint)*(ushort *)(DAT_0065ec4c + 0x10) * 2 + 0x10;
    _DAT_0065ec34 = DAT_0065ec38 + (DAT_0065ec70 + 2) * -2;
    DAT_0065ec28 = 0;
    DAT_0065ec2c = 0;
    puVar2 = (ushort *)((0x20 - DAT_0065ec20) * 2 + DAT_0065ec4c + DAT_0065ec38);
    *puVar2 = *puVar2 & 0xff;
  }
  return;
}

