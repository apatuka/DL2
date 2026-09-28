// FUN_0048960b @ 0048960b size=448 sig=undefined FUN_0048960b() cc=unknown
// callers: FUN_0048997c,FUN_004899ca
// callees: _SmackToBuffer@28,FUN_0048c85e,LeaveCriticalSection,FUN_004a60b1,FUN_004895e4,EnterCriticalSection,_SmackDoFrame@4,_SmackToBufferRect@8,FUN_00495c51,FUN_0048c434

undefined4 FUN_0048960b(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int *piVar6;
  int local_28 [4];
  int local_18 [4];
  undefined4 *local_8;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x1c) != 0)) {
    piVar1 = *(int **)(param_1 + 0x1c);
    iVar2 = *piVar1;
    local_8 = DAT_0051bddc;
    if (((*(int *)(param_1 + 0x18) == 0) && (DAT_0051bddc != (undefined4 *)0x0)) ||
       ((*(int *)(param_1 + 0x18) != 0 &&
        (iVar3 = FUN_0048c434(*(undefined4 *)(param_1 + 0x18)), iVar3 != 0)))) {
      uVar4 = FUN_004895e4(DAT_0051bddc);
      if ((*(byte *)(param_1 + 0x14) & 2) == 0) {
        _SmackToBuffer_28(iVar2,piVar1[1],piVar1[2],DAT_0051bddc[4],*(undefined4 *)(iVar2 + 8),
                          *DAT_0051bddc,uVar4);
      }
      else {
        _SmackToBuffer_28(iVar2,0,0,DAT_0051bddc[4],*(undefined4 *)(iVar2 + 8),*DAT_0051bddc,uVar4);
      }
      _SmackDoFrame_4(iVar2);
      if (*(int *)(param_1 + 0x18) != 0) {
        FUN_0048c434(local_8);
      }
      if ((*(byte *)(param_1 + 0x14) & 1) == 0) {
        if (*(int *)(param_1 + 0x18) != 0) {
          if (DAT_0051b83c != 0) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
          }
          while (iVar3 = _SmackToBufferRect_8(iVar2,0), iVar3 != 0) {
            local_18[0] = *(int *)(iVar2 + 0x380);
            local_18[1] = *(int *)(iVar2 + 900);
            local_18[2] = *(int *)(iVar2 + 0x380) + *(int *)(iVar2 + 0x388);
            local_18[3] = *(int *)(iVar2 + 900) + *(int *)(iVar2 + 0x38c);
            piVar5 = local_18;
            piVar6 = local_28;
            for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
              *piVar6 = *piVar5;
              piVar5 = piVar5 + 1;
              piVar6 = piVar6 + 1;
            }
            if ((*(byte *)(param_1 + 0x14) & 2) != 0) {
              FUN_00495c51(local_28,piVar1[1],piVar1[2]);
            }
            FUN_0048c85e(*(undefined4 *)(param_1 + 0x18),&DAT_0065e644,local_18,local_28,0,0,0);
          }
          if (DAT_0051b83c != 0) {
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
          }
        }
      }
      else {
        while (iVar3 = _SmackToBufferRect_8(iVar2,0), iVar3 != 0) {
          local_18[0] = *(int *)(iVar2 + 0x380);
          local_18[1] = *(int *)(iVar2 + 900);
          local_18[2] = local_18[0] + *(int *)(iVar2 + 0x388);
          local_18[3] = local_18[1] + *(int *)(iVar2 + 0x38c);
          FUN_004a60b1(local_18,0);
        }
      }
      return 1;
    }
  }
  return 0;
}

