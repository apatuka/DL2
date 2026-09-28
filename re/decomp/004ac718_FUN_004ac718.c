// FUN_004ac718 @ 004ac718 size=212 sig=undefined FUN_004ac718() cc=unknown
// callers: FUN_004b1c4c
// callees: GetDriveTypeA,FUN_004b0a30,FUN_004b0b44,GetFullPathNameA,FUN_004b1010

char * FUN_004ac718(char *param_1,LPCSTR param_2,uint param_3)

{
  char cVar1;
  LPSTR lpBuffer;
  DWORD DVar2;
  UINT UVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  LPSTR pCVar7;
  char *pcVar8;
  CHAR local_c [4];
  LPSTR local_8;
  
  lpBuffer = (LPSTR)FUN_004b0b44(0x104);
  if (lpBuffer == (LPSTR)0x0) {
    param_1 = (char *)0x0;
  }
  else {
    DVar2 = GetFullPathNameA(param_2,0x104,lpBuffer,&local_8);
    if ((DVar2 == 0) || (0x103 < DVar2)) {
      FUN_004b0a30(lpBuffer);
      param_1 = (char *)0x0;
    }
    else {
      if (lpBuffer[1] == ':') {
        local_c[0] = *lpBuffer;
        local_c[1] = 0x3a;
        local_c[2] = 0x5c;
        local_c[3] = 0;
        UVar3 = GetDriveTypeA(local_c);
        if (UVar3 < 2) {
          FUN_004b0a30(lpBuffer);
          return (char *)0x0;
        }
      }
      if (param_1 == (char *)0x0) {
        param_1 = (char *)FUN_004b1010(lpBuffer,DVar2 + 1);
      }
      else if (param_3 < DVar2 + 1) {
        FUN_004b0a30(lpBuffer);
        param_1 = (char *)0x0;
      }
      else {
        uVar4 = 0xffffffff;
        pCVar7 = lpBuffer;
        do {
          pcVar6 = pCVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar6 = pCVar7 + 1;
          cVar1 = *pCVar7;
          pCVar7 = pcVar6;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar6 = pcVar6 + -uVar4;
        pcVar8 = param_1;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar8 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          pcVar8 = pcVar8 + 1;
        }
        FUN_004b0a30(lpBuffer);
      }
    }
  }
  return param_1;
}

