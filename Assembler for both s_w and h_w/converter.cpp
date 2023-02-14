#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

int getRegIndex(string s){
    if(s[2]=='0'){
        return 1;
    }
    else if(s[2]=='1'){
        return 2;
    }
    else if(s[2]=='2'){
        return 3;
    }
    else if(s[2]=='3'){
        return 4;
    }
    else if(s[2]=='4'){
        return 5;
    }
    else if(s[1]=='s'&&s[2]=='p'){
        return 6;
    }
    else if(s[1]=='z'&&s[2]=='e'&&s[3]=='r'&&s[4]=='o'){
        return 0;
    }
}
void decToBinary(unsigned short int n)
{
    // array to store binary number
    int binaryNum[32];
  
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
  
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        printf("%d", binaryNum[j]);
    cout<<endl;
}

// function to convert decimal to hexadecimal
string decToHexa(unsigned short int n)
{
	// ans string to store hexadecimal number
	string ans = "";

	while (n != 0) {
		// remainder variable to store remainder
		int rem = 0;
		
		// ch variable to store each character
		char ch;
		// storing remainder in rem variable.
		rem = n % 16;

		// check if temp < 10
		if (rem < 10) {
			ch = rem + 48;
		}
		else {
			ch = rem + 55;
		}
		
		// updating the ans string with the character variable
		ans += ch;
		n = n / 16;
	}
	
	// reversing the ans string to get the final result
	int i = 0, j = ans.size() - 1;
	while(i <= j)
	{
	    swap(ans[i], ans[j]);
        i++;
        j--;
	}
	return ans;
}

int main(){

  char text[200];
  string s,temp;
  fstream readFile,writeFile;
  readFile.open ("assembly.txt",ios::in );
  writeFile.open ("hex.hex",ios::out );
  int size=0;
  unsigned short int res,tempRes;
  int reg1,reg2,dst,amount,start;
  writeFile<<"v2.0 raw"<<endl;
  while(1){ 
    temp="";
    s="";
    res=0;
    reg1=0;
    reg2=0;
    dst=0;
    amount=0;
    start=0;
    getline(readFile,s);
    if(s=="")break;

    stringstream ss(s);
    string word;
    
    getline(ss, word, ' ');
    for(int i=word.size();i<s.size();i++){
        temp+=s[i];
    }
    temp =removeSpaces(temp);
    cout<<temp<<endl;
    if(word == "add"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg2=getRegIndex(word2);
        
        res |=0b0001000000000000;
        res |=reg1<<8;
        res |=reg2<<4;
        res |=dst;
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="addi"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b0010000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="sub"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg2=getRegIndex(word2);
        
        res |=0b0110000000000000;
        res |=reg1<<8;
        res |=reg2<<4;
        res |=dst;
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="subi"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b0101000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="and"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg2=getRegIndex(word2);
        
        res |=0b1011000000000000;
        res |=reg1<<8;
        res |=reg2<<4;
        res |=dst;
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="andi"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b1101000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="or"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg2=getRegIndex(word2);
        
        res |=0b1110000000000000;
        res |=reg1<<8;
        res |=reg2<<4;
        res |=dst;
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="ori"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b0111000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="nor"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg2=getRegIndex(word2);
        
        res |=0b0011000000000000;
        res |=reg1<<8;
        res |=reg2<<4;
        res |=dst;
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="sll"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b1001000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="srl"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b1010000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="lw"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');

        stringstream ss3(word2);
        string word3;

        getline(ss3, word3, '(');
        amount=stoi(word3);
        getline(ss3, word3, '(');

        stringstream ss4(word3);
        string word4;
        getline(ss4, word4, ')');
        reg1=getRegIndex(word4);

        res |=0b0000000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="sw"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');

        stringstream ss3(word2);
        string word3;

        getline(ss3, word3, '(');
        amount=stoi(word3);
        getline(ss3, word3, '(');

        stringstream ss4(word3);
        string word4;
        getline(ss4, word4, ')');
        reg1=getRegIndex(word4);

        res |=0b1111000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="beq"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b1000000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="bneq"){
        stringstream ss2(temp);
        string word2;
        
        getline(ss2, word2, ',');
        dst=getRegIndex(word2);
        getline(ss2, word2, ',');
        reg1=getRegIndex(word2);
        getline(ss2, word2, ',');
        amount=stoi(word2);
        
        res |=0b0100000000000000;
        res |=(0b0000111100000000)&(reg1<<8);
        res |=(0b0000000011110000)&(dst<<4);
        res |=(0b0000000000001111)&(amount);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
    else if(word=="j"){
        res |=0b1100000000000000;
        amount=stoi(temp);
        res |=(0b0000000011110000)&(amount<<4);
        decToBinary(res);
        writeFile<<decToHexa(res)<<" ";
    }
  }
  readFile.close();
  writeFile.close();
  return 0;
}