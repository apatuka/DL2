// FUN_004ae594 @ 004ae594 size=26 sig=undefined FUN_004ae594() cc=unknown
// callers: RaceInit,WinMain,FUN_004634a0,FUN_0047733c,FUN_00468ea4,FUN_00477394,FUN_004618e8
// callees: FUN_004b366c

void FUN_004ae594(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_004b366c();
  *(undefined4 *)(iVar1 + 0x44) = param_1;
  iVar1 = FUN_004b366c();
  *(undefined4 *)(iVar1 + 0x48) = 0;
  return;
}

