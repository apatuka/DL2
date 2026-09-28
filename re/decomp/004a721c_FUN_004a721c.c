// FUN_004a721c @ 004a721c size=31 sig=undefined FUN_004a721c() cc=unknown
// callers: 
// callees: 

undefined4 FUN_004a721c(int param_1,int param_2)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)
          (*(int *)((*(int *)(param_1 + param_2) - *(int *)(*(int *)(param_1 + param_2) + -4)) +
                   -0xc) + 0x20);
}

