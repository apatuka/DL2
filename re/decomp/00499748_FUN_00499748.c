// FUN_00499748 @ 00499748 size=87 sig=undefined FUN_00499748() cc=unknown
// callers: 
// callees: GlobalLock,GlobalUnlock

undefined4 FUN_00499748(int param_1,int *param_2)

{
  LPVOID pvVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (param_2 != (int *)0x0) {
    *param_2 = 0;
  }
  if (((param_1 != 0) && ((*(byte *)(param_1 + 0x28) & 1) != 0)) && (*(int *)(param_1 + 0xb0) == 4))
  {
    pvVar1 = GlobalLock(*(HGLOBAL *)(param_1 + 0xb8));
    uVar2 = *(undefined4 *)((int)pvVar1 + 4);
    if (param_2 != (int *)0x0) {
      *param_2 = (int)*(short *)((int)pvVar1 + 0xe);
    }
    GlobalUnlock(*(HGLOBAL *)(param_1 + 0xb8));
  }
  return uVar2;
}

