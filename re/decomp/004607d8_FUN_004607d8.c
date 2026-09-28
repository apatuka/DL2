// FUN_004607d8 @ 004607d8 size=150 sig=undefined FUN_004607d8() cc=unknown
// callers: FUN_00460870
// callees: FUN_00484ebc,FUN_00484f10,FUN_00484ee0,FUN_00484e88,FUN_00484ea4,WriteFile,FUN_00484f48

undefined4 FUN_004607d8(HANDLE param_1,int param_2)

{
  BOOL BVar1;
  undefined4 uVar2;
  undefined1 local_3c [2];
  undefined2 local_3a;
  undefined1 local_38 [47];
  char local_9;
  DWORD local_8;
  
  if (param_2 == 0) {
    local_9 = '\0';
  }
  else {
    local_9 = FUN_00484e88(param_2);
    FUN_00484ea4(param_2);
  }
  BVar1 = WriteFile(param_1,&local_9,1,&local_8,(LPOVERLAPPED)0x0);
  if (BVar1 == 0) {
    uVar2 = 0;
  }
  else {
    while (local_9 != '\0') {
      local_9 = local_9 + -1;
      local_3c[0] = FUN_00484ee0(param_2);
      local_3a = FUN_00484f10(param_2);
      FUN_00484f48(param_2,local_38);
      BVar1 = WriteFile(param_1,local_3c,0x30,&local_8,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        return 0;
      }
      FUN_00484ebc(param_2);
    }
    uVar2 = 1;
  }
  return uVar2;
}

