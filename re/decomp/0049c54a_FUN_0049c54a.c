// FUN_0049c54a @ 0049c54a size=157 sig=undefined FUN_0049c54a() cc=unknown
// callers: FUN_0049c710
// callees: FUN_004935fc

void FUN_0049c54a(int param_1,undefined4 param_2,int param_3,int *param_4)

{
  FUN_004935fc(*param_4 + 1,param_4[1] + 1,param_4[2] + -1,param_4[3] + -1,
               *(undefined4 *)(param_1 + 0x9c + param_3 * 4));
  FUN_004935fc(*param_4,param_4[1],param_4[2],param_4[1] + 1,
               *(undefined4 *)(param_1 + 0xa8 + param_3 * 4));
  FUN_004935fc(*param_4,param_4[1],*param_4 + 1,param_4[3] + -1,
               *(undefined4 *)(param_1 + 0xa8 + param_3 * 4));
  FUN_004935fc(*param_4,param_4[3] + -1,param_4[2],param_4[3],
               *(undefined4 *)(param_1 + 0xb4 + param_3 * 4));
  FUN_004935fc(param_4[2] + -1,param_4[1] + 1,param_4[2],param_4[3],
               *(undefined4 *)(param_1 + 0xb4 + param_3 * 4));
  return;
}

