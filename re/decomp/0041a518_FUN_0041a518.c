// FUN_0041a518 @ 0041a518 size=195 sig=undefined FUN_0041a518() cc=unknown
// callers: FUN_0044b0a4
// callees: FUN_00418cf4,FUN_00419c88,FUN_00419c58,FUN_00418d18,FUN_00419d94,FUN_00419fe0,FUN_004197a8,FUN_00419710

void FUN_0041a518(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int local_c;
  int local_8;
  
  cVar1 = FUN_00419c88(param_1,param_2,&local_8,&local_c);
  if ((((cVar1 == '\0') || (local_8 != DAT_0053b260)) || (local_c != DAT_0053b264)) ||
     ((DAT_004d5aa0 == '\0' &&
      (*(char *)(*(int *)((int)&DAT_005332dc + local_c * 0x20 + local_8 * 0x146) + 8) !=
       DAT_0058f1f4)))) {
    FUN_00419d94();
  }
  else {
    cVar1 = FUN_00419c58(local_8,local_c);
    if (cVar1 == '\0') {
      FUN_00419d94();
      FUN_00419fe0(param_1,param_2,1);
    }
    if (DAT_005332b0 == '\0') {
      FUN_004197a8();
    }
    else {
      FUN_00419710();
    }
  }
  FUN_00418d18();
  FUN_00418cf4();
  return;
}

