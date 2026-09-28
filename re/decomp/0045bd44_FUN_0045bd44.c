// FUN_0045bd44 @ 0045bd44 size=159 sig=undefined FUN_0045bd44() cc=unknown
// callers: FUN_0044a750
// callees: FUN_0045b970,FUN_0047ee9c

undefined4 FUN_0045bd44(undefined4 param_1,undefined4 param_2)

{
  int local_c;
  int local_8;
  
  if ('\x02' < *(char *)(DAT_00657de0 + 0x66 + DAT_0058f1f4)) {
    FUN_0047ee9c(param_1,param_2,&local_8,&local_c);
    if ((((-1 < local_8) && (local_8 < 6)) && (-1 < local_c)) && (local_c < 6)) {
      DAT_00583d90 = 0xffffffff;
      DAT_00583d98 = local_c * 6 + local_8;
      return 1;
    }
    DAT_00583d90 = FUN_0045b970(param_1,param_2,0);
    DAT_00583d98 = 0xffffffff;
    if (DAT_00583d90 != -1) {
      DAT_00583d98 = 0xffffffff;
      return 1;
    }
  }
  return 0;
}

