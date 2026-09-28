// FUN_004b1528 @ 004b1528 size=70 sig=undefined FUN_004b1528() cc=unknown
// callers: FUN_004b1570
// callees: EnumThreadWindows,GetVersion,GetCurrentThreadId

undefined8 FUN_004b1528(void)

{
  DWORD DVar1;
  undefined4 uVar2;
  WNDENUMPROC lpfn;
  int *lParam;
  int local_4;
  
  lParam = &local_4;
  local_4 = 0;
  DVar1 = GetVersion();
  if ((DVar1 & 0x80000000) == 0) {
    return CONCAT44(local_4,0x2000);
  }
  lpfn = (WNDENUMPROC)&LAB_004b1514;
  DVar1 = GetCurrentThreadId();
  EnumThreadWindows(DVar1,lpfn,(LPARAM)lParam);
  uVar2 = 0x2000;
  if (local_4 == 0) {
    uVar2 = 0x1000;
  }
  return CONCAT44(local_4,uVar2);
}

