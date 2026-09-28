// FUN_004916c2 @ 004916c2 size=39 sig=undefined FUN_004916c2() cc=unknown
// callers: FUN_0048d07b
// callees: GlobalUnlock,FUN_004989de,FUN_0048fbbf,GlobalLock

void FUN_004916c2(HGLOBAL param_1)

{
  undefined4 *puVar1;
  
  puVar1 = GlobalLock(param_1);
  FUN_0048fbbf(*puVar1,0);
  GlobalUnlock(param_1);
  FUN_004989de(param_1);
  return;
}

