#include <iostream>
#include <vector>

#include "calculator.h"

Calculator::Calculator(int _numb1, int _numb2, int _module){
	numb1 = _numb1;
	numb2 = _numb2;
	module = _module;
}

int Calculator::calculateModule(int _numb, int _module){
	int aux;
	int result;

	aux = _numb / _module;
	result = _numb - (aux * _module);

	if (result < 0){
		aux--;
		result = result + _module;
	}

	return result;
}

int Calculator::addition(){
	int add1 = calculateModule(numb1,module);
	int add2 = calculateModule(numb2,module);
	int aux = add1 + add2;
	int result = calculateModule(aux,module);
	return result;
}

int Calculator::subtraction(){
	int sus1 = calculateModule(numb1,module);
	int sus2 = calculateModule(numb2,module);
	int aux = sus1 - sus2;
	int result = calculateModule(aux,module);
	return result;
}

int Calculator::multiplication(){
	int mul1 = calculateModule(numb1,module);
	int mul2 = calculateModule(numb2,module);
	int aux = mul1 * mul2;
	int result = calculateModule(aux,module);
	return result;
}

std::vector<int> Calculator::euclidesExtended(){
  int a = numb1;
  int b = module;
  int d=0,x=0,y=0;
  int x1=0,x2=0,y1=0,y2=0,q=0,r=0;
  std::vector<int> result;
  if (b ==0){
      d = a;
      x = 1;
      y = 0;
      result.push_back(d);
      result.push_back(x);
      result.push_back(y);
      return result;
  }
  x2 = 1;
  x1 = 0;
  y2 = 0;
  y1 = 1;

  while(b>0){
      q = a/b;
      r = a -(q*b);
      x = x2-(q*x1);
      y = y2-(q*y1);
      a = b;
      b = r;
      x2 = x1;
      x1 = x;
      y2 = y1;
      y1 = y;
  }
  d = a;
  x = x2;
  y = y2;
  result.push_back(d);
  result.push_back(x);
  result.push_back(y);
  return result;

}


int Calculator::inverse(){
  int r1 = module;
  int r2;
  int s1;
  int x = 0, y = 1;

  if (module == 1)
      return 0;

  while (numb1 > 1){
		s1 = numb1 / module;
		r2 = module;
		module = calculateModule(numb1,module);
		numb1 = r2;
		r2 = x;
		x = y - s1 * x;
		y = r2;
  }

  if (y < 0)
      y += r1; 
  return y;
}


