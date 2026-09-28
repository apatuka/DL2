// FUN_004ae230 @ 004ae230 size=58 sig=undefined FUN_004ae230() cc=unknown
// callers: FUN_00417434,FUN_00437a3c
// callees: FUN_004afbe4

float10 FUN_004ae230(double param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)param_1;
  if (((ulonglong)param_1 & 0x7fff000000000000) != 0) {
    if ((longlong)param_1 < 0) {
      fVar1 = (float10)FUN_004afbe4(1,&DAT_00520e3c,&param_1,0,DAT_00520e34,DAT_00520e38);
    }
    else {
      fVar1 = SQRT(fVar1);
    }
  }
  return fVar1;
}

