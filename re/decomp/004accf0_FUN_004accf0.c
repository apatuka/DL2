// FUN_004accf0 @ 004accf0 size=76 sig=undefined FUN_004accf0() cc=unknown
// callers: FUN_004ac1c8,FUN_004acdd4,FUN_004acd5c,FUN_004ace78,FUN_004acfa4,FUN_004acd70,FUN_004ac2cc,FUN_004ac4cc,FUN_004acf20
// callees: FUN_004acce4,FUN_004b12c4

undefined4 FUN_004accf0(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  
  if (param_1 < 0) {
    param_1 = -param_1;
    if (param_1 < DAT_00520338) {
      puVar2 = (undefined4 *)FUN_004acce4();
      *puVar2 = 0xffffffff;
      goto LAB_004acd2f;
    }
LAB_004acd03:
    param_1 = 1;
  }
  else if (0x12a < param_1) goto LAB_004acd03;
  piVar1 = (int *)FUN_004acce4();
  *piVar1 = param_1;
  param_1 = (int)(char)(&DAT_0052089c)[param_1];
LAB_004acd2f:
  piVar1 = (int *)FUN_004b12c4();
  *piVar1 = param_1;
  return 0xffffffff;
}

