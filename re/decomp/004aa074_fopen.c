// fopen @ 004aa074 size=51 sig=undefined fopen() cc=unknown
// callers: FUN_0047997c,GetHighScores,FUN_0048fd95,FUN_00412654,DebugLog,FUN_00411534,FUN_00412154,FUN_00479b6c,FUN_0046578c,InitDebugLogs,FUN_0041161c,DumpGameOptions,FUN_004657e0,FUN_00479700,FUN_00410b10,FUN_0041287c,FUN_00479de4,FUN_00467e58,HdxArchive_Open
// callees: FUN_004aa048,FUN_004ab628,FUN_004a9fa0,FUN_004ab638

/* RTL */

undefined4 fopen(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_004ab628();
  iVar1 = FUN_004aa048();
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_004a9fa0(iVar1,param_1,param_2,0);
  }
  FUN_004ab638();
  return uVar2;
}

