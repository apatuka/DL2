// FUN_0049f64c @ 0049f64c size=24 sig=undefined FUN_0049f64c() cc=unknown
// callers: FUN_004a03cf,FUN_0049fc69,FUN_004a060f,FUN_0049fe03,FUN_0049f8dd
// callees: 

uint FUN_0049f64c(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(uint *)(param_1 + 0x28) & 1;
  }
  return uVar1;
}

