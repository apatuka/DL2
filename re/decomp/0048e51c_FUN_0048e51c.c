// FUN_0048e51c @ 0048e51c size=20 sig=undefined FUN_0048e51c() cc=unknown
// callers: FUN_00493ad3
// callees: FUN_0048ddd1

uint FUN_0048e51c(void)

{
  uint uVar1;
  
  uVar1 = FUN_0048ddd1();
  return uVar1 | (uVar1 & 0x3f) << 0x15;
}

