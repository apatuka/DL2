// FUN_0040e10c @ 0040e10c size=88 sig=undefined FUN_0040e10c() cc=unknown
// callers: 
// callees: FUN_0040bbf4,FUN_0046ca40

void FUN_0040e10c(int param_1)

{
  uint uVar1;
  
  uVar1 = FUN_0046ca40();
  *(undefined **)(param_1 + 0x10) = &DAT_005a43d0 + (uVar1 % (uint)(int)DAT_004d5b18) * 0xadc;
  uVar1 = FUN_0046ca40();
  *(undefined **)(param_1 + 0x10) = &DAT_005a43d0 + (uVar1 % (uint)(int)DAT_004d5b18) * 0xadc;
  FUN_0040bbf4(param_1,0,0);
  return;
}

