// FUN_00403350 @ 00403350 size=128 sig=undefined FUN_00403350() cc=unknown
// callers: FUN_004034b8,FUN_00405430,FUN_004033d0,FUN_00403684
// callees: FUN_0045093c,FUN_0040beb4

undefined4 FUN_00403350(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  uVar1 = 1 << ((byte)param_2 & 0x1f);
  if ((uVar1 & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0) {
    uVar2 = 0;
  }
  else {
    *(uint *)(&DAT_0052222c + param_1 * 4) = *(uint *)(&DAT_0052222c + param_1 * 4) & ~uVar1;
    FUN_0045093c(param_1,uVar1,0xffffffff,1,0,0,0);
    for (puVar3 = &DAT_00522584 + param_1 * 0x2648; puVar3 < &DAT_00524bcc + param_1 * 0x2648;
        puVar3 = puVar3 + 0xc4) {
      if (param_2 == *(short *)(puVar3 + 8)) {
        FUN_0040beb4(puVar3);
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

