// FUN_004609e8 @ 004609e8 size=139 sig=undefined FUN_004609e8() cc=unknown
// callers: FUN_00460a74
// callees: ReadFile,FUN_004b02a8,FUN_00484da8,FUN_00484c2c

undefined4 FUN_004609e8(HANDLE param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  BOOL BVar3;
  undefined1 local_3c [48];
  DWORD local_c;
  char local_5;
  
  iVar1 = FUN_004b02a8(8);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00484c2c(iVar1);
  }
  *param_2 = uVar2;
  if (1 < DAT_00583da4) {
    BVar3 = ReadFile(param_1,&local_5,1,&local_c,(LPOVERLAPPED)0x0);
    if (BVar3 == 0) {
      return 0;
    }
    while (local_5 != '\0') {
      local_5 = local_5 + -1;
      BVar3 = ReadFile(param_1,local_3c,0x30,&local_c,(LPOVERLAPPED)0x0);
      if (BVar3 == 0) {
        return 0;
      }
      FUN_00484da8(*param_2,local_3c);
    }
  }
  return 1;
}

