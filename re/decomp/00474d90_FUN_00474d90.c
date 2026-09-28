// FUN_00474d90 @ 00474d90 size=181 sig=undefined FUN_00474d90() cc=unknown
// callers: FUN_00476dcc,FUN_004761b0,FUN_004760d0,FUN_00476448,FUN_004764dc,FUN_00476324,FUN_004765a8,FUN_00475ce8,FUN_00476760,FUN_00476aac,FUN_004775c8,FUN_00476e40,FUN_004757c0,FUN_00474ff0,FUN_0047597c,FUN_00477888,FUN_00477620,FUN_00476668,FUN_00476b58,FUN_00476cc0,FUN_004762a8,FUN_00475d60,FUN_00475ba4,FUN_00477724,FUN_00476ae4,FUN_00475a60,FUN_00475854,FUN_0047654c,FUN_00476d48,FUN_00475e40
// callees: FUN_00474d0c,FUN_00477f9c,MessagePump

undefined4 FUN_00474d90(uint param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((DAT_0058f1f4 == DAT_004d5a58) || (DAT_0058f1fc == 0)) {
    uVar1 = 1;
    if (DAT_004d826c != 2) {
      uVar1 = 0;
    }
  }
  else {
    iVar2 = FUN_00474d0c(param_1);
    if (iVar2 == 2) {
      do {
        do {
          uVar1 = DAT_004d59a4;
          DAT_004d59a4 = 1;
          DAT_004d8260 = 1;
          MessagePump();
          DAT_004d8260 = 0;
          DAT_004d59a4 = uVar1;
          FUN_00477f9c();
        } while (param_1 != DAT_00653598);
      } while (param_2 != DAT_006535a6);
      if ((param_1 == DAT_00653598) && (param_2 == DAT_006535a6)) {
        uVar1 = 1;
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

