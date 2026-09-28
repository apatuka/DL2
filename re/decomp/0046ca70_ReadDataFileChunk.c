// ReadDataFileChunk @ 0046ca70 size=112 sig=undefined ReadDataFileChunk() cc=unknown
// callers: DrawSpriteCentered,FUN_00465070,FUN_00464cbc,CreateWinGWindow,FUN_004818ac,StillPic
// callees: _lclose,_lread,_llseek,_lopen

/* Reads size bytes at offset from a data file (SPRITENW.DAT) */

undefined4 ReadDataFileChunk(LPCSTR param_1,LPVOID param_2,int param_3,UINT param_4)

{
  HFILE hFile;
  LONG LVar1;
  UINT UVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if (((param_4 != 0) && (param_2 != (LPVOID)0x0)) && (param_1 != (LPCSTR)0x0)) {
    hFile = _lopen(param_1,0);
    if (hFile != -1) {
      LVar1 = _llseek(hFile,param_3,0);
      if (LVar1 == param_3) {
        UVar2 = _lread(hFile,param_2,param_4);
        if ((param_4 == UVar2) || (param_4 == 0xffffffff)) {
          uVar3 = 1;
        }
      }
      _lclose(hFile);
    }
  }
  return uVar3;
}

