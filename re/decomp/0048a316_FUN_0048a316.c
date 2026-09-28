// FUN_0048a316 @ 0048a316 size=29 sig=undefined FUN_0048a316() cc=unknown
// callers: FUN_00495f8f,FUN_0049604c,FUN_00496093
// callees: 

undefined4 FUN_0048a316(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0x44) == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

