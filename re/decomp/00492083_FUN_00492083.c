// FUN_00492083 @ 00492083 size=63 sig=undefined FUN_00492083() cc=unknown
// callers: FUN_00492578,FUN_004920d1,FUN_00492391,FUN_00492146,FUN_00492290,FUN_00492498,FUN_00492307,FUN_004921f8
// callees: 

undefined4 FUN_00492083(undefined4 param_1)

{
  short *psVar1;
  int iVar2;
  
  if (DAT_0051dc1c != (short *)0x0) {
    psVar1 = DAT_0051dc1c + 1;
    for (iVar2 = 0; iVar2 < *DAT_0051dc1c; iVar2 = iVar2 + 1) {
      if ((short)param_1 == *psVar1) {
        return CONCAT22((short)((uint)psVar1 >> 0x10),psVar1[1]);
      }
      psVar1 = psVar1 + 2;
    }
  }
  return param_1;
}

