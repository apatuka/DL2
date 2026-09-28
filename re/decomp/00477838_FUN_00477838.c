// FUN_00477838 @ 00477838 size=79 sig=undefined FUN_00477838() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0044dcf4

bool FUN_00477838(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0044dcf4(&DAT_005a43d0 + (uint)*(ushort *)(param_1 + 0x1a) * 0xadc,
                       *(undefined2 *)(param_1 + 0x18),*(undefined2 *)(param_1 + 0x1c),
                       *(undefined2 *)(param_1 + 0x20),*(undefined2 *)(param_1 + 0x1e));
  return iVar1 != 0;
}

