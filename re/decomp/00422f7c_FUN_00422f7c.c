// FUN_00422f7c @ 00422f7c size=392 sig=undefined FUN_00422f7c() cc=unknown
// callers: 
// callees: FUN_00421a54,FUN_00422bb4,FUN_00421e3c,FUN_0044a000,FUN_004a43da,FUN_00422344,FUN_0048db5d,FUN_004503f4,FUN_0049eb44,FUN_00421b24

undefined4 FUN_00422f7c(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 == 0x3b) {
    FUN_004a43da(param_1,0x3b,param_3,param_4);
    if (param_4 != 0) {
      iVar1 = FUN_0049eb44(DAT_004b7b50,0xe,1,0x22,0,0);
      FUN_00422bb4(iVar1);
      if (*(int *)(&DAT_00651cbc +
                  *(int *)(&DAT_0053c4e0 + iVar1 * 6 + DAT_004b7b44 * 0x4802) * 0x14) == 0) {
        if (DAT_0053c4dc == 0) {
          uVar2 = FUN_004503f4((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],8,0xffffffff);
          iVar1 = FUN_00421b24(uVar2);
          if (iVar1 == 0) {
            FUN_00421a54();
            FUN_00422344();
          }
          else {
            FUN_00422344();
            FUN_0044a000();
            DAT_004d59a4 = 1;
            FUN_0048db5d(0);
            DAT_004d59a4 = 0;
            FUN_00421e3c();
            DAT_0053c4dc = 1;
          }
        }
        else if (DAT_004b7b58 == 0) {
          FUN_00421a54();
          FUN_00422344();
          DAT_0053c4dc = 1;
        }
      }
      else {
        iVar1 = FUN_00421b24(*(undefined4 *)
                              (&DAT_00651cbc +
                              *(int *)(&DAT_0053c4e0 + iVar1 * 6 + DAT_004b7b44 * 0x4802) * 0x14));
        if (iVar1 != 0) {
          FUN_00422344();
          FUN_0044a000();
          DAT_004d59a4 = 1;
          FUN_0048db5d(0);
          DAT_004d59a4 = 0;
          FUN_00421e3c();
          DAT_0053c4dc = 1;
        }
      }
    }
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar2;
}

