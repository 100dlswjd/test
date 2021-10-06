#include<iostream>

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n)
	{ }
	SoSimple(const SoSimple& copy) : num(copy.num)
	{
		std::cout << "Called SoSimple(const SoSimple& copy)" << std::endl;
	}
	void ShowData()
	{
		std::cout << "num :" << std::endl;
	}
};

void SimpleFuncObj(SoSimple ob)
{
	ob.ShowData();
}

int main(void)
{
	SoSimple obj(7);
	std::cout << " 함수 호출 전 " << std::endl;
	SimpleFuncObj(obj);
	std::cout << " 함수 호출 후" << std::endl;
	return 0;
}