// FUN_0044f1e8 @ 0044f1e8 size=273 sig=undefined FUN_0044f1e8() cc=unknown
// callers: FUN_0044f3f0
// callees: FUN_0044e9e4

int FUN_0044f1e8(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = (int)*(char *)(param_2 + 7);
  local_c = 0;
  cVar1 = *(char *)(param_2 + 5);
  if (cVar1 == '\x01') {
    local_10 = 0xc;
    local_14 = 0xd;
  }
  else if (cVar1 == '\x02') {
    local_10 = 3;
    local_14 = 4;
  }
  else if (cVar1 == '\x03') {
    local_10 = 0xf;
    local_14 = 0;
  }
  else {
    local_10 = 0;
  }
  if (local_10 != 0) {
    local_18 = 0;
    do {
      iVar4 = 0;
      do {
        iVar5 = *(char *)(param_2 + 7) + iVar4 + local_18 * -6;
        iVar2 = FUN_0044e9e4(param_1,iVar5 * 0x34 + param_1 + 0x140,local_10,100,1);
        if (local_14 != 0) {
          iVar3 = FUN_0044e9e4(param_1,iVar5 * 0x34 + param_1 + 0x140,local_14,100,1);
          iVar2 = iVar2 + iVar3;
        }
        if (local_c < iVar2) {
          local_c = iVar2;
          local_8 = iVar5;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < 2);
      local_18 = local_18 + 1;
    } while (local_18 < 2);
  }
  return local_8;
}

