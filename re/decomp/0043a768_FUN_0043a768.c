// FUN_0043a768 @ 0043a768 size=235 sig=undefined FUN_0043a768() cc=unknown
// callers: FUN_0045ac80
// callees: FUN_0049eb44

void FUN_0043a768(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = 10000;
  local_c = 10000;
  local_8 = 10000;
  local_4 = 10000;
  if (DAT_004d5aa0 == '\0') {
    FUN_0049eb44(DAT_004c48a0,0xe,1,0xd,0,&local_10);
  }
  else {
    FUN_0049eb44(DAT_004c48a0,0xe,1,0xd,0,&local_10);
  }
  local_c = 0x28;
  local_10 = 0x1b3;
  local_8 = 0x1d8;
  local_4 = 0x45;
  if (DAT_004d5aa0 == '\0') {
    FUN_0049eb44(DAT_004c48a0,0x11,1,0xd,0,&local_10);
    FUN_0049eb44(DAT_004c48a0,0x11,1,0x42,0,DAT_004c48a8);
  }
  else {
    FUN_0049eb44(DAT_004c48a0,0x11,1,0xd,0,&local_10);
    FUN_0049eb44(DAT_004c48a0,0x11,1,0x42,0,DAT_004c48a8);
  }
  DAT_00559da0 = 0;
  return;
}

