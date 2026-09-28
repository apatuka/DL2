// _lread @ 004b3f69 size=6 sig=UINT _lread(HFILE hFile, LPVOID lpBuffer, UINT uBytes) cc=__stdcall
// callers: ReadDataFileChunk
// callees: 

UINT _lread(HFILE hFile,LPVOID lpBuffer,UINT uBytes)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x004b3f69. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = _lread(hFile,lpBuffer,uBytes);
  return UVar1;
}

