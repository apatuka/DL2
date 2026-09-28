// FUN_004aa994 @ 004aa994 size=47 sig=undefined FUN_004aa994() cc=unknown
// callers: FUN_00479700,FUN_00479b6c
// callees: FUN_004aa418,FUN_004ab648,FUN_004ab710

void FUN_004aa994(int param_1)

{
  int iVar1;
  
  FUN_004ab648(param_1);
  iVar1 = FUN_004aa418(param_1,0,0);
  if (iVar1 == 0) {
    *(ushort *)(param_1 + 0x12) = *(ushort *)(param_1 + 0x12) & 0xffef;
  }
  FUN_004ab710(param_1);
  return;
}

