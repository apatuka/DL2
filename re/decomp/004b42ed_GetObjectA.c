// GetObjectA @ 004b42ed size=6 sig=int GetObjectA(HANDLE h, int c, LPVOID pv) cc=__stdcall
// callers: FUN_0048bdb0
// callees: 

int GetObjectA(HANDLE h,int c,LPVOID pv)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b42ed. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetObjectA(h,c,pv);
  return iVar1;
}

