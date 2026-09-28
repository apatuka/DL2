// FUN_004acfa4 @ 004acfa4 size=512 sig=undefined FUN_004acfa4() cc=unknown
// callers: FUN_004b16d8,FUN_004a9fa0
// callees: FUN_004accf0,CreateFileA,GetLastError,CloseHandle,FUN_004acf08,FUN_004aca30,FUN_004ac964,FUN_004ac930,GetFileAttributesA

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004acfa4(LPCSTR param_1,uint param_2,uint param_3)

{
  int iVar1;
  HANDLE hObject;
  uint uVar2;
  DWORD dwFlagsAndAttributes;
  DWORD DVar3;
  _SECURITY_ATTRIBUTES local_18;
  DWORD local_c;
  DWORD local_8;
  
  FUN_004ac930();
  if ((param_2 & 0xc000) == 0) {
    param_2 = param_2 | *(uint *)PTR_DAT_00520264 & 0xc000;
  }
  if ((param_2 & 0x8000) == 0) {
    param_2 = param_2 | 0x4000;
  }
  uVar2 = param_2 & 0x700;
  if (uVar2 < 0x501) {
    if (uVar2 == 0x500) {
LAB_004ad014:
      DVar3 = 1;
    }
    else if (uVar2 == 0x100) {
      DVar3 = 4;
    }
    else {
      if (uVar2 == 0x200) goto LAB_004ad029;
      if (uVar2 != 0x300) goto LAB_004ad030;
      DVar3 = 2;
    }
  }
  else if (uVar2 == 0x600) {
LAB_004ad029:
    DVar3 = 5;
  }
  else {
    if (uVar2 == 0x700) goto LAB_004ad014;
LAB_004ad030:
    DVar3 = 3;
  }
  if ((param_2 & 0x100) == 0) {
    dwFlagsAndAttributes = GetFileAttributesA(param_1);
    if (dwFlagsAndAttributes == 0xffffffff) {
      dwFlagsAndAttributes = 0;
    }
  }
  else if ((param_3 & _DAT_00520844 & 0x80) == 0) {
    dwFlagsAndAttributes = 1;
  }
  else {
    dwFlagsAndAttributes = 0x80;
  }
  uVar2 = param_2 & 3;
  if (uVar2 == 0) {
    local_8 = 0x80000000;
  }
  else if (uVar2 == 1) {
    local_8 = 0x40000000;
  }
  else {
    if (uVar2 != 2) {
      iVar1 = FUN_004accf0(1);
      goto LAB_004ad196;
    }
    local_8 = 0xc0000000;
  }
  uVar2 = param_2 & 0x70;
  if (uVar2 == 0x10) {
    local_c = 0;
  }
  else if (uVar2 == 0x20) {
    local_c = 1;
  }
  else if (uVar2 == 0x30) {
    local_c = 2;
  }
  else {
    local_c = 3;
  }
  local_18.nLength = 0xc;
  local_18.lpSecurityDescriptor = (LPVOID)0x0;
  local_18.bInheritHandle = (BOOL)((param_2 & 0x80) == 0);
  hObject = CreateFileA(param_1,local_8,local_c,&local_18,DVar3,dwFlagsAndAttributes,(HANDLE)0x0);
  if (hObject == (HANDLE)0xffffffff) {
    DVar3 = GetLastError();
    uVar2 = DVar3 & 0xffff;
    if ((uVar2 == 0x6e) && (uVar2 = 0x50, (param_2 & 0x100) == 0)) {
      uVar2 = 2;
    }
    iVar1 = FUN_004accf0(uVar2);
  }
  else {
    iVar1 = FUN_004acf08(hObject);
    if (iVar1 != 0) {
      param_2 = param_2 | 0x2000;
    }
    iVar1 = FUN_004aca30(hObject,param_2 & 0xfffff8ff);
    if (iVar1 == -1) {
      FUN_004accf0(4);
      CloseHandle(hObject);
    }
  }
LAB_004ad196:
  FUN_004ac964();
  return iVar1;
}

