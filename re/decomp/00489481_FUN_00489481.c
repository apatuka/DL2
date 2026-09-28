// FUN_00489481 @ 00489481 size=83 sig=undefined FUN_00489481() cc=unknown
// callers: FUN_0049512a
// callees: FUN_004894d4,FUN_004a6964,FUN_00489356

void FUN_00489481(undefined4 param_1,undefined4 param_2,char param_3)

{
  char cVar1;
  undefined1 local_108 [260];
  
  if ((param_3 == '\0') && (cVar1 = FUN_00489356(param_1), cVar1 != '\0')) {
    return;
  }
  FUN_004a6964(local_108,param_2);
  FUN_004894d4(local_108,param_1);
  FUN_004a6964(param_1,local_108);
  return;
}

