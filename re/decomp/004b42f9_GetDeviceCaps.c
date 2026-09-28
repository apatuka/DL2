// GetDeviceCaps @ 004b42f9 size=6 sig=int GetDeviceCaps(HDC hdc, int index) cc=__stdcall
// callers: FUN_00458a5c,CreateMainWindow,WinMain
// callees: 

int GetDeviceCaps(HDC hdc,int index)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42f9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetDeviceCaps(hdc,index);
  return iVar1;
}

