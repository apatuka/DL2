// FUN_00496748 @ 00496748 size=384 sig=undefined FUN_00496748() cc=unknown
// callers: 
// callees: FUN_004989de,FUN_00498ba9,FUN_00496528,FUN_00496496,FUN_0048fe90,FUN_0049656f,FUN_004906e3,FUN_00496358,FUN_00498aab,FUN_00498b98,FUN_004989cf

undefined4
FUN_00496748(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,int param_5,
            int param_6)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int local_10;
  
  uVar5 = 1;
  if (param_5 == 2) {
    if (param_4[7] != 0) {
      if (param_4[9] == 0) {
        uVar2 = FUN_00498aab(param_4[7],1);
      }
      else {
        uVar2 = param_4[7];
      }
      FUN_00496528(uVar2);
      FUN_00496496(uVar2);
      if (param_4[9] == 0) {
        FUN_00498aab(param_4[7],0);
        FUN_004989de(param_4[7]);
      }
      else {
        FUN_004989cf(param_4[7]);
      }
      FUN_0048fe90(param_4);
    }
  }
  else if (param_5 == 3) {
    uVar2 = param_4[6];
    uVar1 = param_4[5];
    piVar4 = (int *)0x0;
    if (param_6 == 0) {
      local_10 = FUN_00498b98(uVar2);
      if (local_10 != 0) {
        piVar4 = (int *)FUN_00498aab(local_10,1);
      }
    }
    else {
      piVar4 = (int *)FUN_00498ba9(uVar2);
    }
    if (piVar4 != (int *)0x0) {
      iVar3 = FUN_004906e3(param_1,uVar1,uVar2,piVar4);
      if (iVar3 == 0) {
        if (*piVar4 != 2) {
          if (param_6 != 0) {
            FUN_004989cf(piVar4);
            return 0;
          }
          FUN_00498aab(local_10,0);
          local_10 = FUN_00496358(local_10,*param_4,0);
          if (local_10 == 0) {
            return 0;
          }
          piVar4 = (int *)FUN_00498aab(local_10,1);
        }
        piVar4[3] = param_1;
        FUN_0049656f(piVar4);
        FUN_0048fe90(param_4);
        param_4[9] = param_6;
        if (param_6 == 0) {
          FUN_00498aab(local_10,0);
          param_4[7] = local_10;
        }
        else {
          param_4[7] = piVar4;
        }
        uVar5 = 1;
      }
      else {
        if (param_6 == 0) {
          FUN_00498aab(local_10,0);
          FUN_004989de(local_10);
        }
        else {
          FUN_004989cf(piVar4);
        }
        uVar5 = 0;
      }
    }
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}

