// FUN_004a4025 @ 004a4025 size=238 sig=undefined FUN_004a4025() cc=unknown
// callers: FUN_00426140,FUN_004196e4,FUN_00416448,FUN_00423cc4,FUN_0042e4c0,FUN_0043c514,FUN_00413e88,FUN_0042f5ac,FUN_0042740c,FUN_004198e0,FUN_00425f58,FUN_00439e6c,CheckSubInfo,FUN_0042ac2c,FUN_00428a24,CheckSubUnit,CheckSubTech,FUN_00416630,FUN_00421990,FUN_0041f4ac,FUN_0041e7ec,FUN_00415830,FUN_0042eb7c,FUN_0042eff4,FUN_00427d74,FUN_004393a0,FUN_0042bc24,FUN_0042e054,FUN_00432dd0,FUN_004360ec,FUN_004375c0,FUN_00428620,FUN_00436838,FUN_0042e7c0,FUN_00430410,FUN_00420c48,FUN_00424564,FUN_0044b518,FUN_0041375c,FUN_004226a0,FUN_0042824c,FUN_00423f18,FUN_004149fc,FUN_0041482c,FUN_004362b4,FUN_0041d188,FUN_0043e37c,FUN_0043cb34,FUN_00426a84,FUN_00432df8,FUN_0042d27c,FUN_0042c2fc,FUN_004169b0,FUN_0041ac8c,FUN_004a5af2,FUN_004251d8,FUN_00432de4,FUN_004a4113,FUN_00436ec8,FUN_00432dbc,FUN_00438254,FUN_0043a4a8,FUN_004154e8
// callees: FUN_004a5dda,FUN_0049f83e,FUN_004a17f6,FUN_00495544,FUN_0049116d,FUN_004954a9,FUN_004989cf,FUN_004a3f2e,FUN_00495162,FUN_004a1797,FUN_0049551a
// strings: \"Disposed SMenu %c%c%c%c, chain count = %d\\r\\n\"

void FUN_004a4025(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 != 0) && (iVar1 = FUN_0049551a(DAT_0051e384,param_1), iVar1 != -1)) {
    FUN_0049f83e(param_1);
    if ((param_1 != 0) && ((*(int *)(param_1 + 300) != 0 && (**(int **)(param_1 + 300) != 0)))) {
      while (**(int **)(param_1 + 300) != 0) {
        FUN_004a3f2e(param_1,**(int **)(param_1 + 300),2);
      }
    }
    if (*(int *)(param_1 + 0x54) != 0) {
      FUN_0049116d(*(undefined4 *)(param_1 + 0x54));
    }
    FUN_004a17f6(param_1,0);
    if (*(int *)(param_1 + 0x28) != 0) {
      FUN_004a5dda(*(undefined4 *)(param_1 + 0x28));
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
    FUN_004a1797(param_1);
    FUN_004954a9(DAT_0051e384,param_1);
    if ((DAT_0051e388 & 1) != 0) {
      uVar2 = FUN_00495544(DAT_0051e384);
      FUN_00495162(s_Disposed_SMenu__c_c_c_c__chain_c_0051e4a8,(int)*(char *)(param_1 + 0x30),
                   (int)(char)((uint)*(undefined4 *)(param_1 + 0x30) >> 8),
                   (int)(char)((uint)*(undefined4 *)(param_1 + 0x30) >> 0x10),
                   (int)(char)((uint)*(undefined4 *)(param_1 + 0x30) >> 0x18),uVar2);
    }
    FUN_004989cf(param_1);
  }
  return;
}

