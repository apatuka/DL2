// FUN_004864c4 @ 004864c4 size=157 sig=undefined FUN_004864c4() cc=unknown
// callers: FUN_0043d184,FUN_0043d630,CreateHit,CreateBldgHit,FUN_004867d8,FUN_0043da5c,FUN_0043d594
// callees: FUN_0047ee04

void FUN_004864c4(int param_1,int param_2,int param_3)

{
  int local_c;
  int local_8;
  
  FUN_0047ee04(param_2 / 3,param_3 / 3,&local_8,&local_c);
  *(int *)(param_1 + 6) = (local_8 + 0x32 + ((param_2 % 3 - param_3 % 3) * 0x32) / 3) * 0x100;
  *(int *)(param_1 + 10) = (local_c + ((param_3 % 3 + param_2 % 3) * 0x19 + 0x32) / 3) * 0x100;
  return;
}

