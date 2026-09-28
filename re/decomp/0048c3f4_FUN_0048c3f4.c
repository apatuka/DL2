// FUN_0048c3f4 @ 0048c3f4 size=64 sig=undefined FUN_0048c3f4() cc=unknown
// callers: FUN_00463aec,FUN_0048c4eb,FUN_0048cf7f,FUN_0048c4ad,FUN_0048c662,FUN_0048c55b,FUN_0048c5c5,FUN_00411808,FUN_0048d205,FUN_0048c85e,FUN_0048cc08,FUN_004a52db
// callees: 

undefined4 FUN_0048c3f4(int param_1)

{
  undefined4 uVar1;
  
  if ((param_1 == 0) || (*(short *)(param_1 + 0x24) < 1)) {
    uVar1 = 0;
  }
  else {
    *(short *)(param_1 + 0x24) = *(short *)(param_1 + 0x24) + -1;
    if ((*(short *)(param_1 + 0x24) == 0) && (*(short *)(param_1 + 0x2a) == 0)) {
      (**(code **)(**(int **)(param_1 + 0x40) + 0x80))(*(int **)(param_1 + 0x40),0);
    }
    uVar1 = 1;
  }
  return uVar1;
}

