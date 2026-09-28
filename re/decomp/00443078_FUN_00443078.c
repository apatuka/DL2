// FUN_00443078 @ 00443078 size=321 sig=undefined FUN_00443078() cc=unknown
// callers: FUN_004432d4
// callees: 

void FUN_00443078(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  iVar1 = param_1 * 0x1a2;
  if (*(short *)(iVar1 + 0x55a866 + param_2 * 0x2a) == 0) {
    if (*(short *)(iVar1 + 0x55a876 + param_2 * 0x2a) == 0) {
      if (*(int *)((int)&DAT_0055a996 + param_2 * 4 + iVar1) == 0) {
        piVar4 = &DAT_0055a97a + param_2;
        for (uVar2 = *(uint *)((int)&DAT_0055a828 + iVar1); uVar2 != 0; uVar2 = (int)uVar2 >> 1) {
          if (((uVar2 & 1) != 0) && (*piVar4 != 0)) {
            *(undefined4 *)(&DAT_0055a838 + param_2 * 4 + iVar1) = 4;
            return;
          }
          piVar4 = (int *)((int)piVar4 + 0x1a2);
        }
        piVar4 = (int *)(&DAT_0055a838 + param_2 * 4 + iVar1);
        for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
            puVar3 = puVar3 + 0x2b7) {
          if ((param_2 == *(char *)(puVar3 + 8)) && ('\0' < *(char *)((int)puVar3 + param_3 + 0x66))
             ) {
            if ((1 << ((byte)param_1 & 0x1f) & puVar3[0x229]) == 0) {
              if ((*piVar4 == 0) &&
                 ((1 << (*(byte *)((int)puVar3 + 0x22) & 0x1f) &
                  *(uint *)((int)&DAT_0055a82c + iVar1)) != 0)) {
                *piVar4 = 1;
              }
            }
            else {
              if (*(short *)(puVar3 + 0x271) != 0) {
                *piVar4 = 3;
                return;
              }
              if (*piVar4 < 2) {
                *piVar4 = 2;
              }
            }
          }
        }
      }
      else {
        *(undefined4 *)(&DAT_0055a838 + param_2 * 4 + iVar1) = 5;
      }
    }
    else {
      *(undefined4 *)(&DAT_0055a838 + param_2 * 4 + iVar1) = 6;
    }
  }
  else {
    *(undefined4 *)(&DAT_0055a838 + param_2 * 4 + iVar1) = 7;
  }
  return;
}

