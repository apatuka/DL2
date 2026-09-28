// FUN_004371e4 @ 004371e4 size=298 sig=undefined FUN_004371e4() cc=unknown
// callers: FUN_00437718,FUN_00437668
// callees: FUN_0049eb44,FUN_004727dc,sprintf,FUN_00414f38,FUN_004ae26c

void FUN_004371e4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_808 [1024];
  undefined1 local_408 [1024];
  
  FUN_0049eb44(DAT_004c4670,9,1,0xe,0x80,auStack_808);
  iVar1 = FUN_004ae26c(auStack_808);
  FUN_0049eb44(DAT_004c4670,8,1,0xe,0x80,auStack_808);
  iVar2 = FUN_004ae26c(auStack_808);
  sprintf(local_408,&DAT_004c46a9,iVar1 * iVar2);
  FUN_0049eb44(DAT_004c4670,0x10,1,0xf,0,local_408);
  iVar3 = FUN_004727dc(DAT_00558f30,DAT_00558f34);
  sprintf(local_408,&DAT_004c46a9,iVar3 * iVar1);
  FUN_0049eb44(DAT_004c4670,0x12,1,0xf,0,local_408);
  iVar3 = FUN_004727dc(DAT_00558f30,DAT_00558f34);
  sprintf(local_408,&DAT_004c46a9,iVar3 * iVar1 + iVar1 * iVar2);
  FUN_0049eb44(DAT_004c4670,0x14,1,0xf,0,local_408);
  FUN_00414f38(DAT_004c4670);
  return;
}

