// FUN_0049979f @ 0049979f size=64 sig=undefined FUN_0049979f() cc=unknown
// callers: 
// callees: GlobalLock,GlobalUnlock

undefined4 FUN_0049979f(int param_1)

{
  LPVOID pvVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (((param_1 != 0) && ((*(byte *)(param_1 + 0x28) & 1) != 0)) && (*(int *)(param_1 + 0xb0) == 4))
  {
    pvVar1 = GlobalLock(*(HGLOBAL *)(param_1 + 0xb8));
    uVar2 = *(undefined4 *)((int)pvVar1 + 0x18);
    GlobalUnlock(*(HGLOBAL *)(param_1 + 0xb8));
  }
  return uVar2;
}

