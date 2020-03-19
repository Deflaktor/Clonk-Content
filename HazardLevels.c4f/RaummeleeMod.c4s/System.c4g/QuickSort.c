/*-- Quicksort --*/

#strict

global func QuicksortAdd(object arrayObject, int index, element) {
  arrayObject->Local(0)++;
  arrayObject->Local(index+1)=element;
}

global func Quicksort(object arrayObject, object callObject, string callEvaluationFunction) {
  QuicksortRecursive(arrayObject, 0, QuicksortSize(arrayObject)-1, callObject, callEvaluationFunction);
}
 
global func QuicksortResult(object arrayObject, int index) {
  return(QuicksortGet(arrayObject, index));
}

// Dont use any of these below

global func QuicksortFunction(object obj, string f, element) {
  return(ObjectCall(obj, f, element));
}

global func QuicksortGet(object arrayObject, int index) {
  return(arrayObject->Local(index+1));
}

global func QuicksortSwap(object arrayObject, int index1, int index2) {
  var temp = arrayObject->Local(index1+1);
  arrayObject->Local(index1+1) = arrayObject->Local(index2+1);
  arrayObject->Local(index2+1) = temp;
}

global func QuicksortSize(object arrayObject) {
  return(arrayObject->Local(0));
}

// Quicksort body

global func QuicksortPartition(object a, int left, int right, int pivotIndex, object obj, string f) {
  // get the pivot value
  var pivotValue = QuicksortFunction(obj, f, QuicksortGet(a, pivotIndex));
  // move pivot to end
  QuicksortSwap(a, pivotIndex, right);
  var storeIndex = left;
  for(var i=left; i<right; i++) {
    if(QuicksortFunction(obj, f, QuicksortGet(a, i)) <= pivotValue) {
	  QuicksortSwap(a, i, storeIndex);
	  storeIndex++;
	}
  }
  QuicksortSwap(a, storeIndex, right);
  return(storeIndex);
}

global func QuicksortRecursive(object a, int left, int right, object obj, string f) {
  if(left<right) {
    var pivotIndex = RandomX(left, right);
	var pivotNewIndex = QuicksortPartition(a, left, right, pivotIndex, obj, f);
	QuicksortRecursive(a, left, pivotNewIndex - 1, obj, f);
	QuicksortRecursive(a, pivotNewIndex + 1, right, obj, f);
  }
}