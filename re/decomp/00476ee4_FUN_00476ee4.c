// FUN_00476ee4 @ 00476ee4 size=61 sig=undefined FUN_00476ee4() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0047510c,FUN_00475040,FUN_004a6b48

void FUN_00476ee4(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0047510c(*(undefined2 *)(param_1 + 0x18));
  if ((iVar1 == 0) || (param_1 + 0x1a == 0)) {
    FUN_00475040(*(undefined4 *)(param_1 + 4));
  }
  else {
    FUN_004a6b48(iVar1 + 0xb,param_1 + 0x1a,0x18);
  }
  return;
}

