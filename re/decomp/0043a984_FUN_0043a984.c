// FUN_0043a984 @ 0043a984 size=125 sig=undefined FUN_0043a984() cc=unknown
// callers: FUN_0043be98,FUN_0043baf4
// callees: FUN_0049eb44,FUN_00481098,FUN_0044a000

void FUN_0043a984(void)

{
  DAT_00559da0 = DAT_00559da0 + 1;
  if (DAT_00559da0 == 6) {
    DAT_00559da0 = 0;
  }
  if (DAT_004d5aa0 == '\0') {
    FUN_0049eb44(DAT_004c48a0,0x11,1,0x42,0,(&DAT_004c48a8)[DAT_00559da0]);
  }
  else {
    FUN_0049eb44(DAT_004c48a0,0x11,1,0x42,0,(&DAT_004c48a8)[DAT_00559da0]);
  }
  if ((DAT_00559da0 == 0) || (DAT_00559da0 == 1)) {
    FUN_00481098();
  }
  FUN_0044a000();
  return;
}

