// FUN_004a5a0b @ 004a5a0b size=87 sig=undefined FUN_004a5a0b() cc=unknown
// callers: 
// callees: FUN_004935fc,FUN_0049372b

bool FUN_004a5a0b(int param_1,undefined4 param_2,int param_3)

{
  if (param_3 == 3) {
    FUN_004935fc(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),
                 *(int *)(param_1 + 8) + *(int *)(param_1 + 0x14),
                 *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10),0);
    FUN_0049372b(*(int *)(param_1 + 8) + 1,*(int *)(param_1 + 0xc) + 1,
                 *(int *)(param_1 + 0x14) + *(int *)(param_1 + 8) + -1,
                 *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0xc) + -1,0xffffffff);
  }
  return param_3 == 3;
}

