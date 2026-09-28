// FUN_0047c4f8 @ 0047c4f8 size=66 sig=undefined FUN_0047c4f8() cc=unknown
// callers: FUN_004782ec
// callees: FUN_00478fec

void FUN_0047c4f8(int param_1)

{
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)(param_1 + 0x1a) << 8 | (uint)*(ushort *)(param_1 + 0x1c);
  if (DAT_004dc3c4 != 0) {
    FUN_00478fec(&DAT_006541f0,DAT_006541ec,uVar1);
    DAT_006541ec = DAT_006541ec + uVar1;
    DAT_006541e8 = 0;
  }
  return;
}

