// DebugLog @ 004587f0 size=79 sig=undefined DebugLog() cc=unknown
// callers: InitCYGame,DebugMessage,FUN_00458a5c,WinMain
// callees: fopen,fclose,FUN_004aa0a8
// strings: \"DEBUG.TXT\"|\"Turn %3d: \"

/* Appends "Turn %3d: <tag>" to DEBUG.TXT */

void DebugLog(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = fopen(s_DEBUG_TXT_004d179c,&DAT_004d1821);
  if (iVar1 != 0) {
    FUN_004aa0a8(iVar1,s_Turn__3d__004d1823,DAT_0059f154);
    FUN_004aa0a8(iVar1,&DAT_004d182e,param_1);
    fclose(iVar1);
  }
  return;
}

