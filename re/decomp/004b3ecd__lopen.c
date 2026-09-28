// _lopen @ 004b3ecd size=6 sig=HFILE _lopen(LPCSTR lpPathName, int iReadWrite) cc=__stdcall
// callers: FUN_0046cae0,ReadDataFileChunk
// callees: 

HFILE _lopen(LPCSTR lpPathName,int iReadWrite)

{
  HFILE HVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3ecd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  HVar1 = _lopen(lpPathName,iReadWrite);
  return HVar1;
}

