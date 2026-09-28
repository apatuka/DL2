// FUN_004ae0c0 @ 004ae0c0 size=33 sig=undefined FUN_004ae0c0() cc=unknown
// callers: FUN_004af8f4,FUN_004af624
// callees: 

void FUN_004ae0c0(longlong *param_1,float10 *param_2)

{
  if (*(short *)((int)param_2 + 8) != 0x403e) {
    *param_1 = (longlong)ROUND(*param_2);
    return;
  }
  *(undefined4 *)param_1 = *(undefined4 *)param_2;
  *(undefined4 *)((int)param_1 + 4) = *(undefined4 *)((int)param_2 + 4);
  return;
}

