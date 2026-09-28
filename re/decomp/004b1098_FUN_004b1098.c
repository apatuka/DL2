// FUN_004b1098 @ 004b1098 size=39 sig=undefined FUN_004b1098() cc=unknown
// callers: 
// callees: FUN_004b0418,FUN_004b0408

uint FUN_004b1098(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  FUN_004b0408();
  uVar1 = *(uint *)(param_1 + -4);
  FUN_004b0418();
  return uVar1 & 0xfffffffc;
}

