// FUN_004752fc @ 004752fc size=72 sig=undefined FUN_004752fc() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0049117e,FUN_0042836c

void FUN_004752fc(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar5 = 0;
  uVar4 = 0;
  uVar3 = 4;
  uVar1 = FUN_0049117e(0,0x54415453,5);
  uVar2 = FUN_0049117e(0,0x54415453,4);
  FUN_0042836c(uVar2,uVar1,uVar3,uVar4,uVar5);
  DAT_004d8264 = 1;
  DAT_004d513c = 0;
  DAT_0058ed2e = 0;
  return;
}

