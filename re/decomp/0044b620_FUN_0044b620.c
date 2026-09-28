// FUN_0044b620 @ 0044b620 size=58 sig=undefined FUN_0044b620() cc=unknown
// callers: FUN_0041c418,FUN_0044bc68,FUN_0044c49c,FUN_0044bd0c,FUN_0041d710
// callees: FUN_0044b5bc

undefined4 FUN_0044b620(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = FUN_0044b5bc(&DAT_005a43d0 + *(short *)(param_1 + 8) * 0xadc,
                         *(undefined4 *)(&DAT_004f9de6 + *(char *)(param_1 + 4) * 0x32));
  }
  return uVar1;
}

