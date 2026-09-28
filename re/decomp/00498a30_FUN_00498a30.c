// FUN_00498a30 @ 00498a30 size=44 sig=undefined FUN_00498a30() cc=unknown
// callers: FUN_0048d7b0,FUN_0049b22d,FUN_0049965c
// callees: GlobalLock,GlobalUnlock

undefined2 FUN_00498a30(HGLOBAL param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  
  uVar2 = 0;
  if (param_1 != (HGLOBAL)0x0) {
    puVar1 = GlobalLock(param_1);
    uVar2 = *puVar1;
    *puVar1 = param_2;
    GlobalUnlock(param_1);
  }
  return uVar2;
}

