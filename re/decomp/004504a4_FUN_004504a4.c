// FUN_004504a4 @ 004504a4 size=66 sig=undefined FUN_004504a4() cc=unknown
// callers: FUN_00404cec,FUN_004046e8
// callees: FUN_0046ca40

uint FUN_004504a4(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(&DAT_004ca3b4 + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 8 + param_2 * 0x38);
  uVar2 = FUN_0046ca40();
  return uVar2 % uVar1;
}

