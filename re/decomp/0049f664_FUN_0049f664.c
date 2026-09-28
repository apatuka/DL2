// FUN_0049f664 @ 0049f664 size=26 sig=undefined FUN_0049f664() cc=unknown
// callers: FUN_0049e007,FUN_0049e47a
// callees: 

uint FUN_0049f664(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x28) & 0x800000;
  }
  return uVar1;
}

