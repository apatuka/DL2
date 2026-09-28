// FUN_00414bd8 @ 00414bd8 size=506 sig=undefined FUN_00414bd8() cc=unknown
// callers: 
// callees: FUN_004935fc,FUN_00483c3c,FUN_004a43da,FUN_00414b64,FUN_0049a8ed,FUN_0049f09b,FUN_0049a93f,FUN_0049b3c9,FUN_0049aa64

undefined4 FUN_00414bd8(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18 [3];
  int local_c;
  int local_8;
  
  if (param_2 == 8) {
    DAT_0053328c = 0;
  }
  else if (param_2 == 3) {
    FUN_0049f09b(param_1,&local_28);
    iVar7 = local_1c - local_24;
    iVar6 = local_20 - local_28;
    FUN_0049a8ed();
    iVar1 = FUN_0049aa64(&local_28);
    if (iVar1 != 0) {
      FUN_004935fc(local_28,local_24,local_28 + iVar6,local_24 + iVar7,0);
      iVar1 = (int)(char)PTR_DAT_004d5988[0x3e];
      if (0 < iVar1) {
        FUN_00414b64();
        iVar2 = FUN_00483c3c(PTR_DAT_004d5988,&DAT_004fbbac + iVar1 * 0x19);
        local_8 = DAT_00533224;
        local_c = ((short)(&DAT_004fbbb2)[iVar1 * 0x19 + (int)(char)*PTR_DAT_004d5988] * 100) /
                  iVar2;
        local_18[2] = (DAT_00533224 * 100) / iVar2 + local_c;
        local_18[1] = 100;
        if (local_c < 0x65) {
          piVar4 = &local_c;
        }
        else {
          piVar4 = local_18 + 1;
        }
        local_c = *piVar4;
        local_18[0] = 100;
        if (local_18[2] < 0x65) {
          piVar5 = local_18 + 2;
        }
        else {
          piVar5 = local_18;
        }
        local_18[2] = *piVar5;
        iVar1 = (local_18[2] * iVar6) / 100;
        iVar6 = (*piVar4 * iVar6) / 100;
        if (local_18[2] == 100) {
          uVar3 = FUN_0049b3c9(DAT_0058df44,0xda);
          FUN_004935fc(local_28,local_24,iVar1 + local_28,iVar7 + local_24,uVar3);
        }
        else {
          if (iVar1 != 0) {
            uVar3 = FUN_0049b3c9(DAT_0058df44,0xd);
            FUN_004935fc(local_28,local_24,iVar1 + local_28,local_24 + iVar7,uVar3);
          }
          if (iVar6 != 0) {
            uVar3 = FUN_0049b3c9(DAT_0058df44,0xdb);
            FUN_004935fc(local_28,local_24,iVar6 + local_28,iVar7 + local_24,uVar3);
          }
        }
      }
    }
    FUN_0049a93f();
    return 1;
  }
  uVar3 = FUN_004a43da(param_1,param_2,param_3,param_4);
  return uVar3;
}

