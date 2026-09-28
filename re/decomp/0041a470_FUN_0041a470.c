// FUN_0041a470 @ 0041a470 size=167 sig=undefined FUN_0041a470() cc=unknown
// callers: FUN_0044abe8
// callees: GetKeyState,FUN_00418cf4,FUN_00419c88,FUN_00418d18,FUN_00419d94,FUN_00419fe0,FUN_00419710

void FUN_0041a470(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  int local_10;
  int local_c;
  uint local_8;
  
  uVar2 = GetKeyState(0x10);
  uVar3 = GetKeyState(0x11);
  local_8 = (uint)((uVar3 & 0x8000) != 0);
  cVar1 = FUN_00419c88(param_1,param_2,&local_c,&local_10);
  if (((cVar1 == '\0') || (local_c != DAT_0053b260)) || (local_10 != DAT_0053b264)) {
    FUN_00419d94();
  }
  else if (((uVar2 & 0x8000) == 0) && (local_8 == 0)) {
    FUN_00419d94();
    FUN_00419fe0(param_1,param_2,1);
    if (DAT_005332b0 != '\0') {
      FUN_00419710();
    }
  }
  FUN_00418d18();
  FUN_00418cf4();
  return;
}

