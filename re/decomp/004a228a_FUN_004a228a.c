// FUN_004a228a @ 004a228a size=125 sig=undefined FUN_004a228a() cc=unknown
// callers: FUN_004a2cb5,FUN_004a43da
// callees: FUN_0049eb44,FUN_0049eaae

void FUN_004a228a(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  if (((param_2 != 0) && ((*(byte *)(param_2 + 0x28) & 4) == 0)) &&
     (((param_4 != 0 && ((*(byte *)(param_2 + 0x28) & 0x10) == 0)) ||
      ((param_4 == 0 && ((*(byte *)(param_2 + 0x28) & 0x10) != 0)))))) {
    FUN_0049eb44(param_1,param_2,2,8,0,0);
    FUN_0049eaae(param_2,param_4 != 0);
    *(undefined4 *)(param_2 + 0xf0) = param_3;
    FUN_0049eb44(param_1,param_2,2,8,0,0);
    FUN_0049eb44(param_1,param_2,2,0x32,0,0);
  }
  return;
}

