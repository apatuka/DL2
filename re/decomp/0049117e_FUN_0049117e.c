// FUN_0049117e @ 0049117e size=75 sig=undefined FUN_0049117e() cc=unknown
// callers: FUN_0047b4ac,FUN_004a08c5,WinMain,FUN_00468214,RaceInit_dc94,FUN_00415924,FUN_004748dc,FUN_00416810,FUN_0049d315,FUN_004897ea,FUN_004752fc,FUN_00436a44,FUN_00474920,FUN_0049585a,FUN_00439e98,FUN_004a3533,FUN_0049ebfb,SynchronizeGame
// callees: FUN_00490ab3,FUN_00490d70

int FUN_0049117e(ushort *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int unaff_ESI;
  
  iVar1 = FUN_00490d70(param_1);
  if (iVar1 != 0) {
    param_1 = (ushort *)FUN_00490ab3(param_1,0x54525453,param_2,0,1);
  }
  if (param_1 != (ushort *)0x0) {
    if (param_3 < (int)(uint)*param_1) {
      unaff_ESI = (uint)param_1[param_3 + 2] + (int)param_1;
    }
    else {
      unaff_ESI = 0;
    }
  }
  return unaff_ESI;
}

