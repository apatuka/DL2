// FUN_0049a9e7 @ 0049a9e7 size=125 sig=undefined FUN_0049a9e7() cc=unknown
// callers: FUN_00414f38,FUN_0043e22c,FUN_0049a93f,FUN_0049501c,FUN_004897ea,FUN_004a322d,FUN_00463d00,FUN_0049aa64,FUN_0049497a,CYGame_InitDirectDraw,FUN_004a5f16,FUN_0047fffc,FUN_00458d80,FUN_00459864,FUN_004877c8,FUN_00449f5c,FUN_0043acd4,FUN_00415180,FUN_00422344,FUN_00468a28,DisableMainInterface,DisableMainInterface_c1a4
// callees: 

undefined4 FUN_0049a9e7(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  if (param_1 == (int *)0x0) {
    DAT_0065e570 = 0;
    DAT_0065e574 = 0;
    DAT_0065e578 = 0;
    DAT_0065e57c = 0;
    uVar1 = 0;
  }
  else {
    DAT_0065e570 = param_1[1];
    DAT_0065e574 = *param_1;
    DAT_0065e57c = param_1[2];
    DAT_0065e578 = param_1[3];
    piVar3 = param_1;
    piVar4 = &DAT_0065e580;
    for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar4 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar4 = piVar4 + 1;
    }
    if ((*param_1 < param_1[2]) && (param_1[1] < param_1[3])) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

