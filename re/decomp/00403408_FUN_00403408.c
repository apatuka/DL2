// FUN_00403408 @ 00403408 size=173 sig=undefined FUN_00403408() cc=unknown
// callers: FUN_00403750,FUN_0040350c
// callees: FUN_0045093c,FUN_004033d0,FUN_004071b0,FUN_0046ca40

undefined4 FUN_00403408(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_2 < 0) {
    uVar1 = 0;
  }
  else if (((1 << ((byte)param_2 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0) &&
          ((((&DAT_005a0548)[param_1] != '\x04' || ((char)(&DAT_0059f161)[param_2 * 0x2d8] < '\x03')
            ) && (*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) < 8)))) {
    FUN_004033d0(param_1);
    FUN_004071b0(param_1,param_2);
    uVar3 = 1 << ((byte)param_2 & 0x1f);
    *(uint *)(&DAT_0052222c + param_1 * 4) = *(uint *)(&DAT_0052222c + param_1 * 4) | uVar3;
    uVar2 = FUN_0046ca40();
    if ((uVar2 & 1) == 0) {
      FUN_0045093c(param_1,uVar3,0xffffffff,0,param_2,0,0);
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

