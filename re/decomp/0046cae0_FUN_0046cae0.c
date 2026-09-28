// FUN_0046cae0 @ 0046cae0 size=105 sig=undefined FUN_0046cae0() cc=unknown
// callers: 
// callees: _lclose,FUN_004a69f0,_lopen

void FUN_0046cae0(LPCSTR param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  HFILE hFile;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  *param_2 = '\0';
  hFile = _lopen(param_1,0);
  if (hFile == -1) {
    if (DAT_004d59ac != 0) {
      uVar2 = 0xffffffff;
      pcVar4 = &DAT_0058f20c;
      do {
        pcVar5 = pcVar4;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        pcVar5 = pcVar4 + 1;
        cVar1 = *pcVar4;
        pcVar4 = pcVar5;
      } while (cVar1 != '\0');
      uVar2 = ~uVar2;
      pcVar4 = pcVar5 + -uVar2;
      pcVar5 = param_2;
      for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar5 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      }
    }
  }
  else {
    _lclose(hFile);
  }
  FUN_004a69f0(param_2,param_1,param_3);
  return;
}

