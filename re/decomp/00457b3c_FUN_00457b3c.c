// FUN_00457b3c @ 00457b3c size=170 sig=undefined FUN_00457b3c() cc=unknown
// callers: FUN_00472e04,RunAITurns
// callees: SendMessageA,FUN_00457a58,FUN_0046ca40,PostMessageA

void FUN_00457b3c(void)

{
  uint uVar1;
  int iVar2;
  
  if ((0x13 < DAT_0059f154) && (uVar1 = FUN_0046ca40(), (uVar1 & 3) == 0)) {
    iVar2 = FUN_00457a58(1);
    if ((((iVar2 == 2) &&
         (((iVar2 = FUN_00457a58(3), iVar2 == 10 && (iVar2 = FUN_00457a58(2), iVar2 == 2)) &&
          (iVar2 = FUN_00457a58(5), iVar2 == 3)))) &&
        (((iVar2 = FUN_00457a58(4), iVar2 == 2 && (iVar2 = FUN_00457a58(6), iVar2 == 0)) &&
         (s____DEADLOCK_TXT_004d02d0[2] == '\\')))) && (DAT_004d02e2 == '\\')) {
      return;
    }
    PTR_FUN_004d02b8 = FUN_00457ac0;
    SendMessageA(DAT_0058f1a4,0x7b0,0,0);
    PostMessageA(DAT_0058f1a4,0x12,0,0);
  }
  return;
}

