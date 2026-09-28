// FUN_004071b0 @ 004071b0 size=150 sig=undefined FUN_004071b0() cc=unknown
// callers: FUN_00403408
// callees: FUN_00476aac,FUN_00476ae4,FUN_0046ca40

void FUN_004071b0(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if ((&DAT_0059f3da)[param_1 * 0xb6 + param_2] != 0) {
    iVar1 = *(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c);
    uVar2 = FUN_0046ca40();
    if ((int)(uVar2 % 100) < (iVar1 * -100) / 0x32) {
      FUN_00476ae4(param_1,param_2,(&DAT_0059f3da)[param_1 * 0xb6 + param_2]);
    }
    else {
      FUN_00476aac(param_1,param_2,(&DAT_0059f3da)[param_1 * 0xb6 + param_2]);
    }
  }
  return;
}

