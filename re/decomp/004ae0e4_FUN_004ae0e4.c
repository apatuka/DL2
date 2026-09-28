// FUN_004ae0e4 @ 004ae0e4 size=17 sig=undefined FUN_004ae0e4() cc=unknown
// callers: FUN_004af8f4,FUN_004af624
// callees: 

ushort FUN_004ae0e4(float10 *param_1)

{
  float10 fVar1;
  float10 fVar2;
  
  fVar1 = *param_1;
  fVar2 = (float10)0;
  return (ushort)NAN(fVar1) << 8 | (ushort)(fVar1 < fVar2) << 9 | (ushort)(fVar1 != fVar2) << 10 |
         (ushort)(fVar1 == fVar2) << 0xe;
}

