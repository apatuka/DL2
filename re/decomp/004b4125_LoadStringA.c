// LoadStringA @ 004b4125 size=6 sig=int LoadStringA(HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int cchBufferMax) cc=__stdcall
// callers: FUN_004257f0,FUN_00425ac4,FUN_004953e8,FUN_004258f8,FUN_0043cd98,FUN_00450670
// callees: 

int LoadStringA(HINSTANCE hInstance,UINT uID,LPSTR lpBuffer,int cchBufferMax)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b4125. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = LoadStringA(hInstance,uID,lpBuffer,cchBufferMax);
  return iVar1;
}

