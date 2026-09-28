// FUN_00497bea @ 00497bea size=168 sig=undefined FUN_00497bea() cc=unknown
// callers: FUN_00498196,FUN_00497fa4
// callees: FUN_0048fade,FUN_0048f992,FUN_0048f877

void FUN_00497bea(int param_1,undefined4 param_2,undefined4 *param_3)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  short sVar6;
  
  uVar2 = FUN_0048f877(*(undefined4 *)(param_1 + 4));
  uVar3 = uVar2;
  if (0x300 < (int)uVar2) {
    uVar3 = 0x300;
  }
  uVar4 = FUN_0048f992(param_2,param_3,uVar3);
  if (uVar4 == uVar3) {
    sVar1 = (short)((int)uVar3 / 3);
    sVar6 = 0;
    if (0 < sVar1) {
      do {
        uVar5 = FUN_0048f877(*param_3);
        *(char *)param_3 = (char)((uint)uVar5 >> 0x18);
        *(char *)((int)param_3 + 1) = (char)((uint)uVar5 >> 0x10);
        *(char *)((int)param_3 + 2) = (char)((uint)uVar5 >> 8);
        param_3 = (undefined4 *)((int)param_3 + 6);
        sVar6 = sVar6 + 1;
      } while (sVar6 < sVar1);
    }
    if ((uVar2 & 1) != 0) {
      uVar2 = uVar2 + 1;
    }
    if (0 < (int)(uVar2 - uVar3)) {
      FUN_0048fade(param_2,uVar2 - uVar3,1);
    }
  }
  return;
}

