// FUN_0041860c @ 0041860c size=84 sig=undefined FUN_0041860c() cc=unknown
// callers: FUN_00418704
// callees: 

undefined4 FUN_0041860c(int *param_1,int *param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  *param_2 = param_4 * 0x25 + 0x16f;
  *param_1 = param_3 * 0x24 + 0x6b;
  if ((((*param_1 < 1) || (0x27f < *param_1)) || (*param_2 < 1)) || (0x1df < *param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = CONCAT31((int3)((uint)*param_2 >> 8),1);
  }
  return uVar1;
}

