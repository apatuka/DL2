// FUN_00471fec @ 00471fec size=41 sig=undefined FUN_00471fec() cc=unknown
// callers: FUN_00472ca0,FUN_004720f4
// callees: 

int FUN_00471fec(int param_1)

{
  return *(int *)(param_1 + 0x56) * 10 + *(int *)(param_1 + 0x4e) * 5 + *(int *)(param_1 + 0x52) * 5
         + *(int *)(param_1 + 0x4a);
}

