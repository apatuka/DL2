// FUN_004045d0 @ 004045d0 size=219 sig=undefined FUN_004045d0() cc=unknown
// callers: FUN_004046ac
// callees: FUN_0044f3f0,FUN_004765a8,FUN_0046bdfc,FUN_0047654c

undefined4 FUN_004045d0(int param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 local_8;
  
  FUN_0047654c(param_1,param_2);
  if (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_1 * 0x2d8] * 2) == 0) {
    local_8 = 1;
  }
  else {
    local_8 = 1;
    piVar2 = &DAT_00521bb4;
    do {
      iVar1 = *piVar2;
      FUN_0044f3f0(iVar1,0,1);
      FUN_0046bdfc(iVar1);
      if (DAT_0058f178 < 100) {
        FUN_004765a8(param_1,(int)*(short *)(iVar1 + 0x1a),0xffffffff);
      }
      else if (99 < *(int *)(&DAT_004d57f0 + (char)(&DAT_0059f16b)[param_1 * 0x2d8] * 4) +
                    DAT_0058f178) {
        FUN_004765a8(param_1,(int)*(short *)(iVar1 + 0x1a),1);
      }
      FUN_0046bdfc(iVar1);
      if (DAT_0058f178 < 100) {
        local_8 = 0;
      }
      piVar2 = (int *)piVar2[1];
    } while (piVar2 != &DAT_00521bb4);
  }
  return local_8;
}

