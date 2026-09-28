// FUN_004878a8 @ 004878a8 size=195 sig=undefined FUN_004878a8() cc=unknown
// callers: FUN_004590f0,FUN_0045e4f4,WinMain,MessagePump,FUN_00472e84,FUN_0046ce10,FUN_0045e6d0,FUN_00459230,FUN_004879b0,FUN_00487e34
// callees: FUN_0048d2e7,FUN_0048c85e,FUN_0048d32c,FUN_00490796

void FUN_004878a8(void)

{
  int iVar1;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_005126dc != 0) {
    if (((DAT_005126dc != 0) && ((*(byte *)(DAT_005126dc + 0x28) & 1) != 0)) &&
       ((*(byte *)(DAT_005126dc + 0xb4) & 1) != 0)) {
      FUN_0048d2e7(DAT_004d5c28);
      local_24 = 0;
      local_20 = 0;
      local_1c = *(int *)(DAT_005126dc + 4);
      local_18 = *(int *)(DAT_005126dc + 8);
      iVar1 = *(int *)(*(int *)(DAT_005126dc + 0xb8) + 0x1c);
      if (iVar1 != 0) {
        local_14 = *(int *)(iVar1 + 4);
        local_10 = *(int *)(iVar1 + 8);
        local_8 = local_10 + local_18;
        local_c = local_14 + local_1c;
        FUN_0048c85e(DAT_005126dc,DAT_004d5c28,&local_24,&local_14,0,0,0);
      }
      FUN_0048d32c();
    }
    FUN_00490796(DAT_005126dc,1);
    DAT_005126dc = 0;
  }
  return;
}

