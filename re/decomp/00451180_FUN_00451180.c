// FUN_00451180 @ 00451180 size=35 sig=undefined FUN_00451180() cc=unknown
// callers: FUN_004556b0,FUN_00453a38,FUN_00451410,FUN_00453ec8,FUN_00454928,FUN_00453c30,FUN_00453954,FUN_00453d9c,FUN_00454690,FUN_00454160,FUN_004543f8
// callees: 

undefined8 FUN_00451180(int param_1,int param_2,int param_3)

{
  longlong lVar1;
  
  param_2 = *(int *)(param_1 + 0x20) - param_2;
  param_3 = *(int *)(param_1 + 0x24) - param_3;
  lVar1 = (longlong)param_3 * (longlong)param_3;
  return CONCAT44((int)((ulonglong)lVar1 >> 0x20),param_2 * param_2 + (int)lVar1);
}

