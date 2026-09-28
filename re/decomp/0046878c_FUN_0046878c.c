// FUN_0046878c @ 0046878c size=69 sig=undefined FUN_0046878c() cc=unknown
// callers: 
// callees: FUN_0042c054,FUN_00466ddc

undefined4 FUN_0046878c(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0042c054();
  if (iVar1 == 0x3a) {
    return 0x55;
  }
  if (iVar1 == 0x3b) {
    iVar1 = FUN_00466ddc();
    if (iVar1 == 0) {
      return 0x3e;
    }
    uVar2 = 0x43;
    if (DAT_004d5a50 != 0) {
      return 0x40;
    }
  }
  else {
    if (iVar1 == 0x3c) {
      return 0x3d;
    }
    uVar2 = 0x3d;
  }
  return uVar2;
}

