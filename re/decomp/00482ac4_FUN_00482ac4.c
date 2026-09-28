// FUN_00482ac4 @ 00482ac4 size=63 sig=undefined FUN_00482ac4() cc=unknown
// callers: FUN_0043d990,DestroyAnim,FUN_0043d860,FUN_0043d594,CreateBldgHit,FUN_0043d2d8,FUN_0043da5c,FUN_0043d8dc,FUN_0043d630,CreateHit,FUN_0042ee18
// callees: FUN_00482ba0

undefined4
FUN_00482ac4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_00657e20 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = FUN_00482ba0(param_1,param_2,param_3,param_4,param_5,param_6,0);
    if (iVar2 == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

