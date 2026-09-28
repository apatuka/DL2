// FUN_00476668 @ 00476668 size=126 sig=undefined FUN_00476668() cc=unknown
// callers: FUN_0045ca3c
// callees: FUN_004723cc,FUN_004779c0,FUN_00474d90

undefined4 FUN_00476668(int param_1,int param_2,undefined4 *param_3)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  if (DAT_0058f1fc == 0) {
    uVar4 = FUN_004723cc(param_1,param_2,param_3);
  }
  else {
    sVar1 = *(short *)(param_1 + 0x1a);
    iVar5 = 1;
    uVar2 = *(ushort *)(param_2 + 0x1a);
    do {
      param_3 = param_3 + 1;
      FUN_004779c0((int)*(char *)(param_1 + 0x20),0x27,(int)(short)(sVar1 << 8 | uVar2),iVar5,
                   *param_3,0,0);
      iVar3 = FUN_00474d90(0x27,(int)*(char *)(param_1 + 0x20));
      if (iVar3 == 0) {
        return 0;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0xb);
    uVar4 = 1;
  }
  return uVar4;
}

