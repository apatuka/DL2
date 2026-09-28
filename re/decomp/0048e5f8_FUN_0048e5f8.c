// FUN_0048e5f8 @ 0048e5f8 size=94 sig=undefined FUN_0048e5f8() cc=unknown
// callers: FUN_004a5699,FUN_0048e656,FUN_004a3533,LoadPhaseSprites,FUN_004a335b,FUN_00490122
// callees: FUN_00495162,FUN_004b185c,FUN_0049539b,FUN_004ab474

void FUN_0048e5f8(int param_1)

{
  code *pcVar1;
  undefined1 local_204 [512];
  
  if (DAT_0051c3a0 != 0) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 != 0) {
    FUN_004ab474(local_204,param_1,&stack0x00000008);
    FUN_0049539b(local_204);
    if ((DAT_0051dcc4 & 0x80) != 0) {
      FUN_00495162(local_204);
    }
  }
  FUN_004b185c(1);
  return;
}

