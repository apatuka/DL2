// FUN_0049c0e4 @ 0049c0e4 size=104 sig=undefined FUN_0049c0e4() cc=unknown
// callers: FUN_0049c14c,FUN_004a2a27
// callees: FUN_0049bb73

undefined4 FUN_0049c0e4(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  FUN_0049bb73(param_1,param_2,4,&local_14);
  if ((*(byte *)(param_2 + 0x24) & 0x40) == 0) {
    if ((local_14 + -0x14 <= param_3) && (param_3 <= local_c + 0x14)) {
      return 1;
    }
  }
  else if ((local_10 + -0x14 <= param_4) && (param_4 <= local_8 + 0x14)) {
    return 1;
  }
  return 0;
}

