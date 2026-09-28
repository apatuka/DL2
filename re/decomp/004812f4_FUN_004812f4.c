// FUN_004812f4 @ 004812f4 size=423 sig=undefined FUN_004812f4() cc=unknown
// callers: FUN_00449d54,FUN_00449870
// callees: FUN_004152ec,FUN_0048d32c,FUN_00463da8,FUN_004152e0,FUN_00465df8,FUN_00480d78,FUN_0048d2e7,FUN_004810cc,FUN_0048125c

/* WARNING: Removing unreachable block (ram,0x00481384) */
/* WARNING: Heritage AFTER dead removal. Example location: s0xffffffec : 0x0048138c */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_004812f4(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int local_28;
  int local_24 [3];
  undefined4 local_18;
  int local_14;
  int local_10 [3];
  
  if ((short)(&DAT_005a0552)[param_3 * 200 + param_2 * 5] == -1) {
    DAT_00657de0 = (undefined *)0x0;
  }
  else {
    DAT_00657de0 = &DAT_005a43d0 + (short)(&DAT_005a0552)[param_3 * 200 + param_2 * 5] * 0xadc;
  }
  FUN_004152e0();
  FUN_00465df8(2);
  local_10[2] = 0x280;
  local_10[1] = 0x140;
  local_10[0] = DAT_00583e0c;
  local_14 = 0x140;
  if (DAT_00583e0c < 0x280) {
    piVar2 = local_10 + 2;
  }
  else {
    piVar2 = local_10;
  }
  iVar1 = *piVar2;
  local_18 = 0x140;
  FUN_0048d2e7(DAT_004dcc1c);
  FUN_0048125c(param_2,param_3,iVar1,local_18);
  DAT_004c5b64 = 0;
  DAT_004c5b60 = 0;
  DAT_004c5460 = local_10[0];
  DAT_004c5464 = local_14;
  DAT_004c5458 = 0;
  DAT_004c545c = 0;
  local_24[2] = DAT_00657dd8 - local_10[0] >> 1;
  local_24[1] = 0;
  if (local_24[2] < 0) {
    piVar2 = local_24 + 1;
  }
  else {
    piVar2 = local_24 + 2;
  }
  DAT_004dcc24 = *piVar2;
  local_24[0] = DAT_00657ddc - local_14 >> 1;
  local_28 = 0;
  if (local_24[0] < 0) {
    piVar2 = &local_28;
  }
  else {
    piVar2 = local_24;
  }
  DAT_004dcc28 = *piVar2;
  FUN_004810cc(DAT_00657de0);
  DAT_005644d8 = local_10[0];
  DAT_005644dc = local_14;
  DAT_005644e4 = DAT_00657dd8 - local_10[0];
  DAT_005644e0 = DAT_00657ddc - local_14;
  FUN_004152ec();
  FUN_00480d78();
  FUN_0048d32c();
  FUN_00463da8(0);
  FUN_00463da8(1);
  return;
}

