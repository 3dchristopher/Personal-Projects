//Program to Encrypt text files using RSA algorithm
//Work in progress
//Christopher Little

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstdlib>
using namespace std;

int binary(int x){
  string result;
  result.clear();
  string r;
  while(x!=0) {
    r=(x%2==0 ?"0":"1")+r; x/=2;
  }
  
  stringstream sstm;
  sstm << result << r;
  result = sstm.str();
  //cout << result << endl;

  while(result.size()<8){
    result.insert(0,"0");
  }
  int intResult = stoi (result,nullptr,10);
  //cout << intResult << endl << endl;
  return intResult;
  
}

long long mod_exp (long long n, long long e, long long mod)
{
  if(e == 1)
  {
       return (n % mod);
  }
  else
  {
      if((e % 2) == 1)
      {
          long long temp = mod_exp(n, (e-1)/2, mod);
          return ((n * temp * temp) % mod);
      }
      else
      {
          long long temp = mod_exp(n, e/2, mod);
          return ((temp*temp) % mod); 
      }
  }
}

bool prime(int n){
  bool val = true;
  for(int i=2; i<n; i++){
    if(n%i==0){
      val=false;
      break;
    }
  }
  return val;
};

int euclid(int i, int j){
  while(i!=j){
    if(i>j){
      i=i-j;
    }
    else{
      j=j-i;
    }
  }
  //cout << "Euclid returns: " << i << endl;
  return i;
};

int main(){
  cout << "Please input text to encrypt(at the end of your message, type the word 'done'):" << endl;
  string space = " ";
  vector<string> input;
  vector<long long> binaryInput;
  string s;
  while(cin>>s){
    if(s=="done"){
      break;
    }
    input.push_back(s);
    input.push_back(space);
  }
  for(int i=0; i<input.size();i++){
    for(int j=0; j<input[i].length(); j++){
      int x=input[i][j];
      //cout << x << endl;
      binaryInput.push_back(binary(x));
    }
  }
  
  srand(time(NULL));
  int p = rand() % 10 + 5;
  while(!prime(p)){
    p--;
  }
  int q = rand() % 10 + 5;
  while(!prime(q) || q==p){
    q++;
  }
  cout << "p, q is :" << p << ", " << q << endl;
  int N=p*q;
  int phiN=(p-1)*(q-1);
  vector <int> coprime;
  for(int i=phiN-1; i>1; i--){
    if(euclid(i,N)==1 && euclid(i,phiN)==1){
      coprime.push_back(i);
    }
  }
  int randChoice = rand() % coprime.size();
  int e=coprime[randChoice];
  int dHelp = rand() % 20;
  int z=0;
  int w = 1;
  int dVal = 0;
  while(z<dHelp+1){
    if((e*w)%phiN==1){
      z++;
      dVal=w;
     }
     w++;
  }
  vector<long long> encrypOut;
  for(int k=0; k<binaryInput.size(); k++){
    long long output1 = mod_exp(binaryInput[k]%1000, (long long)e, (long long)N);
    long long output2 = mod_exp(binaryInput[k]/1000, (long long)e, (long long)N);
    encrypOut.push_back(output1);
    encrypOut.push_back(output2);
  }
  
  cout << "Encrypted message is: " << endl;
  string spac = " ";
  for(int i=0; i<encrypOut.size();i++){
    cout << encrypOut[i] << spac;
  }
  
  cout << endl << "Public key pair is : (" << e << "," << N << ")" << endl;
  cout << "Private key pair is : (" << dVal << "," << N << ")" << endl;
  
  return 0;
}






