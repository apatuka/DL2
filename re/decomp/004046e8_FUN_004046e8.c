// FUN_004046e8 @ 004046e8 size=183 sig=undefined FUN_004046e8() cc=unknown
// callers: 
// callees: FUN_004412d4,FUN_004504a4,FUN_0040526c,FUN_0045093c

void FUN_004046e8(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (((1 << ((byte)param_3 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0) ||
     (*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) < -0x13)) {
    iVar2 = FUN_004412d4(param_1,param_3,0x10);
    if ((iVar2 != 0) && (*(int *)(&DAT_005220a4 + param_2 * 4 + param_1 * 0x1c) < 0x14)) {
      uVar5 = 0;
      uVar4 = 0;
      uVar3 = 0;
      uVar1 = FUN_004504a4(param_1,0x20);
      FUN_0045093c(param_1,1 << ((byte)param_2 & 0x1f),0x20,uVar1,uVar3,uVar4,uVar5);
      FUN_0040526c(param_1,param_2,0xfffffff8);
    }
  }
  else {
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = 0;
    uVar1 = FUN_004504a4(param_1,0x23);
    FUN_0045093c(param_1,1 << ((byte)param_2 & 0x1f),0x23,uVar1,uVar3,uVar4,uVar5);
    FUN_0040526c(param_1,param_2,8);
  }
  return;
}

