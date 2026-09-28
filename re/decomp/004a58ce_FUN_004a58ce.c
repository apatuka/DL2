// FUN_004a58ce @ 004a58ce size=317 sig=undefined FUN_004a58ce() cc=unknown
// callers: FUN_004a5c60
// callees: FUN_00493149,FUN_00491bf7,FUN_004a6964

void FUN_004a58ce(undefined4 param_1)

{
  int iVar1;
  int local_8;
  
  FUN_00491bf7(DAT_0051e524);
  FUN_004a6964(&DAT_0069eeb4,param_1);
  iVar1 = FUN_00493149(&DAT_0069eeb4,0x100,&local_8,0);
  DAT_0069efc4 = local_8 + 8;
  DAT_0069efc8 = ((int)DAT_0069f044 + (int)DAT_0069f046) * iVar1 + 8;
  DAT_0069efb4 = 1000;
  DAT_0069efb8 = 2;
  DAT_0069efbc = 0;
  DAT_0069efc0 = 0;
  DAT_0069efcc = 0x12;
  DAT_0069efd0 = DAT_0051e520;
  DAT_0069efd4 = 0xb;
  DAT_0069efd8 = 0x50495454;
  DAT_0069efdc = 0xffffffff;
  DAT_0069efe0 = 5;
  DAT_0069efe4 = 10;
  DAT_0069efe8 = 0x10;
  DAT_0069efec = 3;
  DAT_0069eff0 = 0x80;
  DAT_0069eff4 = 1;
  DAT_0069eff8 = &DAT_0069eeb4;
  DAT_0069effc = 2;
  DAT_0069f000 = 4;
  DAT_0069f004 = 4;
  DAT_0069f008 = local_8;
  DAT_0069f00c = ((int)DAT_0069f044 + (int)DAT_0069f046) * iVar1;
  DAT_0069f010 = 0xffffffff;
  DAT_0069f014 = 0xffffffff;
  FUN_00491bf7(0);
  return;
}

