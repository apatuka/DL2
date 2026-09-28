// FUN_004ad86c @ 004ad86c size=85 sig=undefined FUN_004ad86c() cc=unknown
// callers: FUN_004ad768,FUN_004ad840,FUN_004ad794,FUN_004ad7c0,FUN_004ad7ec,FUN_004ad82c,FUN_004ad854,FUN_004ad7d4,FUN_004ad818,FUN_004ad7ac,FUN_004ad800
// callees: GetStringTypeW

uint FUN_004ad86c(int param_1,uint param_2)

{
  uint uVar1;
  ushort local_6;
  
  uVar1 = param_2;
  if (param_1 == 0xffff) {
    param_2 = 0;
  }
  else if ((*(int *)(PTR_DAT_00520d10 + 8) == 0) || (0xff < param_1)) {
    GetStringTypeW(1,(LPCWSTR)&param_1,1,&local_6);
    param_2 = local_6 & uVar1;
  }
  else {
    param_2 = *(ushort *)(&DAT_005209ce + (WCHAR)param_1 * 2) & param_2;
  }
  return param_2;
}

