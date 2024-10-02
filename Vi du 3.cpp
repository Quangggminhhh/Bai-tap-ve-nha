#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TaiKhoan {
protected:
    string soTaiKhoan;
    string chuTaiKhoan;
    double soDu;

public:
    TaiKhoan(string so, string ten, double soDuKhoiTao)
        : soTaiKhoan(so), chuTaiKhoan(ten), soDu(soDuKhoiTao) {}

    virtual void napTien(double soTien) {
        if (soTien > 0) {
            soDu += soTien;
            cout << "Ða nap " << soTien << " vao tai khoan." << endl;
        } else {
            cout << "So tien khong hop le." << endl;
        }
    }

    virtual bool rutTien(double soTien) {
        if (soTien > 0 && soDu >= soTien) {
            soDu -= soTien;
            cout << "Da rut " << soTien << " tu tai khoan." << endl;
            return true;
        } else {
            cout << "Khong the rut tien. So du khong du hoac so tien khong hop le." << endl;
            return false;
        }
    }

    virtual void hienThiThongTin() const {
        cout << "So tai khoan: " << soTaiKhoan << endl;
        cout << "Chu tai khoan: " << chuTaiKhoan << endl;
        cout << "So du: " << soDu << endl;
    }

    virtual ~TaiKhoan() {}
};

class TaiKhoanTietKiem : public TaiKhoan {
private:
    double laiSuat;

public:
    TaiKhoanTietKiem(string so, string ten, double soDuKhoiTao, double lai)
        : TaiKhoan(so, ten, soDuKhoiTao), laiSuat(lai) {}

    void apDungLai() {
        double lai = soDu * laiSuat;
        napTien(lai);
        cout << "Da cong lai: " << lai << endl;
    }

    void hienThiThongTin() const override {
        TaiKhoan::hienThiThongTin();
        cout << "Lai suat: " << (laiSuat * 100) << "%" << endl;
    }
};

class TaiKhoanThanhToan : public TaiKhoan {
private:
    double gioiHanThauChi;

public:
    TaiKhoanThanhToan(string so, string ten, double soDuKhoiTao, double gioiHan)
        : TaiKhoan(so, ten, soDuKhoiTao), gioiHanThauChi(gioiHan) {}

    bool rutTien(double soTien) override {
        if (soTien > 0 && (soDu + gioiHanThauChi) >= soTien) {
            soDu -= soTien;
            cout << "Da rut " << soTien << " tu tai khoan." << endl;
            return true;
        } else {
            cout << "Khong the rut tien. So du khong du hoac so tien khong hop le." << endl;
            return false;
        }
    }

    void hienThiThongTin() const override {
        TaiKhoan::hienThiThongTin();
        cout << "Gioi han thau chi: " << gioiHanThauChi << endl;
    }
};

class NganHang {
private:
    vector<TaiKhoan*> danhSachTaiKhoan;

public:
    void themTaiKhoan(TaiKhoan* taiKhoan) {
        danhSachTaiKhoan.push_back(taiKhoan);
    }

    void hienThiTatCaTaiKhoan() const {
        for (size_t i = 0; i < danhSachTaiKhoan.size(); ++i) {
            danhSachTaiKhoan[i]->hienThiThongTin();
            cout << "------------------------" << endl;
        }
    }

    ~NganHang() {
        for (size_t i = 0; i < danhSachTaiKhoan.size(); ++i) {
            delete danhSachTaiKhoan[i];
        }
    }
};

int main() {
    NganHang nganHang;
    nganHang.themTaiKhoan(new TaiKhoanTietKiem("TK001", "Nguyen Van A", 1000000, 0.05));
    nganHang.themTaiKhoan(new TaiKhoanThanhToan("TK002", "Tran Thi B", 2000000, 500000));

    cout << "Thong tin tat ca tai khoan:" << endl;
    nganHang.hienThiTatCaTaiKhoan();

    return 0;
}

