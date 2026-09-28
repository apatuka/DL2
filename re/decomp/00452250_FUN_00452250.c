// FUN_00452250 @ 00452250 size=112 sig=undefined FUN_00452250() cc=unknown
// callers: FUN_004568c8
// callees: FUN_00451b68,memset

void FUN_00452250(undefined1 param_1,int param_2)

{
  int iVar1;
  undefined1 local_60 [6];
  undefined1 local_5a;
  undefined1 local_58;
  undefined1 local_3c;
  undefined1 local_3a;
  undefined2 local_38;
  undefined2 local_34;
  int local_28;
  int local_24;
  int local_20;
  
  memset(local_60,0,0x5c);
  local_58 = param_1;
  if (*(char *)(param_2 + 0x21) == '\0') {
    local_5a = 0x26;
  }
  else {
    local_5a = 0x25;
  }
  local_3c = 0;
  local_3a = 100;
  local_38 = 0;
  local_34 = 0;
  local_20 = param_2;
  local_24 = param_2;
  local_28 = param_2;
  iVar1 = 0;
  do {
    FUN_00451b68(local_60);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x18);
  return;
}

