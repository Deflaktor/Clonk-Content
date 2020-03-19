/*-- Neues Objekt --*/

#strict


ControlDig:
  var caller, selectedId;
  caller=Par(0);
  selectedId=Par(1);
  // Lokales Menü mit lokalen Kommandos erzeugen
  CreateMenu(GetID(), caller, this(), C4MN_Extra_None, Format("%s ist leer", GetName()));
  // Menüeinträge erzeugen
  var id;
  var i;
  var i2;
  var obj;
  var count;
  var menu;
  i=0;
  i2=0;
  while(obj=Contents(i)) {
    if(GetID(obj)!=id) {
      id=GetID(obj);
      count=ContentsCount(id);
      AddMenuItem(Format("%s holen", GetName(obj)), "GetItem", id, caller, count, caller);
      i2++;
    }
    i++;
  }
  if(selectedId) {
    if(selectedId<i2)
      caller->SelectMenuItem(selectedId);
    else
      caller->SelectMenuItem(i2-1);
  }
  return(1);

GetItem:
  var i;
  var i2;
  var obj;
  var id;
  i=0;
  i2=0;
  while(obj=Contents(i)) {
    if(GetID(obj)!=id) {
      id=GetID(obj);
      if(id==Par(0)) {
        Collect(obj, Par(1));
        return(ControlDig(Par(1), i2));
      }
      i2++;
    }
    i++;
  }
  return(1);


/*ControlThrow:
  Enter(this(), Contents(0,Par(0)));
  return(1);*/
