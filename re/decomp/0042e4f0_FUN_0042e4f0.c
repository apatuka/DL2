// FUN_0042e4f0 @ 0042e4f0 size=146 sig=undefined FUN_0042e4f0() cc=unknown
// callers: FUN_0042e66c
// callees: FUN_004a19b4,FUN_0049eb44

undefined4 FUN_0042e4f0(int param_1)

{
  undefined4 uVar1;
  int local_8;
  
  uVar1 = 1;
  FUN_0049eb44(DAT_004c36ac,2,1,0x3f,0,&local_8);
  FUN_0049eb44(DAT_004c36ac,2,1,0x44,4,0);
  if (*(int *)(&DAT_004c36c0 + param_1 * 8) != local_8) {
    uVar1 = FUN_0049eb44(DAT_004c36ac,2,1,0x40,0,*(int *)(&DAT_004c36c0 + param_1 * 8));
    FUN_0049eb44(DAT_004c36ac,2,1,0x42,0,0);
  }
  FUN_004a19b4(DAT_004c36ac,2,1,0x11,param_1);
  return uVar1;
}

