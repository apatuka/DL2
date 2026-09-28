// FUN_00499fd7 @ 00499fd7 size=331 sig=undefined FUN_00499fd7() cc=unknown
// callers: FUN_0049a317
// callees: 

void FUN_00499fd7(double param_1,double param_2,double param_3,double *param_4,double *param_5,
                 double *param_6)

{
  double dVar1;
  double dVar2;
  double dVar3;
  
  dVar1 = param_1;
  if (param_1 < param_2) {
    dVar1 = param_2;
  }
  dVar2 = param_3;
  if ((param_3 <= dVar1) && (dVar2 = param_1, param_1 < param_2)) {
    dVar2 = param_2;
  }
  dVar1 = param_2;
  if (param_1 < param_2) {
    dVar1 = param_1;
  }
  dVar3 = param_3;
  if ((dVar1 < param_3) && (dVar3 = param_2, param_1 < param_2)) {
    dVar3 = param_1;
  }
  *param_6 = (dVar2 + dVar3) * 0.5;
  if (dVar2 == dVar3) {
    *(undefined4 *)param_5 = 0;
    *(undefined4 *)((int)param_5 + 4) = 0;
    *(undefined4 *)param_4 = 0;
    *(undefined4 *)((int)param_4 + 4) = 0;
  }
  else {
    dVar1 = dVar2 - dVar3;
    if (0.5 < *param_6) {
      *param_5 = dVar1 / (2.0 - (dVar2 + dVar3));
    }
    else {
      *param_5 = dVar1 / (dVar2 + dVar3);
    }
    if (param_1 == dVar2) {
      *param_4 = (param_2 - param_3) / dVar1;
    }
    else if (param_2 == dVar2) {
      *param_4 = (param_3 - param_1) / dVar1 + 2.0;
    }
    else {
      *param_4 = (param_1 - param_2) / dVar1 + 4.0;
    }
    *param_4 = (double)((float)*param_4 * 60.0);
    if (*param_4 < 0.0) {
      *param_4 = (double)((float)*param_4 + 360.0);
    }
  }
  return;
}

