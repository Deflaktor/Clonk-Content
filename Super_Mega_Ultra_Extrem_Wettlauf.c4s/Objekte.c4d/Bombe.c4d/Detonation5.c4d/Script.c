#strict

Launch:
  ObjectCall(CreateObject(WP32,0,64),"Launch",Par(0));
  return(RemoveObject());
Remove:
  RemoveObject();
  return(1);