/*-- Punkte --*/

#strict

Check:
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
      DoScore(i, Local(i+1)-GetPlayerValue(i)-GetScore(i)+GameCall("StartingScore"), 1);
      --j;
    }
  return(1);

AddScore:
  Local(Par(0)+1) += Par(1);
  return(1);

GetPlayerValue:
  var value;
  while(Var(0) = FindObjectOwner(0,Par(0),0,0,0,0,0,0,0,Var(0)))
    value += GetValue(Var(0));
  return(value);

global func DoScore(iPlr, iChange, bInherited) {
  if(bInherited)
    return(inherited(iPlr, iChange));
  var obj;
  obj = FindObject(_SCR);
  if(!obj)
    obj = CreateObject(_SCR);
  obj->AddScore(iPlr, iChange);
  return(1);
}