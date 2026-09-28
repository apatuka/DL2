// FUN_004ae090 @ 004ae090 size=45 sig=undefined FUN_004ae090() cc=unknown
// callers: 
// callees: 

float10 FUN_004ae090(longlong *param_1)

{
  if ((longlong)(*param_1 & -0x8000000000000000) == 0) {
    return (float10)*param_1;
  }
  return (float10)CONCAT28(0x403e,*param_1);
}

