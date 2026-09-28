// SetWindowTextA @ 004b40e3 size=6 sig=BOOL SetWindowTextA(HWND hWnd, LPCSTR lpString) cc=__stdcall
// callers: FUN_0040c8c8,FUN_00484980,@DebugMinisterDialog$qqspvuiuil,FUN_00405d54,FUN_004770fc,FUN_0047425c,FUN_00473d0c
// callees: 

BOOL SetWindowTextA(HWND hWnd,LPCSTR lpString)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b40e3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetWindowTextA(hWnd,lpString);
  return BVar1;
}

