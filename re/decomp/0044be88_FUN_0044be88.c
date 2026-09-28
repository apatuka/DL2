// FUN_0044be88 @ 0044be88 size=30 sig=undefined FUN_0044be88() cc=unknown
// callers: FUN_0044bea8
// callees: FUN_0044ba40

undefined4 FUN_0044be88(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0044ba40(param_1);
  if ((param_1 != 0) && ((*(byte *)(param_1 + 2) & 4) == 0)) {
    uVar1 = 0;
  }
  return uVar1;
}

