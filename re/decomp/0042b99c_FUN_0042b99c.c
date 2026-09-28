// FUN_0042b99c @ 0042b99c size=252 sig=undefined FUN_0042b99c() cc=unknown
// callers: 
// callees: FUN_0049eb9f,FUN_00491e02,FUN_00493108,FUN_0049ea99,sprintf,FUN_0049a93f,FUN_0049a8ed,FUN_0049aa64,FUN_0049f22b,FUN_004a43da

undefined4 FUN_0042b99c(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined1 local_10 [12];
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    piVar3 = &local_20;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049f22b(uVar1,piVar3);
    FUN_0049aa64(&local_20);
    FUN_004a43da(param_1,3,param_3,param_4);
    iVar2 = FUN_0049eb9f(param_1,0);
    if (iVar2 != 0) {
      if (*(int *)(param_1 + 0x30) == 0x27) {
        sprintf(local_10,&DAT_004bdae8,*(undefined4 *)(param_1 + 0x48));
      }
      else {
        sprintf(local_10,&DAT_004bdaeb,*(undefined4 *)(param_1 + 0x48));
      }
      local_1c = *(int *)(param_1 + 0x10);
      local_20 = *(int *)(param_1 + 0xc) + DAT_004bda64;
      local_18 = local_20 + *(int *)(param_1 + 0x18);
      local_14 = local_1c + *(int *)(param_1 + 0x14);
      FUN_00491e02(0x30);
      FUN_0049a8ed();
      FUN_0049aa64(&local_20);
      FUN_00493108(local_10,&local_20,9,0);
      FUN_0049a93f();
    }
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

