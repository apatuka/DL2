// FUN_004766e8 @ 004766e8 size=117 sig=undefined FUN_004766e8() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00475048,FUN_00472448
// strings: \"Error in Net Transfer Materials.\"

bool FUN_004766e8(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00472448(&DAT_005a43d0 + ((int)(uint)*(ushort *)(param_1 + 0x18) >> 8) * 0xadc,
                       &DAT_005a43d0 + (*(ushort *)(param_1 + 0x18) & 0xff) * 0xadc,
                       (int)(uint)*(ushort *)(param_1 + 0x1c) >> 8,*(undefined2 *)(param_1 + 0x1a),
                       *(ushort *)(param_1 + 0x1c) & 0xff);
  if (iVar1 == -1) {
    FUN_00475048(s_Error_in_Net_Transfer_Materials__004dc15c,param_1);
  }
  return iVar1 != -1;
}

