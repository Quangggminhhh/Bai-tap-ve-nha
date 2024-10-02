#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Quanlynhanvien {
protected:
    int id;
    string Ten;
    int Tuoi;
    double Luong;

public:
    Quanlynhanvien(int id, string Ten, int Tuoi, double Luong)
        : id(id), Ten(Ten), Tuoi(Tuoi), Luong(Luong) {}

    virtual void Hienthithongtin() const {
        cout << "ID: " << id << ", Ten: " << Ten
             << ", Tuoi: " << Tuoi << ", Luong: " << Luong << endl;
    }

    virtual double Tinhluong() const {
        return Luong;
    }

    void Tangluong(double amount) {
        Luong += amount;
    }

    virtual ~Quanlynhanvien() {}
};

class Quanly : public Quanlynhanvien {
private:
    int Sonhanvien;

public:
    Quanly(int id, string Ten, int Tuoi, double Luong, int teamSize)
        : Quanlynhanvien(id, Ten, Tuoi, Luong), Sonhanvien(Sonhanvien) {}

    void Hienthithongtin() const override {
        Quanlynhanvien::Hienthithongtin();
        cout << "So nhan vien quan ly: " << Sonhanvien << endl;
    }

    double Tinhluong() const override {
        return Quanlynhanvien::Tinhluong() + (Sonhanvien * 1000);
    }
};

class Congty {
private:
    vector<Quanlynhanvien*> Danhsachnhanvien;
public:
    void Themnhanvien(Quanlynhanvien* nv) {
        Danhsachnhanvien.push_back(nv);
    }

    void Hienthitatcanhanvien() const {
        for (size_t i = 0; i < Danhsachnhanvien.size(); ++i) {
            Danhsachnhanvien[i]->Hienthithongtin();
            cout << "------------------------" << endl;
        }
    }

    double Tongluong() const {
        double S = 0;
        for (size_t i = 0; i < Danhsachnhanvien.size(); ++i) {
            S += Danhsachnhanvien[i]->Tinhluong();
        }
        return S;
    }

    ~Congty() {
        for (size_t i = 0; i < Danhsachnhanvien.size(); ++i) {
            delete Danhsachnhanvien[i];
        }
    }
};

int main() {
    Congty m;
    m.Themnhanvien(new Quanlynhanvien(1, "Nguyen Van A", 30, 10000000));
    m.Themnhanvien(new Quanlynhanvien(2, "Tran Thi B", 25, 8000000));
    m.Themnhanvien(new Quanly(3, "Le Van C", 40, 20000000, 5));

    cout << "Thong tin tat ca nhan vien: " << endl;
    m.Hienthitatcanhanvien();
    cout << "Tong luong cong ty: " << m.Tongluong() << endl;

    return 0;
}

