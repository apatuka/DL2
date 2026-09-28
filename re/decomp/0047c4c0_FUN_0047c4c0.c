// FUN_0047c4c0 @ 0047c4c0 size=54 sig=undefined FUN_0047c4c0() cc=unknown
// callers: FUN_004782ec
// callees: memcpy

void FUN_0047c4c0(int param_1)

{
  if (DAT_004dc3c4 != 0) {
    memcpy(&DAT_006541f0 + DAT_006541e8,param_1 + 0x18,0x40);
    DAT_006541e8 = DAT_006541e8 + 0x40;
  }
  return;
}

