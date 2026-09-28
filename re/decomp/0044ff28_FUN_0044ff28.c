// FUN_0044ff28 @ 0044ff28 size=87 sig=undefined FUN_0044ff28() cc=unknown
// callers: FUN_0041026c,FUN_004383a4,FUN_004101d4
// callees: FUN_0044fe1c

undefined4 FUN_0044ff28(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0044fe1c(7);
  if ((iVar1 == 0) ||
     ((((((param_1 != 9 && (param_1 != 10)) && (param_1 != 0xb)) &&
        ((param_1 != 0x10 && (param_1 != 0x11)))) &&
       ((param_1 != 0x12 && ((param_1 != 0x14 && (param_1 != 0x1c)))))) &&
      ((param_1 != 0x22 && ((param_1 != 0x23 && (param_1 != 0x24)))))))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

