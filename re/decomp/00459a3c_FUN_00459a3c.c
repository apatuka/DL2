// FUN_00459a3c @ 00459a3c size=396 sig=undefined FUN_00459a3c() cc=unknown
// callers: FUN_00459bdc
// callees: sprintf,FUN_00459ee0,FUN_0043ee40,FUN_004847f8,FUN_00459864

void FUN_00459a3c(undefined4 param_1,int param_2,int *param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 local_28 [16];
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  iVar4 = 0;
  do {
    if (*param_3 != 0) {
      pcVar1 = *(char **)(param_2 + 0x80 + *(char *)(param_2 + 0x75) * 4);
      iVar3 = (int)*pcVar1;
      iVar2 = (int)pcVar1[1];
      switch(iVar4) {
      case 0:
        local_10 = 1;
        local_18 = 0;
        local_14 = 0;
        break;
      case 1:
        if (*(char *)(param_2 + 0x21) == '\0') {
          if (param_4 == 0) {
            local_10 = 6;
          }
          else {
            local_10 = 7;
          }
        }
        else {
          local_10 = 0;
        }
        local_14 = 0;
        local_18 = 0x10;
        break;
      case 2:
        local_10 = 2;
        iVar2 = iVar2 + 1;
        local_18 = 0;
        local_14 = 0;
        break;
      case 3:
        if (*(char *)(param_2 + 0x21) == '\0') {
          local_10 = 3;
        }
        else {
          local_10 = 4;
        }
        iVar2 = iVar2 + 1;
        local_14 = 0;
        local_18 = 0x10;
        break;
      case 4:
        local_10 = 5;
        iVar3 = iVar3 + 3;
        iVar2 = iVar2 + 1;
        local_18 = 0;
        local_14 = 0;
      }
      if (DAT_004d5ad0 == 0) {
        FUN_00459ee0(iVar3,iVar2,&local_8,&local_c);
      }
      else {
        FUN_0043ee40(iVar3,iVar2,&local_8,&local_c);
        local_c = local_c + -0x20;
      }
      local_8 = local_8 + local_14;
      local_c = local_c + local_18;
      FUN_00459864(param_1,(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] + 1000,local_10,local_8,
                   local_c);
      sprintf(local_28,&DAT_004d1b84,*param_3);
      FUN_004847f8(local_8 + 0x10,local_c + 0x10,local_28,0xff);
    }
    iVar4 = iVar4 + 1;
    param_3 = param_3 + 1;
  } while (iVar4 < 5);
  return;
}

