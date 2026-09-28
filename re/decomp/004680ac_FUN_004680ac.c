// FUN_004680ac @ 004680ac size=53 sig=undefined FUN_004680ac() cc=unknown
// callers: 
// callees: FUN_0043a1f8,FUN_0043694c

undefined4 FUN_004680ac(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0043694c(0x2c);
  if (iVar1 == 5) {
    return 0x15;
  }
  if (iVar1 != 6) {
    if (iVar1 != 8) {
      return 0x35;
    }
    return 0x3c;
  }
  uVar2 = FUN_0043a1f8(3);
  return uVar2;
}

