int returns[3]; //global variables have to be declared here?
// also investigate "extern int returns[3]
void try_1(){
  int a = 1;
  int b = 2;
  int c = 3;

  returns[0] = a;
  returns[1] = b;
  returns[2] = c;
}

int try_2(int string){
  int a = 10;
  int b = 20;
  int c = 30;
  int ans;
  
  if(string == 0){
    ans = a;
  }
  else if(string == 1){
    ans = b;
  }
  else if(string == 2){
    ans = c;
  }
  else{
    ans = 101010;
  }

  return ans;
}
