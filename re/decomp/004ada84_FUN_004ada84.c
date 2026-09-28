// FUN_004ada84 @ 004ada84 size=295 sig=undefined FUN_004ada84() cc=unknown
// callers: 
// callees: MultiByteToWideChar,strlen,GetLastError

uint FUN_004ada84(LPWSTR param_1,byte *param_2,uint param_3)

{
  int iVar1;
  DWORD DVar2;
  byte *pbVar3;
  uint uVar4;
  
  uVar4 = 0;
  if ((param_1 == (LPWSTR)0x0) || (param_3 != 0)) {
    if (param_1 == (LPWSTR)0x0) {
      if (*(int *)(PTR_DAT_00520d10 + 8) == 0) {
        iVar1 = MultiByteToWideChar(*(UINT *)PTR_DAT_00520d10,9,(LPCSTR)param_2,-1,(LPWSTR)0x0,0);
        if (iVar1 == 0) {
          uVar4 = 0xffffffff;
        }
        else {
          uVar4 = iVar1 - 1;
        }
      }
      else {
        uVar4 = strlen(param_2);
      }
    }
    else if (*(int *)(PTR_DAT_00520d10 + 8) == 0) {
      iVar1 = MultiByteToWideChar(*(UINT *)PTR_DAT_00520d10,9,(LPCSTR)param_2,-1,param_1,param_3);
      if (iVar1 == 0) {
        DVar2 = GetLastError();
        pbVar3 = param_2;
        uVar4 = param_3;
        if (DVar2 == 0x7a) {
          for (; (uVar4 != 0 && (*pbVar3 != 0)); pbVar3 = pbVar3 + 1) {
            if (((&DAT_0069f56d)[*pbVar3] & 4) != 0) {
              pbVar3 = pbVar3 + 1;
            }
            uVar4 = uVar4 - 1;
          }
          uVar4 = MultiByteToWideChar(*(UINT *)PTR_DAT_00520d10,1,(LPCSTR)param_2,
                                      (int)pbVar3 - (int)param_2,param_1,param_3);
          if (uVar4 == 0) {
            uVar4 = 0xffffffff;
          }
        }
        else {
          uVar4 = 0xffffffff;
        }
      }
      else {
        uVar4 = iVar1 - 1;
      }
    }
    else if (param_3 != 0) {
      do {
        *param_1 = (ushort)param_2[uVar4];
        if (param_2[uVar4] == 0) {
          return uVar4;
        }
        uVar4 = uVar4 + 1;
        param_1 = param_1 + 1;
      } while (uVar4 < param_3);
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

