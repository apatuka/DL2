// FUN_00497d40 @ 00497d40 size=250 sig=undefined FUN_00497d40() cc=unknown
// callers: FUN_00497e3a
// callees: FUN_0048fa92,FUN_00497b55,FUN_004979d8,FUN_0048f992,FUN_0048f7f1

void FUN_00497d40(undefined4 param_1,undefined4 param_2,int param_3,undefined2 *param_4,int param_5,
                 int *param_6,undefined2 param_7,short param_8,short param_9)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  undefined2 uVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  undefined2 extraout_var;
  int iVar8;
  
  bVar1 = *(byte *)(param_4 + 4);
  bVar2 = *(byte *)((int)param_4 + 9);
  cVar3 = *(char *)(param_4 + 5);
  uVar4 = *param_4;
  iVar8 = 0;
  bVar5 = false;
  while ((*param_6 != 0 && (!bVar5))) {
    iVar6 = FUN_0048fa92(param_1);
    if (cVar3 == '\0') {
      FUN_0048f992(param_1,param_2,(int)param_8);
    }
    else {
      FUN_00497b55(param_1,param_2,param_8);
    }
    iVar7 = FUN_0048fa92(param_1);
    *param_6 = *param_6 - (iVar7 - iVar6);
    if (param_5 == 0x4d424c49) {
      if ((short)iVar8 < (short)(ushort)bVar1) {
        FUN_004979d8(param_2,param_3,uVar4,CONCAT22(extraout_var,param_9),iVar8,
                     CONCAT22((short)((uint)(iVar7 - iVar6) >> 0x10),param_7));
      }
      iVar8 = iVar8 + 1;
      if ((int)(short)(ushort)bVar1 + (int)(short)(ushort)bVar2 == (int)(short)iVar8) {
        iVar8 = 0;
        param_3 = param_3 + param_9;
      }
    }
    else {
      FUN_0048f7f1(param_2,param_3,(int)param_8);
      param_3 = param_3 + param_9;
    }
    if ((short)iVar8 == 0) {
      bVar5 = true;
    }
  }
  return;
}

