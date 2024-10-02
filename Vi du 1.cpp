#include<iostream>
#include<string>
using namespace std;
class Hocsinh
{
	private:
		string Ten;
		int Tuoi;
		float GPA;
	public:
		Hocsinh(string n,int a,float g) : Ten(n), Tuoi(a), GPA(g){}
	string getTen() const { return Ten;}
	int getTuoi()const {return Tuoi;}
	float getGPA()const {return GPA;}
	
	void setTen(string n) {Ten = n;}
	void setTuoi(int a) {Tuoi=a;}
	void setGPA(float g) {GPA=g;}
	
	void Thongtin() const{
	cout<<"Ten: "<<Ten<<endl;
	cout<<"Tuoi: "<<Tuoi<<endl;
	cout<<"GPA: "<<GPA<<endl;
	}
};
int main()
{
	Hocsinh s1("Vu Quang Minh", 30, 4.0);
	cout<<"Thong tin sinh vien: "<<endl;
	s1.Thongtin();
	s1.setGPA(3.8);
	cout<<"\n Thong tin sau khi cap nhat GPA: "<<endl;
	s1.Thongtin();
	return 0;
}
