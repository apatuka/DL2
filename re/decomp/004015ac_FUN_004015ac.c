// FUN_004015ac @ 004015ac size=194 sig=undefined FUN_004015ac() cc=unknown
// callers: FUN_00401670,FUN_004015ac
// callees: FUN_004412d4,FUN_004015ac

undefined4 FUN_004015ac(int param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  ushort *local_c;
  int local_8;
  
  if (*(short *)(param_1 + 0x30) == 0) {
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x200 << ((byte)param_2 & 0x1f);
    local_c = (ushort *)(param_1 + 0x890);
    local_8 = 0;
    do {
      uVar2 = *local_c;
      for (iVar3 = 0; (uVar2 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
        if (((uVar2 & 1) != 0) &&
           ((iVar1 = local_8 * 0x10 + iVar3,
            (0x200 << ((byte)param_2 & 0x1f) & (&DAT_005a43ec)[iVar1 * 0x2b7]) == 0 &&
            (iVar1 = FUN_004015ac(&DAT_005a43d0 + iVar1 * 0xadc,param_2), iVar1 != 0)))) {
          return 1;
        }
        uVar2 = (short)uVar2 >> 1;
      }
      local_8 = local_8 + 1;
      local_c = local_c + 1;
    } while (local_8 < 7);
  }
  else if ((param_2 != *(char *)(param_1 + 0x20)) &&
          (iVar3 = FUN_004412d4(param_2,(int)*(char *)(param_1 + 0x20),2), iVar3 == 0)) {
    return 1;
  }
  return 0;
}

