// FUN_004ae034 @ 004ae034 size=28 sig=undefined FUN_004ae034() cc=unknown
// callers: Timer_Init,WaveOut_Init
// callees: FUN_004ae204

float10 FUN_004ae034(double param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)param_1;
  if ((ushort)(param_1._6_2_ * 2) < 0x8681) {
    fVar1 = (float10)FUN_004ae204();
  }
  return fVar1;
}

