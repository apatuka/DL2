// FUN_00476fb8 @ 00476fb8 size=67 sig=undefined FUN_00476fb8() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0045f148,FUN_00449760

void FUN_00476fb8(int param_1)

{
  if (*(ushort *)(param_1 + 0x18) == DAT_0059f154) {
    if ((&DAT_0059f168)[*(short *)(param_1 + 0x16) * 0x2d8] == '\0') {
      (&DAT_0059f168)[*(short *)(param_1 + 0x16) * 0x2d8] = 1;
    }
    FUN_0045f148();
    FUN_00449760();
  }
  return;
}

