// FUN_004a9b0c @ 004a9b0c size=21 sig=undefined FUN_004a9b0c() cc=unknown
// callers: FUN_004a73d4
// callees: 

void FUN_004a9b0c(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined2 in_FS;
  
  puVar1 = (undefined4 *)segment(in_FS,0);
  *param_1 = *puVar1;
  puVar1 = (undefined4 *)segment(in_FS,0);
  *puVar1 = param_1;
  return;
}

