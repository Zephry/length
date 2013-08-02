#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

void StringSplit(string s,char splitchar,vector<string>& vec)
{
  if(vec.size()>0)	
		vec.clear();
	int length = s.length();
	int start=0;
	for(int i=0;i<length;i++)
	{
		if(s[i] == splitchar && i == 0)		
		{
			start += 1;
		}
		else if(s[i] == splitchar)
		{
			vec.push_back(s.substr(start,i - start));
			start = i+1;
		}
		else if(i == length-1)				
		{
			vec.push_back(s.substr(start,i+1 - start));
		}
	}
}

class changeintometer
{
	vector<string> inputtype;
	vector<double> changerate;
	void learn(vector<string> sentence)
	{
		
		inputtype.push_back(sentence[1]);
		changerate.push_back(stod(sentence[3]));
		if(sentence[1] == "foot")
		{
			inputtype.push_back("feet");
			changerate.push_back(stod(sentence[3]));
		}else
		{
			string stored = sentence[1];
			inputtype.push_back(sentence[1].append("es"));
			changerate.push_back(stod(sentence[3]));
			inputtype.push_back(stored.append("s"));
			changerate.push_back(stod(sentence[3]));
		}
		
	}

	double calculate(vector<string> sentence)
	{
		double result = 0;
		int index = findtype(sentence[1]);
		result += (stod(sentence[0]))*changerate[index];
		for(int i = 0;i < ((sentence.size()-2)/3);i++)
		{
			int position = (3*i)+2;
			if(sentence[position] == "+")
			{
				int index = findtype(sentence[position+2]);
				result += (stod(sentence[position+1]))*changerate[index];
			}else if (sentence[position] == "-")
			{
				int index = findtype(sentence[position+2]);
				result -= (stod(sentence[position+1]))*changerate[index];
			}else if(sentence[position] == "*")
			{
				int index = findtype(sentence[position+2]);
				result *= (stod(sentence[position+1]))*changerate[index];
			}else
			{
				int index = findtype(sentence[position+2]);
				result /= (stod(sentence[position+1]))*changerate[index];

			}
		}
		return result;
	}
	int findtype(string type)
	{
		for(int i =0;i<inputtype.size();i++)
		{
			if (inputtype[i] == type)
			{
				return i;
			}
		}
	}
public:
	

	double ReceiveSentence(string sentence)
	{
		vector<string> SentenceElement;
		StringSplit(sentence,' ',SentenceElement);
		//cout << SentenceElement[1];
		if (SentenceElement.size() == 0)
		{
			return -1;
		}
		else if (SentenceElement.size() < 3)
		{
			double result = calculate(SentenceElement);
			return result;
		}else
		{

			if ((SentenceElement[2]) == "=")
			{
				learn(SentenceElement);
				return -1;
			}else
			{
				double result = calculate(SentenceElement);
				return result;
			}
		}
	}


};


int main()
{	
	ifstream fin;
	char input[100];
	changeintometer Calculaor;
	for(int i = 0;i<100;i++)
	{
		input[i] = NULL;
	}
	ofstream fou;
	fou.open("output.txt");
	fou << "454410517@qq.com" << endl;
	fou << endl;
	
	fin.open("input.txt");
	if(!fin)
	{
		cout<<"File open error!\n";
		return 1;
	}
	double result;
	while (!fin.eof()) 
	{
		fin.getline(input,100);
		string sentence;
		sentence = input;

		result = Calculaor.ReceiveSentence(sentence);

		if (result >= 0)
		{
			//result=((double)((int)((result+0.005)*100)))/100;
			fou << setprecision(2) << fixed <<result << " m" << endl;
		}
	}
	

	fin.close();
	fou.close();
	return 1;
}


