// FUN_00440f64 @ 00440f64 size=408 sig=undefined FUN_00440f64() cc=unknown
// callers: FUN_00449870,FUN_0045e274
// callees: 

/* WARNING: Removing unreachable block (ram,0x00440fcc) */
/* WARNING: Removing unreachable block (ram,0x0044100a) */
/* WARNING: Heritage AFTER dead removal. Example location: s0xfffffff0 : 0x00441014 */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_00440f64(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_24;
  int local_20;
  int local_1c [3];
  undefined4 local_10;
  
  piVar4 = &local_24;
  local_24 = ((int)DAT_004d5b1a + (int)DAT_004d5b1b) * 0x20;
  local_20 = local_24 >> 1;
  local_1c[0] = DAT_00583e0c;
  local_1c[1] = 0x140;
  DAT_004c5b64 = 0;
  DAT_004c5b60 = 0;
  iVar2 = DAT_00583e0c;
  if (DAT_00583e0c < 0) {
    iVar2 = DAT_00583e0c + 0x1f;
  }
  local_1c[2] = (iVar2 >> 5) << 5;
  if (DAT_00583e0c < local_1c[2]) {
    piVar3 = local_1c;
  }
  else {
    piVar3 = local_1c + 2;
  }
  local_1c[0] = *piVar3;
  local_10 = 0x140;
  local_1c[1] = 0x140;
  if (*piVar3 <= local_24) {
    piVar4 = local_1c;
  }
  iVar1 = *piVar4;
  DAT_00559df8 = iVar1;
  if (local_20 < 0x140) {
    piVar4 = &local_20;
  }
  else {
    piVar4 = local_1c + 1;
  }
  DAT_00559dfc = *piVar4;
  DAT_004c5460 = iVar1;
  DAT_004c5464 = DAT_00559dfc;
  DAT_004c5458 = DAT_00583e0c - iVar1 >> 1;
  if (DAT_004c5458 < 0) {
    DAT_004c5458 = DAT_004c5458 + (uint)((DAT_00583e0c - iVar1 & 1U) != 0);
  }
  DAT_004c545c = (int)(0x140U - DAT_00559dfc) >> 1;
  if (DAT_004c545c < 0) {
    DAT_004c545c = DAT_004c545c + (uint)((0x140U - DAT_00559dfc & 1) != 0);
  }
  DAT_004c5450 = 1;
  DAT_00559dd8 = -(int)DAT_004d5b1b;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x1f;
  }
  DAT_00559ddc = (int)DAT_004d5b1a - (iVar1 >> 5);
  DAT_00559de0 = 0;
  local_20 = local_20 - DAT_00559dfc;
  if (local_20 < 0) {
    local_20 = local_20 + 0x1f;
  }
  DAT_00559de4 = local_20 >> 5;
  DAT_005644d8 = iVar2 >> 5;
  DAT_005644dc = 10;
  DAT_005644e4 = DAT_00559ddc;
  DAT_005644e0 = local_20 >> 5;
  return;
}

