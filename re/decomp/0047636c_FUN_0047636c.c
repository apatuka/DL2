// FUN_0047636c @ 0047636c size=218 sig=undefined FUN_0047636c() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00475040,FUN_00475048,_MovePopulation
// strings: \"Error in Net Move Population!\"

bool FUN_0047636c(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  
  sVar1 = *(short *)(param_1 + 0x1e);
  sVar2 = *(short *)(param_1 + 0x20);
  if ((sVar1 != -1) && (sVar2 != -1)) {
    if ((&DAT_005a4524)[(uint)*(ushort *)(param_1 + 0x1a) * 0x2b7 + sVar1 * 0xd] == 0) {
      FUN_00475040(*(undefined4 *)(param_1 + 4));
      return false;
    }
    if (*(int *)((&DAT_005a4524)[(uint)*(ushort *)(param_1 + 0x1a) * 0x2b7 + sVar1 * 0xd] + 0x18 +
                sVar2 * 4) == 0) {
      FUN_00475040(*(undefined4 *)(param_1 + 4));
      return false;
    }
  }
  iVar3 = _MovePopulation(&DAT_005a43d0 + (uint)*(ushort *)(param_1 + 0x1a) * 0xadc,
                          &DAT_005a43d0 + (uint)*(ushort *)(param_1 + 0x1c) * 0xadc,
                          *(ushort *)(param_1 + 0x18) & 0x3fff,
                          (*(ushort *)(param_1 + 0x18) & 0x4000) != 0,sVar1,
                          CONCAT22((short)((uint)(&DAT_005a43d0 +
                                                 (uint)*(ushort *)(param_1 + 0x1c) * 0xadc) >> 0x10)
                                   ,sVar2));
  if (iVar3 == 0) {
    FUN_00475048(s_Error_in_Net_Move_Population__004dc13e,param_1);
  }
  return iVar3 != 0;
}

