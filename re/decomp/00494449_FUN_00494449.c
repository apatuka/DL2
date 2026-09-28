// FUN_00494449 @ 00494449 size=1014 sig=undefined FUN_00494449() cc=unknown
// callers: FUN_00494c15,FUN_0049497a
// callees: FUN_00494b6b,EnterCriticalSection,FUN_00494346,FUN_0048c85e,FUN_004942d0,FUN_0048bb80,FUN_00496cc3,LeaveCriticalSection,FUN_00496ffb,FUN_00495c51

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_00494449(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_38 [4];
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_0051b83c != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  if ((((DAT_0065ec80 != 0) && (DAT_0065ec7c != 0)) && (DAT_0051dc9c != 0)) && (DAT_0065ecac != 0))
  {
    FUN_00496cc3(DAT_0065ecb0,DAT_0051dc78,0,DAT_0051dc70,&local_18);
    DAT_0065ec90 = local_14 + DAT_0065ec88;
    DAT_0065ec98 = local_c + DAT_0065ec88;
    DAT_0065ec8c = local_18 + DAT_0065ec84;
    DAT_0065ec94 = local_10 + DAT_0065ec84;
    iVar3 = DAT_0065ec94 - DAT_0065ec8c;
    local_8 = DAT_0065ec98 - DAT_0065ec90;
    iVar1 = FUN_004942d0(iVar3,local_8);
    if (iVar1 != 0) {
      if (((DAT_0051dc8c == 0) || (DAT_0065ec94 <= DAT_0065ec9c)) ||
         ((DAT_0065eca4 <= DAT_0065ec8c ||
          ((DAT_0065ec98 <= DAT_0065eca0 || (DAT_0065eca8 <= DAT_0065ec90)))))) {
        FUN_00494b6b();
        local_28 = 0;
        local_24 = 0;
        local_1c = local_8;
        local_20 = iVar3;
        FUN_0048c85e(DAT_0065ecac,DAT_0065ecbc,&DAT_0065ec8c,&local_28,0,0,0);
        iVar1 = FUN_00494346(iVar3,local_8);
        if (iVar1 != 0) {
          FUN_0048c85e(DAT_0065ecbc,DAT_0065ecb8,&local_28,&local_28,0,0,0);
        }
        piVar2 = &DAT_0065ec8c;
        piVar4 = &DAT_0065ec9c;
        for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
          *piVar4 = *piVar2;
          piVar2 = piVar2 + 1;
          piVar4 = piVar4 + 1;
        }
        piVar2 = &DAT_0065ec8c;
        piVar4 = local_38;
        for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
          *piVar4 = *piVar2;
          piVar2 = piVar2 + 1;
          piVar4 = piVar4 + 1;
        }
      }
      else {
        local_28 = 0;
        local_24 = 0;
        local_20 = *(undefined4 *)(DAT_0065ecbc + 4);
        local_1c = *(undefined4 *)(DAT_0065ecbc + 8);
        piVar2 = &DAT_0065ec8c;
        piVar4 = local_38;
        for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
          *piVar4 = *piVar2;
          piVar2 = piVar2 + 1;
          piVar4 = piVar4 + 1;
        }
        local_38[2] = *(int *)(DAT_0065ecbc + 4) + local_38[0];
        local_38[3] = *(int *)(DAT_0065ecbc + 8) + local_38[1];
        if (DAT_0065eca0 < local_38[1]) {
          FUN_00495c51(local_38,0,DAT_0065eca0 - local_38[1]);
        }
        if (DAT_0065ec9c < local_38[0]) {
          FUN_00495c51(local_38,DAT_0065ec9c - local_38[0],0);
        }
        FUN_0048c85e(DAT_0065ecac,DAT_0065ecbc,local_38,&local_28,0,0,0);
        local_20 = DAT_0065eca4 - DAT_0065ec9c;
        local_1c = DAT_0065eca8 - DAT_0065eca0;
        if (DAT_0065ec90 < DAT_0065eca0) {
          FUN_00495c51(&local_28,0,DAT_0065eca0 - DAT_0065ec90);
        }
        if (DAT_0065ec8c < DAT_0065ec9c) {
          FUN_00495c51(&local_28,DAT_0065ec9c - DAT_0065ec8c,0);
        }
        FUN_00495c51(&DAT_0065ec9c,-DAT_0065ec9c,-DAT_0065eca0);
        FUN_0048c85e(DAT_0065ecb8,DAT_0065ecbc,&DAT_0065ec9c,&local_28,0,0,0);
        iVar1 = FUN_00494346(iVar3,local_8);
        if (iVar1 != 0) {
          piVar2 = &DAT_0065ec8c;
          piVar4 = &DAT_0065ec9c;
          for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
            *piVar4 = *piVar2;
            piVar2 = piVar2 + 1;
            piVar4 = piVar4 + 1;
          }
          local_18 = local_38[0];
          local_14 = local_38[1];
          local_10 = (DAT_0065eca4 - DAT_0065ec9c) + local_38[0];
          local_c = (DAT_0065eca8 - DAT_0065eca0) + local_38[1];
          if (local_38[1] < DAT_0065eca0) {
            FUN_00495c51(&local_18,0,DAT_0065eca0 - local_38[1]);
          }
          if (local_38[0] < DAT_0065ec9c) {
            FUN_00495c51(&local_18,DAT_0065ec9c - local_38[0],0);
          }
          FUN_00495c51(&local_18,-local_38[0],-local_38[1]);
          local_28 = 0;
          local_24 = 0;
          local_20 = *(int *)(DAT_0065ecb8 + 4);
          local_1c = *(int *)(DAT_0065ecb8 + 8);
          FUN_0048c85e(DAT_0065ecbc,DAT_0065ecb8,&local_18,&local_28,0,0,0);
        }
      }
      DAT_0051dc8c = (uint)(DAT_0065ecb8 != 0);
      local_18 = 0;
      local_14 = 0;
      local_10 = *(int *)(DAT_0065ecbc + 4);
      local_c = *(int *)(DAT_0065ecbc + 8);
      FUN_0048bb80(DAT_0065ecbc,&local_18);
      FUN_00496ffb(DAT_0065ecb0,DAT_0051dc78,0,DAT_0051dc70,DAT_0065ec84 - local_38[0],
                   DAT_0065ec88 - local_38[1],0xffffffff,0,DAT_0065ecbc);
      FUN_0048c85e(DAT_0065ecbc,DAT_0065ecac,&local_18,local_38,0,0,0);
    }
  }
  if (DAT_0051b83c != 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0065e558);
  }
  return;
}

