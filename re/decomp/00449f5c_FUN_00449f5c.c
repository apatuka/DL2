// FUN_00449f5c @ 00449f5c size=121 sig=undefined FUN_00449f5c() cc=unknown
// callers: FUN_0041ccb0,FUN_0045e398,FUN_0045d984,FUN_0045b304,FUN_0045d6a4,RunAITurns,FUN_0044a48c,FUN_0045dfd4,FUN_0044a5e8,FUN_0045b094,FUN_0044a000,FUN_00436db8,FUN_0045d418
// callees: FUN_004879fc,FUN_0043ba60,FUN_0049a8ed,FUN_0049a9e7,FUN_0049a93f,FUN_00482320

void FUN_00449f5c(void)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int local_18 [4];
  
  if (DAT_004d59b4 != 9) {
    if ((DAT_004d59b4 == 0) || (DAT_004d59b4 == 1)) {
      FUN_0043ba60();
    }
    else {
      puVar2 = &DAT_004c5ba8;
      piVar3 = local_18;
      for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        piVar3 = piVar3 + 1;
      }
      local_18[0] = DAT_004c5478;
      local_18[2] = DAT_004c5478 + DAT_004c5480;
      local_18[1] = DAT_004c547c;
      local_18[3] = DAT_004c547c + DAT_004c5484;
      FUN_0049a8ed();
      FUN_0049a9e7(local_18);
      FUN_00482320();
      FUN_0049a93f();
    }
    FUN_004879fc();
  }
  return;
}

