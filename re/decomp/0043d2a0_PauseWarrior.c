// PauseWarrior @ 0043d2a0 size=53 sig=undefined PauseWarrior() cc=unknown
// callers: 
// callees: DebugMessage
// strings: \"NULL anim in PauseWarrior\"

/* auto-named from string evidence: PauseWarrior */

void PauseWarrior(short param_1,int param_2)

{
  if (param_2 == 0) {
    DebugMessage(s_NULL_anim_in_PauseWarrior_004c499e);
  }
  else {
    *(short *)(param_2 + 0x1e) = param_1 * (short)DAT_004c4954;
    *(short *)(param_2 + 0x2a) = param_1 * (short)DAT_004c4954;
  }
  return;
}

