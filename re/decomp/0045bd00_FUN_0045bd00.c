// FUN_0045bd00 @ 0045bd00 size=68 sig=undefined FUN_0045bd00() cc=unknown
// callers: 
// callees: FUN_00459068,FUN_0045bc10,FUN_0047ee9c

void FUN_0045bd00(undefined4 param_1,undefined4 param_2)

{
  int local_c;
  int local_8;
  
  FUN_00459068();
  FUN_0047ee9c(param_1,param_2,&local_8,&local_c);
  DAT_00583d9c = local_c * 6 + local_8;
  FUN_0045bc10(param_1,param_2);
  return;
}

