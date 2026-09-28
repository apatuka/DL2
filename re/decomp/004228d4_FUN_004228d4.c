// FUN_004228d4 @ 004228d4 size=187 sig=undefined FUN_004228d4() cc=unknown
// callers: FUN_00422d04
// callees: FUN_00422874,FUN_0042278c

void FUN_004228d4(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = &DAT_00651cb4;
  (&DAT_00540ce0)[param_1 * 0x4802] = 0;
  for (iVar2 = 0; iVar2 < DAT_0065209c; iVar2 = iVar2 + 1) {
    iVar1 = FUN_0042278c(*puVar3);
    switch(*(undefined2 *)(&DAT_004fc914 + iVar1 * 0x12)) {
    case 0:
      if (param_1 == 0) {
        FUN_00422874(0,iVar2);
      }
      break;
    case 1:
    case 3:
    case 4:
    case 0xb:
      if (param_1 == 4) {
        FUN_00422874(4,iVar2);
      }
      break;
    case 5:
    case 10:
      if (param_1 == 3) {
        FUN_00422874(3,iVar2);
      }
      break;
    case 6:
      if (param_1 == 5) {
        FUN_00422874(5,iVar2);
      }
      break;
    case 8:
    case 9:
    case 0xc:
    case 0xd:
      if (param_1 == 2) {
        FUN_00422874(2,iVar2);
      }
      break;
    case 0xffff:
    case 2:
      if (param_1 == 1) {
        FUN_00422874(1,iVar2);
      }
    }
    puVar3 = puVar3 + 5;
  }
  return;
}

