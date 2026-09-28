// FUN_0049a13b @ 0049a13b size=422 sig=undefined FUN_0049a13b() cc=unknown
// callers: FUN_0049a317
// callees: FUN_004ae068

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049a13b(double param_1,double param_2,double param_3,double *param_4,double *param_5,
                 double *param_6)

{
  double dVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  float10 fVar5;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined8 local_c;
  
  if (0.5 < param_3) {
    local_c = (param_3 + param_2) - param_3 * param_2;
  }
  else {
    local_c = (double)(((float)param_2 + 1.0) * (float)param_3);
  }
  if (local_c == 0.0) {
    *param_6 = param_3;
    *param_5 = param_3;
    *param_4 = param_3;
  }
  else {
    dVar1 = (double)((float)param_3 * 2.0 - (float)local_c);
    fVar5 = _DAT_0049a30b * (float10)param_1;
    iVar4 = FUN_004ae068();
    dVar2 = local_c * ((local_c - dVar1) / local_c) * ((double)fVar5 - (double)iVar4);
    dVar3 = dVar1 + dVar2;
    dVar2 = local_c - dVar2;
    local_34 = SUB84(dVar3,0);
    uStack_30 = (undefined4)((ulonglong)dVar3 >> 0x20);
    local_3c = SUB84(dVar2,0);
    uStack_38 = (undefined4)((ulonglong)dVar2 >> 0x20);
    switch(iVar4) {
    case 0:
      *(undefined4 *)param_4 = (undefined4)local_c;
      *(undefined4 *)((int)param_4 + 4) = local_c._4_4_;
      *(undefined4 *)param_5 = local_34;
      *(undefined4 *)((int)param_5 + 4) = uStack_30;
      *param_6 = dVar1;
      break;
    case 1:
      *(undefined4 *)param_4 = local_3c;
      *(undefined4 *)((int)param_4 + 4) = uStack_38;
      *(undefined4 *)param_5 = (undefined4)local_c;
      *(undefined4 *)((int)param_5 + 4) = local_c._4_4_;
      *param_6 = dVar1;
      break;
    case 2:
      *param_4 = dVar1;
      *(undefined4 *)param_5 = (undefined4)local_c;
      *(undefined4 *)((int)param_5 + 4) = local_c._4_4_;
      *(undefined4 *)param_6 = local_34;
      *(undefined4 *)((int)param_6 + 4) = uStack_30;
      break;
    case 3:
      *param_4 = dVar1;
      *(undefined4 *)param_5 = local_3c;
      *(undefined4 *)((int)param_5 + 4) = uStack_38;
      *(undefined4 *)param_6 = (undefined4)local_c;
      *(undefined4 *)((int)param_6 + 4) = local_c._4_4_;
      break;
    case 4:
      *(undefined4 *)param_4 = local_34;
      *(undefined4 *)((int)param_4 + 4) = uStack_30;
      *param_5 = dVar1;
      *(undefined4 *)param_6 = (undefined4)local_c;
      *(undefined4 *)((int)param_6 + 4) = local_c._4_4_;
      break;
    case 5:
      *(undefined4 *)param_4 = (undefined4)local_c;
      *(undefined4 *)((int)param_4 + 4) = local_c._4_4_;
      *param_5 = dVar1;
      *(undefined4 *)param_6 = local_3c;
      *(undefined4 *)((int)param_6 + 4) = uStack_38;
    }
  }
  return;
}

