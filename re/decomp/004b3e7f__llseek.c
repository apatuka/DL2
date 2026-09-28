// _llseek @ 004b3e7f size=6 sig=LONG _llseek(HFILE hFile, LONG lOffset, int iOrigin) cc=__stdcall
// callers: ReadDataFileChunk
// callees: 

LONG _llseek(HFILE hFile,LONG lOffset,int iOrigin)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3e7f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = _llseek(hFile,lOffset,iOrigin);
  return LVar1;
}

