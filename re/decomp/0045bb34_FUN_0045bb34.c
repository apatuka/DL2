// FUN_0045bb34 @ 0045bb34 size=84 sig=undefined FUN_0045bb34() cc=unknown
// callers: FUN_0044a838,FUN_0044a92c
// callees: FUN_0045b970,FUN_0047ee9c

undefined4 FUN_0045bb34(undefined4 param_1,undefined4 param_2)

{
  int local_c;
  int local_8;
  
  FUN_0047ee9c(param_1,param_2,&local_8,&local_c);
  if ((local_8 != -1) && (local_c != -1)) {
    DAT_00583d9c = local_c * 6 + local_8;
  }
  DAT_00583d94 = FUN_0045b970(param_1,param_2,0);
  return 1;
}

