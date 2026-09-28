// FUN_00436098 @ 00436098 size=82 sig=undefined FUN_00436098() cc=unknown
// callers: RaceInit,FUN_00468ea4,FUN_004399dc,FUN_00430abc,FUN_004618e8,FUN_00438fe0,WinMain
// callees: FUN_004a2004,FUN_004a3de6,FUN_00414f04,FUN_004493dc

undefined4 FUN_00436098(void)

{
  DAT_004c4658 = FUN_004a3de6(0,0x39303044);
  if (DAT_004c4658 != 0) {
    FUN_004493dc(1);
    DAT_00558ea8 = DAT_004d59b4;
    DAT_004d59b4 = 0x2a;
    FUN_00414f04(DAT_004c4658);
    FUN_004a2004(DAT_004c4658);
    return 1;
  }
  return 0;
}

