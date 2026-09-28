// FUN_004b1fb4 @ 004b1fb4 size=887 sig=undefined FUN_004b1fb4() cc=unknown
// callers: FUN_004b1bfc
// callees: FUN_004b185c,WaitForSingleObject,FUN_004b1e64,memset,FUN_004b01d4,FUN_004aff84,FUN_004b1dac,FUN_004b18ac,CreateProcessA,FUN_004b1f50,GetLastError,FUN_004b1da4,FUN_004b17e4,GetExitCodeProcess,FUN_004b0a30,FUN_004ac5c4,CloseHandle,FUN_004b002c,FUN_004b0b44,FUN_004b12c4
// strings: \"COMSPEC\"

DWORD FUN_004b1fb4(int param_1,char *param_2,undefined4 *param_3,int param_4,undefined4 param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  LPSTR lpCommandLine;
  BOOL BVar6;
  DWORD DVar7;
  LPCSTR lpApplicationName;
  undefined4 uVar8;
  LPVOID lpEnvironment;
  _PROCESS_INFORMATION local_174;
  _STARTUPINFOA local_164;
  _SECURITY_ATTRIBUTES local_120;
  CHAR local_114 [260];
  int local_10;
  LPCSTR local_c;
  DWORD local_8;
  
  uVar1 = (uint)*param_2;
  if (0x60 < uVar1) {
    uVar1 = uVar1 - 0x20;
  }
  if ((((0x40 < uVar1) && (uVar1 < 0x5b)) && (param_2[1] == ':')) ||
     ((iVar2 = FUN_004aff84(param_2,0x2f), iVar2 != 0 ||
      (iVar2 = FUN_004aff84(param_2,0x5c), iVar2 != 0)))) {
    param_5 = 0;
  }
  iVar2 = 0;
  local_10 = FUN_004b01d4(param_2,0x2e);
  if (local_10 == 0) {
    iVar3 = FUN_004b1dac(param_2,local_114,&DAT_005213ac,param_5);
    if ((iVar3 == 0) &&
       (iVar2 = FUN_004b1dac(param_2,local_114,&DAT_005213b1,param_5), iVar3 = iVar2, iVar2 == 0)) {
      iVar2 = FUN_004b1dac(param_2,local_114,&DAT_005213b6,param_5);
      iVar3 = iVar2;
    }
  }
  else {
    iVar3 = FUN_004b1dac(param_2,local_114,&DAT_005213a1,param_5);
    if ((iVar3 != 0) &&
       ((iVar4 = FUN_004b002c(local_10,&DAT_005213a2), iVar4 == 0 ||
        (iVar4 = FUN_004b002c(local_10,&DAT_005213a7), iVar4 == 0)))) {
      iVar2 = 1;
    }
  }
  if ((iVar3 == 0) ||
     ((iVar2 != 0 && (local_c = (LPCSTR)FUN_004b18ac(s_COMSPEC_005213bb), local_c == (LPCSTR)0x0))))
  {
    puVar5 = (undefined4 *)FUN_004b12c4();
    *puVar5 = 2;
    return 0xffffffff;
  }
  if (iVar2 == 0) {
    lpCommandLine = (LPSTR)FUN_004b1e64(*param_3,0,param_3 + 1);
  }
  else {
    lpCommandLine = (LPSTR)FUN_004b1e64(local_c,&DAT_005213c3,param_3);
  }
  if (lpCommandLine == (LPSTR)0x0) {
    puVar5 = (undefined4 *)FUN_004b12c4();
    *puVar5 = 8;
    return 0xffffffff;
  }
  if (param_4 == 0) {
    lpEnvironment = (LPVOID)0x0;
  }
  else {
    lpEnvironment = (LPVOID)FUN_004b1f50(param_4);
    if (lpEnvironment == (LPVOID)0x0) goto LAB_004b215a;
  }
  (*(code *)PTR_FUN_005212ec)();
  memset(&local_164,0,0x44);
  local_164.cb = 0x44;
  local_164.wShowWindow = 10;
  if (DAT_0051fce0 != 0) {
    local_164.cbReserved2 = (*(code *)PTR_FUN_00520840)(0);
    local_164.lpReserved2 = (LPBYTE)FUN_004b0b44(local_164.cbReserved2);
    if (local_164.lpReserved2 == (LPBYTE)0x0) {
LAB_004b215a:
      puVar5 = (undefined4 *)FUN_004b12c4();
      *puVar5 = 8;
      FUN_004b0a30(lpCommandLine);
      return 0xffffffff;
    }
    (*(code *)PTR_FUN_00520840)(local_164.lpReserved2);
  }
  local_120.nLength = 0xc;
  local_120.lpSecurityDescriptor = (LPVOID)0x0;
  local_120.bInheritHandle = 1;
  DVar7 = 8;
  if (param_1 != 4) {
    DVar7 = 0;
  }
  lpApplicationName = local_c;
  if (iVar2 == 0) {
    lpApplicationName = local_114;
  }
  BVar6 = CreateProcessA(lpApplicationName,lpCommandLine,&local_120,&local_120,1,DVar7,lpEnvironment
                         ,(LPCSTR)0x0,&local_164,&local_174);
  if (BVar6 != 1) {
    DVar7 = GetLastError();
    uVar1 = DVar7 & 0xffff;
    if (uVar1 == 1) {
      uVar8 = 0x13;
    }
    else if (uVar1 == 8) {
      uVar8 = 8;
    }
    else if (uVar1 == 0x59) {
      uVar8 = 0x2a;
    }
    else {
      uVar8 = 0x15;
    }
    puVar5 = (undefined4 *)FUN_004b12c4();
    *puVar5 = uVar8;
    local_8 = 0xffffffff;
    goto LAB_004b2314;
  }
  if (param_1 == 0) {
    WaitForSingleObject(local_174.hProcess,0xffffffff);
    GetExitCodeProcess(local_174.hProcess,&local_8);
    CloseHandle(local_174.hProcess);
  }
  else if (param_1 == 1) {
LAB_004b22d4:
    local_8 = (*(code *)PTR_FUN_00521398)(local_174.dwProcessId,local_174.hProcess);
  }
  else {
    if (param_1 == 2) {
      FUN_004b0a30(lpEnvironment);
      FUN_004b0a30(lpCommandLine);
      FUN_004b185c(0);
    }
    else if (param_1 - 3U < 2) {
      CloseHandle(local_174.hProcess);
      goto LAB_004b22d4;
    }
    local_8 = 0xffffffff;
  }
  CloseHandle(local_174.hThread);
LAB_004b2314:
  FUN_004b0a30(lpEnvironment);
  FUN_004b0a30(lpCommandLine);
  return local_8;
}

