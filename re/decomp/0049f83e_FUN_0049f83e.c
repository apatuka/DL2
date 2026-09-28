// FUN_0049f83e @ 0049f83e size=99 sig=undefined FUN_0049f83e() cc=unknown
// callers: FUN_004a41d0,FUN_004158fc,FUN_00436070,FUN_00436424,FUN_00423bfc,FUN_00436190,FUN_004a3ffd,FUN_004a3fcd,FUN_00436d90,FUN_0041f360,FUN_004a24f1,FUN_004a4025,FUN_004155bc,FUN_004a2004,FUN_00427fb0,FUN_00415304
// callees: FUN_0049f22b,FUN_0049eb20,FUN_00495bf0,FUN_0049551a

void FUN_0049f83e(int param_1)

{
  int iVar1;
  undefined1 local_24 [16];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1 != 0) {
    iVar1 = FUN_0049551a(DAT_0051e384,param_1);
    if (iVar1 != -1) {
      FUN_0049f22b(param_1,local_24);
      local_10 = *(int *)(param_1 + 0xc);
      local_14 = *(int *)(param_1 + 8);
      local_c = local_14 + *(int *)(param_1 + 0x14);
      local_8 = local_10 + *(int *)(param_1 + 0x10);
      FUN_00495bf0(&local_14,local_24);
      FUN_0049eb20(param_1,local_24);
    }
  }
  return;
}

