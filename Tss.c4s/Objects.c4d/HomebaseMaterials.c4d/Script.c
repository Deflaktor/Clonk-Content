/*-- HomeBase Remember --*/

#strict


public func InitializePlayer(iPlr)
{
  // Neuer Spieler, altes Konto
  var obj;
  while(obj=FindObject(HBK_, 0,0,0,0, 0, 0 ,0,0, obj))
    if(Local(0,obj)==iPlr) {
	  obj->ResetForPlayer(iPlr);
	  if(!FindObject(_TAC))
	    obj->SetAction("Check");
	  return(1);
	}
  // Neuer Spieler, neues Konto
  obj=CreateObject(HBK_, 0,0, iPlr);
  SetLocal(0,iPlr,obj);
  if(!FindObject(_TAC))
    obj->SetAction("Check");
}

protected func Activate(caller) {
  MessageWindow(GetDesc(), caller);
  return(1);
}
