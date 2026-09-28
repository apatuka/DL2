// FUN_004a823b @ 004a823b size=28 sig=undefined FUN_004a823b() cc=unknown
// callers: 
// callees: Local_unwind

void FUN_004a823b(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined2 in_FS;
  
  Local_unwind(param_1,0);
  puVar1 = (undefined4 *)segment(in_FS,0);
  *puVar1 = *param_1;
  return;
}

