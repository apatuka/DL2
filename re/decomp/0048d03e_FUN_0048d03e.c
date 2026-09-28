// FUN_0048d03e @ 0048d03e size=61 sig=undefined FUN_0048d03e() cc=unknown
// callers: FUN_0043e694,FUN_00491200,FUN_0048c662,FUN_0049ae0c,FUN_0048d205,FUN_0048cc08,FUN_00493974
// callees: 

undefined8 FUN_0048d03e(int *param_1,int param_2,int param_3)

{
  longlong lVar1;
  int iVar2;
  
  DAT_0065ee28 = param_2;
  DAT_0065ee2c = param_3;
  if (param_1 == (int *)0x0) {
    iVar2 = 0;
  }
  else {
    lVar1 = (longlong)(param_1[3] + 7 >> 3) * (longlong)param_2;
    param_2 = (int)((ulonglong)lVar1 >> 0x20);
    iVar2 = param_1[4] * param_3 + *param_1 + (int)lVar1;
  }
  return CONCAT44(param_2,iVar2);
}

