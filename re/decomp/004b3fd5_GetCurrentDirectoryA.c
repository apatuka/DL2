// GetCurrentDirectoryA @ 004b3fd5 size=6 sig=DWORD GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer) cc=__stdcall
// callers: FUN_004ac7ec,FUN_004ac688,FUN_00488dd3
// callees: 

DWORD GetCurrentDirectoryA(DWORD nBufferLength,LPSTR lpBuffer)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3fd5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetCurrentDirectoryA(nBufferLength,lpBuffer);
  return DVar1;
}

