// FUN_0042e584 @ 0042e584 size=230 sig=undefined FUN_0042e584() cc=unknown
// callers: FUN_0041e6d4,FUN_0042df28,FUN_004272b4,FUN_0042e66c
// callees: FUN_004a19b4,FUN_0049eb44

undefined4 FUN_0042e584(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  int local_8;
  
  uVar2 = 1;
  FUN_0049eb44(DAT_004c36ac,2,1,0x3f,0,&local_8);
  FUN_0049eb44(DAT_004c36ac,2,1,0x41,0,&local_c);
  FUN_0049eb44(DAT_004c36ac,2,1,0x44,2,0);
  if (*(int *)(&DAT_004c36f8 + param_1 * 8) == local_8) {
    if (*(int *)(&DAT_004c36fc + param_1 * 8) != local_c) {
      uVar2 = FUN_0049eb44(DAT_004c36ac,2,1,0x42,0,*(int *)(&DAT_004c36fc + param_1 * 8));
    }
  }
  else {
    iVar1 = FUN_0049eb44(DAT_004c36ac,2,1,0x40,0,*(undefined4 *)(&DAT_004c36f8 + param_1 * 8));
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = FUN_0049eb44(DAT_004c36ac,2,1,0x42,0,*(undefined4 *)(&DAT_004c36fc + param_1 * 8));
    }
  }
  FUN_004a19b4(DAT_004c36ac,2,1,0x11,param_1);
  return uVar2;
}

