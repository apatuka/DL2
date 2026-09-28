// FUN_004375f4 @ 004375f4 size=116 sig=undefined FUN_004375f4() cc=unknown
// callers: FUN_00437668
// callees: FUN_0049eb44,FUN_004375c0,FUN_004ae26c

void FUN_004375f4(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined1 local_404 [1024];
  
  FUN_0049eb44(DAT_004c4670,9,1,0xe,0x80,local_404);
  uVar1 = FUN_004ae26c(local_404);
  *param_1 = uVar1;
  FUN_0049eb44(DAT_004c4670,8,1,0xe,0x80,local_404);
  uVar1 = FUN_004ae26c(local_404);
  *param_2 = uVar1;
  FUN_004375c0();
  return;
}

