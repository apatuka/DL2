// FUN_0044ff80 @ 0044ff80 size=57 sig=undefined FUN_0044ff80() cc=unknown
// callers: FUN_0040ba64
// callees: FUN_0044fe1c

undefined4 FUN_0044ff80(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0044fe1c(7);
  if ((iVar1 == 0) ||
     ((((param_1 != 3 && (param_1 != 0xd)) && (param_1 != 9)) &&
      ((param_1 != 0x12 && (param_1 != 0x13)))))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

