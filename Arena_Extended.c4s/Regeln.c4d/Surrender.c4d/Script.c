/*-- Aufgeben erlaubt --*/

#strict

protected func Activate(iPlr)
{
  CreateMenu(SURR,GetCursor(iPlr), this());
  AddMenuItem("$Aufgeben$", "Surrender", SURR, GetCursor(iPlr), 0, iPlr, " ", 2, 1);
  AddMenuItem("$NichtAufgeben$", "DoNotSurrender", SURR, GetCursor(iPlr), 0, 0, " ", 2, 2);
}

public func Surrender(idDummy, iPlr)
{
  SurrenderPlayer(iPlr);
}

public func DoNotSurrender(idDummy, iPlr)
{
  return(1);
}