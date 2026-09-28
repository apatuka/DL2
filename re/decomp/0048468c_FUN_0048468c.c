// FUN_0048468c @ 0048468c size=240 sig=undefined FUN_0048468c() cc=unknown
// callers: FUN_004847f8,FUN_004847c8,FUN_0048477c
// callees: FUN_00491a2b,FUN_00491e02,FUN_0048463c,FUN_00491fad,FUN_00491d38,FUN_00492aac,FUN_00491df3,FUN_00491f47,FUN_00491efa,FUN_00491f94,FUN_00492578,FUN_00491ace

void FUN_0048468c(uint param_1,undefined4 param_2,char *param_3,int param_4,int param_5)

{
  char cVar1;
  
  if (param_3 != (char *)0x0) {
    if (DAT_00508f90 == -1) {
      FUN_0048463c(0);
    }
    FUN_00491a2b(*(undefined4 *)(&DAT_00508f9c + DAT_00508f90 * 4));
    if (param_5 == 1) {
      FUN_00491df3(1);
      FUN_00491f94(1);
      FUN_00491fad(1,1);
      FUN_00491f47(0xf7);
    }
    else {
      FUN_00491df3(0);
    }
    FUN_00491d38(DAT_0058df44);
    if (param_4 == 0xff) {
      param_4 = -0x7f000001;
    }
    FUN_00491e02(param_4);
    FUN_00491efa(0xff);
    FUN_00492aac(param_1,param_2);
    while( true ) {
      cVar1 = *param_3;
      param_3 = param_3 + 1;
      if (cVar1 == '\0') break;
      if (cVar1 == '\t') {
        DAT_0065ec40 = DAT_0065ec40 + 0x10;
        DAT_0065ec40 = DAT_0065ec40 & 0x7ff0;
      }
      else if (cVar1 == '\n') {
        DAT_0065ec3c = DAT_0065ec3c + DAT_0065e010 + 1;
        DAT_0065ec40 = param_1;
      }
      else {
        FUN_00492578(cVar1);
      }
    }
    FUN_00491ace();
  }
  return;
}

