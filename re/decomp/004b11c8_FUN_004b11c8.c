// FUN_004b11c8 @ 004b11c8 size=69 sig=undefined FUN_004b11c8() cc=unknown
// callers: __assertfail
// callees: FUN_004a69f0,strlen

void FUN_004b11c8(undefined1 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *local_8;
  
  *param_1 = 0;
  local_8 = (int *)&stack0x0000000c;
  while( true ) {
    iVar1 = *local_8;
    if (iVar1 == 0) {
      return;
    }
    iVar2 = strlen(param_1);
    iVar2 = (param_2 - iVar2) + -1;
    if (iVar2 < 1) break;
    FUN_004a69f0(param_1,iVar1,iVar2);
    local_8 = local_8 + 1;
  }
  return;
}

