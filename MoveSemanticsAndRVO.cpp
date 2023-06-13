#include <vector>
#include <iostream>
class CustomVector
{

	size_t size;
	double* arr_;
public:
	CustomVector(const CustomVector& rhs )
	{
		std::cout << "Copy constructor\n";
		this->size = rhs.size;
		this->arr_ = new double[this->size]{};
		for (size_t i = 0; i < this->size; ++i)
		{
			this->arr_[i] = rhs.arr_[i];
		}
	}
	CustomVector(CustomVector&& rhs)
	{
		std::cout << "Move constructor\n";
		this->size=rhs.size;
		this->arr_ = rhs.arr_;
		// Reseting rvalue 
		rhs.size = 0;
		rhs.arr_ = nullptr;
	}
	CustomVector(size_t size)
	{
		std::cout << "Specialized constructor\n";
		this->size = size;
		this->arr_ = new double[this->size]{};
		for (size_t i = 0; i < this->size; ++i)
		{
			this->arr_[i] = i;
		}
	}
	~CustomVector()
	{
		delete this->arr_;
	}
	void Print()
	{
		for (size_t i = 0; i < this->size; ++i)
		{
			std::cout << this->arr_[i] << '\n';
		}
	}
};
void foo(CustomVector vect)
{

	std::cout << "Inside foo function\n";
}
CustomVector CreateVector(size_t size)
{
	
	return  CustomVector(size); // RVO
}
int main()
{
	// Inside CreateVector, a CustomVector is constructed directly in the memory that will be used for customVector.
	// So there's no need for any copy or move operations, and no "Copy constructor" or "Move constructor" print statement is generated.
	CustomVector customVector = CreateVector(6);
	customVector.Print();
	foo(customVector);
	
}
