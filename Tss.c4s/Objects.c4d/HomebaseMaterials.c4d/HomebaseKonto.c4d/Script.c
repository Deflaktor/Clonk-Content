/*-- HomeBase Account --*/

#strict

Check:
  var iObj=Par(0);
  // Alle Spieler überprüfen
  if(GetOwner()==-1)
    return(SetAction("Idle"));
  var iPlr = GetOwner();
  var id=1, i=0;
  Reset(iObj);
  while(id) {
    var count;
	id = GetHomebaseMaterial(iPlr,0,i,MatCategory());
	count = GetHomebaseMaterial(iPlr, id);
	if(id)
	  SetComponent(id, count, iObj);
	i++;
  }
  return(1);

public func ResetForPlayer() {
  SetOwner(Par(0));
  var iPlr = GetOwner();
  var id=1, i=0;
  while(id) {
    var count;
	id = GetHomebaseMaterial(iPlr,0,i,MatCategory());
	count = GetHomebaseMaterial(iPlr, id);
	if(id)
	  DoHomebaseMaterial(iPlr,id,-count);
	i++;
  }
  id=1;
  i=0;
  while(id) {
    var count;
	id = GetComponent(0, i);
	count = GetComponent(id);
	if(id)
	  DoHomebaseMaterial(iPlr,id,count);
	i++;
  }
}

public func EqualTo(iObj) {
  var i,id,id2;
  id=1;
  while(id||id2) {
    var count;
	id = GetComponent(0, i);
	count = GetComponent(id);
	if(id)
	  if(count!=GetComponent(id, 0, iObj))
        return(false);
    id2 = GetComponent(0, i, iObj);
	count = GetComponent(id2, 0, iObj);
	if(id2)
	  if(count!=GetComponent(id2, 0))
        return(false);
	i++;
  }
  return(true);
}

public func MaxWith(iObj) {
  var i,id,id2;
  id=1;
  while(id||id2) {
    var count,count2;
	id = GetComponent(0, i);
	count = GetComponent(id);
	if(id)
	  SetComponent(id, Max(count, GetComponent(id,0, iObj)));
    id2 = GetComponent(0, i, iObj);
	count = GetComponent(id2, 0, iObj);
	if(id2)
	  SetComponent(id2, Max(count, GetComponent(id2,0, iObj)));
	i++;
  }
  return(true);
}

public func Add(iObj, iTarget) {
  var i,id;
  id=1;
  while(id) {
    var count;
	id = GetComponent(0, i, iObj);
	count = GetComponent(id,0, iObj);
	if(id)
	  SetComponent(id, count + GetComponent(id), iTarget);
	i++;
  }
  return(1);
}

public func Subtract(iObj, iTarget) {
  var i,id;
  id=1;
  while(id) {
    var count;
	id = GetComponent(0, i, iObj);
	count = GetComponent(id,0, iObj);
	if(id)
	  SetComponent(id, GetComponent(id) - count, iTarget);
	i++;
  }
  return(1);
}

public func SubtractInv(iObj, iTarget) {
  var i,id;
  id=1;
  while(id) {
    var count;
	id = GetComponent(0, i, iObj);
	count = GetComponent(id,0, iObj);
	if(id)
	  SetComponent(id, count - GetComponent(id), iTarget);
	i++;
  }
  return(1);
}

public func Set(iObj) {
  var i,id;
  while (id = GetComponent(0, i++))
    SetComponent(id, 0);
  i=0;
  while (id = GetComponent(0, i++, iObj))
    SetComponent(id, GetComponent(id, 0, iObj));
}

public func Reset(iObj) {
  var i,id;
  while (id = GetComponent(0, i++, iObj))
    SetComponent(id, 0, iObj);
}

MatCategory:
  return(C4D_Living()|C4D_Object()|C4D_Vehicle());