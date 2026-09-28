// FUN_004a4ffe @ 004a4ffe size=491 sig=undefined FUN_004a4ffe() cc=unknown
// callers: FUN_004994ed
// callees: FUN_00498ba9,FUN_0048f8e8,FUN_004989cf,FUN_004a4c92,FUN_004a4e8e,FUN_0048fbbf,FUN_004a4c60

undefined4 FUN_004a4ffe(undefined4 param_1,undefined4 param_2,code *param_3,undefined4 *param_4)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  short unaff_DI;
  byte local_a4c [2];
  undefined1 local_a4a;
  undefined2 local_a47;
  short local_a40;
  short local_a3e;
  byte local_a3c;
  int local_10;
  int local_c;
  ushort local_8;
  short local_6;
  
  iVar3 = FUN_0048f8e8(param_1,param_2);
  if (iVar3 != 0) {
    sVar1 = FUN_004a4c92(local_a4c,iVar3);
    if (sVar1 == 0) {
      local_8 = local_a40 * (short)((int)(local_a3c + 7) >> 3);
      uVar2 = local_8;
      if (local_8 < 0x800) {
        uVar2 = 0x800;
      }
      local_c = FUN_00498ba9(uVar2);
      if (local_c != 0) {
        if ((param_3 != (code *)0x0) &&
           (local_10 = (*param_3)(0,0,local_a3e,local_a40,1,local_a3c), local_10 == 0)) {
          return 0;
        }
        local_6 = local_a3e;
        if ((param_3 != (code *)0x0) && (param_4 != (undefined4 *)0x0)) {
          uVar4 = (*param_3)(4,(uint)local_a4c[0] + local_c,0,0,0,local_a47);
          *param_4 = uVar4;
          local_6 = local_a3e;
        }
        while (local_6 = local_6 + -1, -1 < local_6) {
          unaff_DI = FUN_004a4e8e(local_c,local_a40,(int)(local_a3c + 7) >> 3,iVar3,local_a4a);
          if (unaff_DI < 0) {
            FUN_0048fbbf(iVar3,0);
            if (param_3 != (code *)0x0) {
              (*param_3)(2,0,local_a3e,(int)unaff_DI,1,local_a3c);
            }
            return 0;
          }
          if (param_3 != (code *)0x0) {
            (*param_3)(3,local_c,(int)local_6,(int)unaff_DI,1,local_a3c);
          }
        }
        FUN_004a4c60(local_a4c);
        FUN_0048fbbf(iVar3,0);
        FUN_004989cf(local_c);
        if (param_3 != (code *)0x0) {
          uVar4 = (*param_3)(1,0,local_a3e,(int)unaff_DI,1,local_a3c);
          return uVar4;
        }
      }
      FUN_004a4c60(local_a4c);
      FUN_0048fbbf(iVar3,0);
    }
    else {
      FUN_0048fbbf(iVar3,0);
    }
  }
  return 0;
}

