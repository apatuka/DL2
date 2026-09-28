// FUN_00427a0c @ 00427a0c size=96 sig=undefined FUN_00427a0c() cc=unknown
// callers: FUN_00477604,FUN_004775c8
// callees: FUN_00426bd0,FUN_00427278,FUN_00426eb8,FUN_0042726c

void FUN_00427a0c(int param_1,int param_2)

{
  (&DAT_0059f166)[param_1 * 0x16c] = (short)param_2;
  (&DAT_005a43f0)[param_2 * 0xadc] = (char)param_1;
  FUN_00426bd0(DAT_00557784);
  if (DAT_004d59b4 == 0x4a) {
    FUN_00426eb8();
    FUN_00427278();
    FUN_0042726c();
  }
  return;
}

