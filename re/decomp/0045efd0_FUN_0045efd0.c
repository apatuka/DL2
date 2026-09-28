// FUN_0045efd0 @ 0045efd0 size=45 sig=undefined FUN_0045efd0() cc=unknown
// callers: FUN_0045f148,FUN_004618e8,RunAITurns
// callees: timeGetTime,FUN_00482f80

void FUN_0045efd0(undefined4 param_1)

{
  if (DAT_004d5aa0 == '\0') {
    DAT_00583da0 = timeGetTime();
    DAT_004d1c84 = 1;
    FUN_00482f80(param_1);
  }
  return;
}

