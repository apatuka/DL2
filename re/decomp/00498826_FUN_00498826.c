// FUN_00498826 @ 00498826 size=214 sig=undefined FUN_00498826() cc=unknown
// callers: FUN_004988fc
// callees: FUN_00488a09,FUN_00488998,FUN_0049539b,FUN_004984f5,FUN_0049859f,FUN_00488c1c
// strings: \"Can't create '%s'.\\n\"|\"Write error on '%s'\"

void FUN_00498826(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 local_9;
  uint local_8;
  
  if (param_2 != 0) {
    iVar2 = FUN_00488998(param_1,0x200);
    if (iVar2 == -1) {
      FUN_0049539b(s_Can_t_create___s___0051e174,param_1);
    }
    else {
      cVar1 = FUN_0049859f(iVar2,0,param_2,0);
      if (cVar1 == '\0') {
        FUN_0049539b(s_Write_error_on___s__0051e188,param_1);
      }
      else {
        local_8 = FUN_004984f5(iVar2,param_2,0);
        if ((int)local_8 < 0) {
          FUN_0049539b(s_Write_error_on___s__0051e19c,param_1);
        }
        else {
          if ((local_8 & 1) != 0) {
            local_8 = local_8 + 1;
            local_9 = 0;
            iVar3 = FUN_00488c1c(iVar2,&local_9,1);
            if (iVar3 != 1) {
              FUN_0049539b(s_Write_error_on___s__0051e1b0,param_1);
              FUN_00488a09(iVar2);
              return;
            }
          }
          FUN_0049859f(iVar2,local_8,param_2,0);
        }
      }
      FUN_00488a09(iVar2);
      DAT_0051e170 = 0;
    }
  }
  return;
}

