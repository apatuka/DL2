// FUN_00441c28 @ 00441c28 size=103 sig=undefined FUN_00441c28() cc=unknown
// callers: FUN_00427ab0,FUN_00427854
// callees: 

int FUN_00441c28(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort *local_c;
  int local_8;
  
  local_8 = 0;
  iVar2 = 0;
  local_c = (ushort *)(param_1 + 0x890);
  do {
    uVar1 = *local_c;
    for (iVar3 = 0; (uVar1 != 0 && (iVar3 < 0x10)); iVar3 = iVar3 + 1) {
      if (((uVar1 & 1) != 0) && ((&DAT_005a43f1)[(iVar2 * 0x10 + iVar3) * 0xadc] != '\0')) {
        local_8 = local_8 + 1;
      }
      uVar1 = (short)uVar1 >> 1;
    }
    iVar2 = iVar2 + 1;
    local_c = local_c + 1;
  } while (iVar2 < 7);
  return local_8;
}

