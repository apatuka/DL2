// FUN_0047fd88 @ 0047fd88 size=467 sig=undefined FUN_0047fd88() cc=unknown
// callers: FUN_00480150
// callees: FUN_00456d70,DrawSTileBuilding

/* WARNING: Removing unreachable block (ram,0x0047fe0c) */
/* WARNING: Removing unreachable block (ram,0x0047fe1e) */
/* WARNING: Removing unreachable block (ram,0x0047fe14) */

void FUN_0047fd88(int param_1,undefined4 param_2,undefined4 param_3,short param_4,undefined1 param_5
                 )

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  undefined1 local_12c [2];
  undefined2 local_12a;
  char local_128;
  undefined1 local_125;
  short local_124;
  int local_8;
  
  cVar1 = *(char *)(param_1 + 0x18);
  iVar6 = (int)cVar1;
  uVar2 = FUN_00456d70(param_1);
  iVar3 = (int)uVar2 >> 1;
  uVar2 = uVar2 & 1;
  local_8 = (int)(char)(&DAT_004f9dc5)[iVar6 * 0x32];
  if (((uVar2 != 0) || ((&DAT_005a43f1)[param_4 * 0xadc] != '\0')) || (iVar6 == 0x26)) {
    if ((iVar3 == 0) || (iVar3 == -1)) {
      if ((&DAT_004f9dc3)[iVar6 * 0x32] == '\x12') {
        if (uVar2 == 0) {
          iVar4 = 0x12;
        }
        else {
          iVar4 = 0;
          if (iVar3 == 0) {
            iVar4 = 1;
          }
        }
      }
      else {
        iVar4 = 0;
        if (uVar2 == 0) {
          iVar4 = 10;
        }
      }
      iVar5 = (int)(short)(&DAT_004f9dc0)[iVar6 * 0x19] + (int)*(char *)(param_1 + 0x19);
      puVar7 = (&PTR_DAT_004d02f4)[iVar5 * 3] + iVar4 * 0x10;
      if ((*(int *)(puVar7 + 8) == 0) ||
         ((*(short *)(puVar7 + 4) == 0 && (*(short *)(puVar7 + 6) == 0)))) {
        puVar7 = (&PTR_DAT_004d02f4)[iVar5 * 3];
      }
    }
    else if (uVar2 == 0) {
      iVar4 = 0x6f;
      if (local_8 != 1) {
        iVar4 = 0x70;
      }
      puVar7 = (&PTR_DAT_004d02f4)[iVar4 * 3];
    }
    else {
      puVar7 = (&PTR_DAT_004d02f4)[iVar3 * 3];
    }
    if (((iVar3 == 0) || (iVar3 == -1)) && ((&DAT_004f9dc3)[iVar6 * 0x32] != '\x14')) {
      local_12a = 0;
    }
    else {
      local_12a = 0x20;
    }
    local_128 = cVar1;
    if (((&DAT_004f9dc3)[iVar6 * 0x32] == '\x12') && (iVar3 == 0)) {
      local_128 = -1;
    }
    local_124 = param_4;
    local_125 = param_5;
    DrawSTileBuilding(param_2,param_3,puVar7,iVar6,local_12c);
  }
  return;
}

