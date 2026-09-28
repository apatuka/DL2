// FUN_004767c8 @ 004767c8 size=37 sig=undefined FUN_004767c8() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: 

void FUN_004767c8(int param_1)

{
  if (*(short *)(param_1 + 0x16) != DAT_0058f1f4) {
    *(uint *)(&DAT_006534fc + (uint)*(ushort *)(param_1 + 0x18) * 4) =
         (uint)*(ushort *)(param_1 + 0x1a);
  }
  return;
}

