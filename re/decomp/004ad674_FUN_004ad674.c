// FUN_004ad674 @ 004ad674 size=81 sig=undefined FUN_004ad674() cc=unknown
// callers: FUN_004ae670,FUN_004ae928,FUN_004ae974,FUN_004ae62c
// callees: 

undefined4 FUN_004ad674(int param_1)

{
  if (param_1 < 0x11) {
    if (param_1 == 0x10) {
      return *(undefined4 *)(*(int *)(PTR_DAT_00520d10 + 0x18) + 8);
    }
    if (param_1 == 0xe) {
      return *(undefined4 *)(*(int *)(PTR_DAT_00520d10 + 0x18) + 4);
    }
    if (param_1 == 0xf) {
      return **(undefined4 **)(PTR_DAT_00520d10 + 0x18);
    }
  }
  else {
    if (param_1 == 0x50) {
      return *(undefined4 *)(*(int *)(PTR_DAT_00520d10 + 0x18) + 0xc);
    }
    if (param_1 == 0x51) {
      return *(undefined4 *)(*(int *)(PTR_DAT_00520d10 + 0x18) + 0x10);
    }
  }
  return 0;
}

