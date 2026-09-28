// FUN_0041ba04 @ 0041ba04 size=110 sig=undefined FUN_0041ba04() cc=unknown
// callers: FUN_0041ba74,DrawCAGuyPool
// callees: 

undefined4 FUN_0041ba04(int *param_1,int *param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_2 = param_3 * 0x15 + 0x144;
  if (param_3 == 4) {
    *param_1 = param_4 * 0x17 + 0x7d;
  }
  else {
    *param_1 = param_4 * 0x17 + 0x66;
  }
  if ((((*param_1 < 1) || (0x27f < *param_1)) || (*param_2 < 1)) || (0x1df < *param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = CONCAT31((int3)((uint)*param_2 >> 8),1);
  }
  return uVar1;
}

