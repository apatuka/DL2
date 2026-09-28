// FUN_00401670 @ 00401670 size=165 sig=undefined FUN_00401670() cc=unknown
// callers: FUN_004096a8,FUN_0040e384,FUN_00401718
// callees: FUN_004015ac,FUN_0045dfb0,FUN_00448314

uint FUN_00401670(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  ushort *local_10;
  int local_c;
  uint local_8;
  
  local_8 = 0;
  if (param_2 == -1) {
    local_8 = 0;
  }
  else {
    local_c = 0;
    local_10 = (ushort *)(param_1 + 0x890);
    do {
      uVar3 = *local_10;
      for (iVar4 = 0; (uVar3 != 0 && (iVar4 < 0x10)); iVar4 = iVar4 + 1) {
        if ((uVar3 & 1) != 0) {
          FUN_0045dfb0(0x200 << ((byte)param_2 & 0x1f));
          iVar1 = FUN_004015ac(&DAT_005a43d0 + (local_c * 0x10 + iVar4) * 0xadc,param_2);
          if (iVar1 != 0) {
            uVar2 = FUN_00448314(&DAT_005a43d0 + (local_c * 0x10 + iVar4) * 0xadc,param_1,0);
            local_8 = local_8 | uVar2;
          }
        }
        uVar3 = (short)uVar3 >> 1;
      }
      local_c = local_c + 1;
      local_10 = local_10 + 1;
    } while (local_c < 7);
  }
  return local_8;
}

