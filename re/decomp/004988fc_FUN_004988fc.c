// FUN_004988fc @ 004988fc size=149 sig=undefined FUN_004988fc() cc=unknown
// callers: 
// callees: FUN_00488f76,FUN_004a6964,FUN_00489406,FUN_00498826

void FUN_004988fc(void)

{
  int iVar1;
  int iVar2;
  undefined1 local_108 [4];
  char local_104;
  char local_103;
  undefined1 local_102;
  
  iVar2 = 0;
  do {
    FUN_004a6964(local_108,&DAT_0051e1c4);
    local_104 = (char)(iVar2 / 10) + '0';
    local_103 = (char)iVar2 + (char)(iVar2 / 10) * -10 + '0';
    local_102 = 0;
    FUN_00489406(local_108,&DAT_0051e1c9,1);
    iVar2 = iVar2 + 1;
    iVar1 = FUN_00488f76(local_108);
    if (iVar1 == 0) break;
  } while (iVar2 < 100);
  FUN_00498826(local_108,DAT_0051bddc);
  return;
}

