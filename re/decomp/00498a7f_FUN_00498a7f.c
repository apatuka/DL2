// FUN_00498a7f @ 00498a7f size=37 sig=undefined FUN_00498a7f() cc=unknown
// callers: 
// callees: GlobalLock,GlobalUnlock

undefined2 FUN_00498a7f(HGLOBAL param_1)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  
  uVar2 = 0;
  if (param_1 != (HGLOBAL)0x0) {
    puVar1 = GlobalLock(param_1);
    uVar2 = *puVar1;
    GlobalUnlock(param_1);
  }
  return uVar2;
}

