// FUN_0045ab1c @ 0045ab1c size=355 sig=undefined FUN_0045ab1c() cc=unknown
// callers: FUN_0045e274,FUN_00449870
// callees: 

/* WARNING: Removing unreachable block (ram,0x0045ab75) */
/* WARNING: Removing unreachable block (ram,0x0045abaa) */
/* WARNING: Heritage AFTER dead removal. Example location: s0xffffffe4 : 0x0045abb2 */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_0045ab1c(void)

{
  int iVar1;
  int *piVar2;
  int local_18 [3];
  int local_c;
  int local_8;
  
  local_8 = (int)DAT_004d5b1a << 5;
  local_c = (int)DAT_004d5b1b << 5;
  local_18[2] = DAT_00583e0c;
  local_18[1] = 0x140;
  DAT_004c5b64 = 0;
  DAT_004c5b60 = 0;
  iVar1 = DAT_00583e0c;
  if (DAT_00583e0c < 0) {
    iVar1 = DAT_00583e0c + 0x1f;
  }
  DAT_005644d8 = iVar1 >> 5;
  local_18[0] = DAT_005644d8 << 5;
  if (DAT_00583e0c < DAT_005644d8 << 5) {
    piVar2 = local_18 + 2;
  }
  else {
    piVar2 = local_18;
  }
  local_18[2] = *piVar2;
  local_18[1] = 0x140;
  if (local_18[2] < local_8) {
    piVar2 = local_18 + 2;
  }
  else {
    piVar2 = &local_8;
  }
  iVar1 = *piVar2;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x1f;
  }
  DAT_005644c4 = iVar1 >> 5;
  if (local_c < 0x141) {
    piVar2 = &local_c;
  }
  else {
    piVar2 = local_18 + 1;
  }
  iVar1 = *piVar2;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x1f;
  }
  DAT_005644c8 = iVar1 >> 5;
  if (local_8 < local_18[2]) {
    piVar2 = &local_8;
  }
  else {
    piVar2 = local_18 + 2;
  }
  DAT_004c5460 = *piVar2;
  if (local_c < 0x140) {
    piVar2 = &local_c;
  }
  else {
    piVar2 = local_18 + 1;
  }
  DAT_004c5464 = *piVar2;
  DAT_004c5458 = 0;
  DAT_004c545c = 0;
  DAT_004c5450 = 1;
  DAT_005644dc = 10;
  DAT_005644e4 = DAT_004d5b1a - DAT_005644d8;
  DAT_005644e0 = DAT_004d5b1b + -10;
  return;
}

