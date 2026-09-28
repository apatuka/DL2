// FUN_004272b4 @ 004272b4 size=68 sig=undefined FUN_004272b4() cc=unknown
// callers: FUN_004493dc
// callees: FUN_0042e584,FUN_004a3fa6,FUN_004a1c75

void FUN_004272b4(char param_1)

{
  int iVar1;
  undefined4 local_8;
  
  iVar1 = FUN_004a1c75(DAT_004c36ac,2,1,0x11,&local_8);
  if (iVar1 == 0) {
    local_8 = 0xffffffff;
  }
  FUN_0042e584(local_8);
  FUN_004a3fa6(DAT_004b7d34,(int)param_1);
  return;
}

