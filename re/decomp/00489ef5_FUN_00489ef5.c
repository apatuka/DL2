// FUN_00489ef5 @ 00489ef5 size=300 sig=undefined FUN_00489ef5() cc=unknown
// callers: 
// callees: CreateMutexA,FUN_00495454,ReleaseMutex,FUN_004989cf,FUN_00498ba9,timeSetEvent,FUN_00495162,timeBeginPeriod,FUN_0048f774
// strings: \"Unable to allocate sound buffer:size = %ul, format = %d, sample rate = %ul\"

DWORD_PTR FUN_00489ef5(undefined4 param_1,byte param_2,undefined2 *param_3)

{
  int iVar1;
  HANDLE pvVar2;
  MMRESULT MVar3;
  DWORD_PTR dwUser;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  undefined2 *local_8;
  
  dwUser = 0;
  if (DAT_0051b5fc != (int *)0x0) {
    dwUser = FUN_00498ba9(0x68);
    if (dwUser != 0) {
      FUN_0048f774(dwUser,0x68,0);
      *(DWORD_PTR *)(dwUser + 0x20) = dwUser;
      FUN_0048f774(&local_18,0x14,0);
      local_18 = 0x14;
      local_14 = 0;
      if ((param_2 & 1) == 0) {
        local_14 = 2;
      }
      local_14 = local_14 | 0xe0;
      local_10 = param_1;
      local_8 = param_3;
      iVar1 = (**(code **)(*DAT_0051b5fc + 0xc))(DAT_0051b5fc,&local_18,dwUser + 0x44,0);
      if (iVar1 == 0) {
        *(undefined4 *)(dwUser + 8) = param_1;
        *(undefined4 *)(dwUser + 0x24) = 1;
        *(undefined4 *)(dwUser + 0x5c) = 0;
        *(undefined4 *)(dwUser + 0x34) = 0;
        pvVar2 = CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,1,(LPCSTR)0x0);
        *(HANDLE *)(dwUser + 0x48) = pvVar2;
        FUN_00495454(DAT_0051e08c,dwUser,0);
        if ((param_2 & 2) == 0) {
          *(undefined4 *)(dwUser + 0x4c) = 0;
        }
        else {
          MVar3 = timeBeginPeriod(0x32);
          if (MVar3 == 0) {
            MVar3 = timeSetEvent(0x32,10,&LAB_0048a7b0,dwUser,1);
            *(MMRESULT *)(dwUser + 0x4c) = MVar3;
            *(undefined4 *)(dwUser + 100) = 0;
          }
          else {
            *(undefined4 *)(dwUser + 0x4c) = 0;
          }
        }
        ReleaseMutex(*(HANDLE *)(dwUser + 0x48));
      }
      else {
        if ((DAT_0051dcc5 & 4) != 0) {
          FUN_00495162(s_Unable_to_allocate_sound_buffer__0051b7c3,param_1,*param_3,
                       *(undefined4 *)(param_3 + 2));
        }
        FUN_004989cf(dwUser);
        dwUser = 0;
      }
    }
  }
  return dwUser;
}

