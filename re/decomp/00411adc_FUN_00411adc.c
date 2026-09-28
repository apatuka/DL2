// FUN_00411adc @ 00411adc size=88 sig=undefined FUN_00411adc() cc=unknown
// callers: FUN_00411b54,FUN_00411ab0
// callees: FUN_00411990,FUN_0041244c,FUN_00411a68

int FUN_00411adc(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = FUN_00411a68(param_1,param_2,param_3);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x14) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_0041244c(*(int *)(param_1 + 0x14),param_2,param_3);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        FUN_00411990(param_1,param_2,iVar1,*param_3);
      }
    }
  }
  return iVar1;
}

