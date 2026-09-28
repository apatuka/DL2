// FUN_00458bb0 @ 00458bb0 size=18 sig=undefined FUN_00458bb0() cc=unknown
// callers: CreateGamePalette,FUN_00464f80,ShutdownGame,FUN_00464a3c,CreateGamePalette2,FUN_00464cbc
// callees: DeleteObject

void FUN_00458bb0(HGDIOBJ param_1)

{
  DeleteObject(param_1);
  return;
}

