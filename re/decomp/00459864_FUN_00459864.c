// FUN_00459864 @ 00459864 size=226 sig=undefined FUN_00459864() cc=unknown
// callers: FUN_00459948,FUN_0047f728,FUN_00480150,FUN_00459a3c,FUN_00459c48,FUN_0047f670
// callees: FUN_00496c61,FUN_0049a93f,FUN_0049a8ed,FUN_00498aab,FUN_0048d2e7,FUN_0049a760,FUN_0048d32c,FUN_0049aa95,FUN_0049a9e7

void FUN_00459864(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 local_8 [3];
  byte local_5;
  
  uVar1 = FUN_00498aab(param_1,1);
  piVar2 = (int *)FUN_00496c61(uVar1,param_2,param_3,0,0,0,0,local_8);
  if ((piVar2 != (int *)0x0) && ((local_5 & 0x40) == 0)) {
    FUN_0048d2e7(DAT_004d5c28);
    uVar3 = 8;
    if ((*(byte *)(*piVar2 + 8) & 3) != 0) {
      uVar3 = 0x10;
    }
    uVar1 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | uVar3);
    local_18 = DAT_004c5458;
    local_10 = DAT_004c5458 + DAT_004c5460;
    local_14 = DAT_004c545c;
    local_c = DAT_004c545c + DAT_004c5464;
    FUN_0049a8ed();
    FUN_0049a9e7(&local_18);
    FUN_0049aa95(*piVar2,param_4,param_5,(int)*(short *)(*piVar2 + 0xe),0);
    FUN_0049a93f();
    FUN_0049a760(uVar1);
    FUN_0048d32c();
  }
  FUN_00498aab(param_1,0);
  return;
}

