// FUN_00497fa4 @ 00497fa4 size=498 sig=undefined FUN_00497fa4() cc=unknown
// callers: FUN_004994ed
// callees: FUN_00498ba9,FUN_00497bea,FUN_00497eea,FUN_0048fade,FUN_0048f992,FUN_0048f8e8,FUN_00497c92,FUN_00497e3a,FUN_0048fbbf,FUN_0048f877,FUN_004989cf

undefined4 FUN_00497fa4(undefined4 param_1,undefined4 param_2,code *param_3,undefined4 *param_4)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  undefined1 local_35c [768];
  undefined1 local_5c [64];
  int local_1c;
  uint local_18;
  undefined4 local_14;
  short *local_10;
  int local_c;
  short local_6;
  
  local_14 = 0;
  piVar1 = (int *)FUN_00498ba9(0x1000);
  if (piVar1 == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_0048f8e8(param_1,param_2);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      DAT_0065ee0c = piVar1 + 0x100;
      DAT_0065ee08 = piVar1 + 0x300;
      iVar4 = FUN_0048f992(iVar3,piVar1,0xc);
      if ((iVar4 == 0xc) && (*piVar1 == 0x4d524f46)) {
        local_c = piVar1[2];
        local_10 = (short *)0x0;
        local_6 = 0;
        if ((local_c == 0x4d424c49) || (local_c == 0x204d4250)) {
          do {
            while( true ) {
              if ((local_6 != 0) || (iVar4 = FUN_0048f992(iVar3,piVar1,8), iVar4 != 8))
              goto LAB_0049812d;
              iVar4 = *piVar1;
              if (iVar4 == 0x44484d42) break;
              if (iVar4 == 0x474e5243) {
                FUN_00497eea(piVar1,iVar3,local_5c,&local_14);
              }
              else if (iVar4 == 0x50414d43) {
                FUN_00497bea(piVar1,iVar3,local_35c);
              }
              else if (iVar4 == 0x59444f42) {
                pcVar5 = param_3;
                uVar2 = FUN_0048f877(piVar1[1]);
                FUN_00497e3a(iVar3,local_10,local_c,uVar2,pcVar5);
                local_6 = 1;
              }
              else {
                local_18 = piVar1[1];
                local_18 = FUN_0048f877(local_18);
                if ((local_18 & 1) != 0) {
                  local_18 = local_18 + 1;
                }
                FUN_0048fade(iVar3,local_18,1);
              }
            }
            FUN_00497c92(piVar1,iVar3,&local_10);
          } while ((param_3 == (code *)0x0) ||
                  (local_1c = (*param_3)(0,0,(int)local_10[1],(int)*local_10,2,8), local_1c != 0));
        }
      }
LAB_0049812d:
      FUN_004989cf(piVar1);
      FUN_0048fbbf(iVar3,0);
      if (((local_1c != 0) && (param_4 != (undefined4 *)0x0)) && (param_3 != (code *)0x0)) {
        uVar2 = (*param_3)(4,local_35c,0,0,0,0x100);
        *param_4 = uVar2;
      }
      if ((param_3 == (code *)0x0) || (local_1c == 0)) {
        uVar2 = 0;
      }
      else {
        uVar2 = (*param_3)(1,0,(int)local_10[1],(int)*local_10,1,8);
      }
    }
  }
  return uVar2;
}

