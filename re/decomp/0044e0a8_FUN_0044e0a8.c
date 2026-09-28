// FUN_0044e0a8 @ 0044e0a8 size=201 sig=undefined FUN_0044e0a8() cc=unknown
// callers: FUN_004760d0,FUN_00476084
// callees: FUN_0044ddf4,FUN_00484ebc,FUN_0044bea8,FUN_00484f48,UnitList__Delete,FUN_00484ea4,FUN_00484ee0,FUN_0044b5bc

undefined4 FUN_0044e0a8(int param_1,int param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int *piVar5;
  undefined1 local_64 [4];
  short local_60 [20];
  undefined1 local_38 [4];
  int local_34;
  
  iVar2 = FUN_0044b5bc(param_1,param_3);
  if (iVar2 != 0) {
    iVar3 = FUN_00484ea4(iVar2);
    while (iVar3 != 0) {
      if (param_4 == 0) {
        cVar1 = FUN_00484ee0(iVar2);
        FUN_00484f48(iVar2,local_64);
        FUN_0044ddf4(param_2,(int)cVar1,local_38);
        iVar3 = 1;
        *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + local_34;
        psVar4 = local_60;
        piVar5 = (int *)(param_1 + 0x3e);
        do {
          *piVar5 = *piVar5 + (int)*psVar4;
          iVar3 = iVar3 + 1;
          piVar5 = piVar5 + 1;
          psVar4 = psVar4 + 2;
        } while (iVar3 < 0xb);
        if ((cVar1 == '\x19') || (cVar1 == '\x1f')) {
          *(short *)(param_1 + 0x30) = *(short *)(param_1 + 0x30) + 100;
          FUN_0044bea8(param_1);
        }
        UnitList__Delete(iVar2);
        return 1;
      }
      iVar3 = FUN_00484ebc(iVar2);
      param_4 = param_4 + -1;
    }
  }
  return 0;
}

