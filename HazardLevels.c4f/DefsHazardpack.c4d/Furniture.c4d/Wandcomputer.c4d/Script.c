#strict

Initialize:
  if(!Par(0)) SetAction(Format("Stand%d",Sum(1,Random(4))));
  if((!FindObject(SO3V,-100,-100,200,200,"Comp1"))&&(!FindObject(SO3V,-100,-100,200,200,"Comp2"))&&(!FindObject(SO3V,-100,-100,200,200,"Comp3"))&&(!FindObject(SO3V,-100,-100,200,200,"Comp4"))) ObjectSetAction(CreateObject(SO3V),Format("Comp%d",Random(4)+1));
  return(1);
