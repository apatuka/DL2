// FUN_004af0b4 @ 004af0b4 size=116 sig=undefined FUN_004af0b4() cc=unknown
// callers: 
// callees: FUN_004ae314

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004af0b4(float *param_1,double *param_2,uint param_3)

{
  float10 fVar1;
  
  if ((param_3 & 4) == 0) {
    if ((param_3 & 8) == 0) {
      fVar1 = (float10)FUN_004ae314(0,*param_1,param_1[1],*(undefined2 *)(param_1 + 2),
                                    (double)_DAT_00520fe4);
      *(float *)param_2 = (float)fVar1;
    }
    else {
      *(float *)param_2 = *param_1;
      *(float *)((int)param_2 + 4) = param_1[1];
      *(undefined2 *)(param_2 + 1) = *(undefined2 *)(param_1 + 2);
    }
  }
  else {
    fVar1 = (float10)FUN_004ae314(1,*param_1,param_1[1],*(undefined2 *)(param_1 + 2),DAT_00520f1c,
                                  DAT_00520f20);
    *param_2 = (double)fVar1;
  }
  return;
}

