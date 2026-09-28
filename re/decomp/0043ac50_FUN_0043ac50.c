// FUN_0043ac50 @ 0043ac50 size=132 sig=undefined FUN_0043ac50() cc=unknown
// callers: FUN_00449760
// callees: FUN_0049eb44

void FUN_0043ac50(char param_1,int param_2)

{
  if (DAT_004d5aa0 == '\0') {
    if (param_1 == '\0') {
      FUN_0049eb44(DAT_004c48a0,param_2 + 0x26,1,0xb,0,0);
    }
    else {
      FUN_0049eb44(DAT_004c48a0,param_2 + 0x26,1,0xb,1,0);
    }
  }
  else if (param_1 == '\0') {
    FUN_0049eb44(DAT_004c48a0,param_2 + 0x27,1,0xb,0,0);
  }
  else {
    FUN_0049eb44(DAT_004c48a0,param_2 + 0x27,1,0xb,1,0);
  }
  return;
}

