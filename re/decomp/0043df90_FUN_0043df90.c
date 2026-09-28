// FUN_0043df90 @ 0043df90 size=148 sig=undefined FUN_0043df90() cc=unknown
// callers: FUN_0043e138,FUN_0043e168,FUN_0043e0b8,CombatReport
// callees: FUN_00482b38,FUN_004879f8,FUN_00456e44,FUN_0044a000,FUN_0043d990

void FUN_0043df90(int param_1)

{
  if (param_1 != 0) {
    DAT_00559dd4 = (param_1 + -0x57bd38) / 0x86;
    DAT_00559dc8 = DAT_004c5b50;
    DAT_00559dcc = DAT_004d5acc;
    DAT_00559dd0 = 0;
    DAT_00559dc0 = 0;
    FUN_004879f8();
    DAT_004cf850 = 1;
    FUN_00456e44(param_1);
    DAT_00559dbc = param_1;
    DAT_004d5acc = 2;
    DAT_004c5b50 = (int)*(short *)(*(int *)(param_1 + 4) + 0x1a);
    FUN_0044a000();
    FUN_00482b38(3,0);
    FUN_0043d990(param_1);
  }
  return;
}

