#include <vector>
#include "relation.h"


//return y related to x and fill gaps using linear function
double data_set::value(double xs){
	int n;
	if(binary_search(x,xs,n))return y[n];
	else{
		if(eval_type==0){
			if(n<=0)return linear_approximation(x[n],y[n],x[n+1],y[n+1],xs);
			else return linear_approximation(x[0],y[0],x[1],y[1],xs);
		}else return 0;
	}
}

//search for index of given value in array and stores it in n
//return 0 if given value is not contained in array, and array[n]<x
bool binary_search(std::vector<double>&array, double x, int&n){
	int offset=(array.size()-1)/2;
	n=offset;
	while(array[n]!=x){
		if(offset>0){	
			offset/=2;
			if(array[n]<x)n=n+offset+1;
			else n=n-offset-1;
		}else return 0;
	}
	if(x<array[n])n--;
	return 1;
}

//approximate at xs using linear function with given points (x0,y0) (x1,y1)
inline double linear_approximation(double x0,double y0,double x1,double y1,double xs){
	return y0+(y1-y0)/(x1-x0)*(xs-x0);
}

data_set data_set::operator+(data_set const&data_s){
	return data_set();
}


double formula::value(double x){
	double val=0;
	int size=value_sum.size();
	for(int i=0;i<size;i++)val+=value_sum[i](x);
	return val;
}

formula formula::operator+(formula const&form){
	std::vector<double(*)(double)>values;
	values=value_sum;
	std::vector<double(*)(double)>::iterator it;
	it=values.begin();
	values.insert(it,form.value_sum.begin(),form.value_sum.end());
	return formula(values);
}
