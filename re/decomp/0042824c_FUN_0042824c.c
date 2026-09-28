// FUN_0042824c @ 0042824c size=104 sig=undefined FUN_0042824c() cc=unknown
// callers: FUN_00427ee8
// callees: FUN_004a4025,FUN_0044a000,FUN_004691f8,FUN_004493dc

void FUN_0042824c(int param_1)

{
  FUN_004a4025(*(undefined4 *)(param_1 + 4));
  *(undefined4 *)(param_1 + 4) = 0;
  DAT_004b7d94 = *(undefined4 *)(param_1 + 0xc);
  DAT_004d59b4 = *(int *)(param_1 + 8);
  if (((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) && (DAT_004c48a0 == 0)) {
    DAT_004d59b4 = 0x32;
  }
  FUN_004493dc(0);
  if (DAT_004d5978 == 0) {
    FUN_0044a000();
  }
  else {
    FUN_004691f8();
  }
  return;
}

