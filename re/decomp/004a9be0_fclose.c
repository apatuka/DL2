// fclose @ 004a9be0 size=159 sig=undefined fclose() cc=unknown
// callers: FUN_0047997c,GetHighScores,FUN_0048fd95,FUN_00412654,DebugLog,FUN_00411534,FUN_00412154,FUN_00479b6c,FUN_0046578c,FUN_00479a5c,InitDebugLogs,FUN_0041161c,DumpGameOptions,FUN_004657e0,FUN_00479700,FUN_00411dd4,FUN_00410b10,FUN_004a9fa0,FUN_0041287c,FUN_00479de4,FUN_00467e58,HdxArchive_Open
// callees: FUN_004aa828,FUN_004ad1a4,FUN_004ab648,FUN_004a9c80,FUN_004b0a30,FUN_004ab710,FUN_004ace78

/* RTL */

undefined4 fclose(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if ((param_1 == 0) || ((char)param_1 != *(char *)(param_1 + 0x17))) {
    return 0xffffffff;
  }
  FUN_004ab648(param_1);
  if (*(int *)(param_1 + 0xc) != 0) {
    if ((*(int *)(param_1 + 8) < 0) && (iVar1 = FUN_004a9c80(param_1), iVar1 != 0)) {
      uVar3 = 0xffffffff;
      goto LAB_004a9c71;
    }
    if ((*(byte *)(param_1 + 0x12) & 4) != 0) {
      FUN_004b0a30(*(undefined4 *)(param_1 + 4));
    }
  }
  uVar3 = FUN_004ace78((int)*(char *)(param_1 + 0x16));
  *(undefined2 *)(param_1 + 0x12) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined1 *)(param_1 + 0x16) = 0xff;
  if (*(short *)(param_1 + 0x10) != 0) {
    uVar2 = FUN_004aa828(0,0,*(short *)(param_1 + 0x10));
    FUN_004ad1a4(uVar2);
    *(undefined2 *)(param_1 + 0x10) = 0;
  }
LAB_004a9c71:
  FUN_004ab710(param_1);
  return uVar3;
}

