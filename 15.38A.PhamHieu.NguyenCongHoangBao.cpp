#include<iostream>
#include<vector>
#include<windows.h>
#include<fstream>
using namespace std;

// dinh nghia cau truc thoi gian (gio, phut, giay)
struct thoi_gian
{
    int gio;
    int phut;
    int giay;
    char dau1;
    char dau2;
};

// dinh nghia cau truc ngay (ngay, thang, nam)
struct ngay
{
    int ngay;
    int thang;
    int nam;
    char ky_tu1;
    char ky_tu2;
};

class xe
{
    string bien_so;
    int loai;
    ngay ngay_gio_vao;
    thoi_gian gio_vao;
    thoi_gian gio_ra;

public:
    void themXe();
    void xoaXe();
    void inXe(xe x);
    void hienThi();
};

vector<xe> danh_sach_xe(100); // Tao mang luu tru thong tin cua 100 xe
int static so_luong_xe = 0, so_xe_hoi = 0, so_xe_bus = 0, so_xe_tai = 0, tong_doanh_thu = 0, i = 0;

fstream file; // doi tuong file
void xe::themXe()
{
    xe* x = new xe; // Tao mot doi tuong xe moi

    cout << "Nhap loai xe (1 cho o to/2 cho xe bus/ 3 cho xe tai) : ";
    cin >> x->loai;
    cout << "Nhap bien so xe : ";
    cin >> x->bien_so;
    cout << "Nhap thoi gian vao (hh/mm/ss) : ";
    cin >> x->gio_vao.gio >> x->gio_vao.dau1 >> x->gio_vao.phut >> x->gio_vao.dau2 >> x->gio_vao.giay;
    cout << "Nhap ngay (dd/mm/yy) : ";
    cin >> x->ngay_gio_vao.ngay >> x->ngay_gio_vao.ky_tu1 >> x->ngay_gio_vao.thang >> x->ngay_gio_vao.ky_tu2 >> x->ngay_gio_vao.nam;

    danh_sach_xe.at(i).bien_so = x->bien_so;
    danh_sach_xe.at(i).loai = x->loai;
    danh_sach_xe.at(i).gio_vao.gio = x->gio_vao.gio;
    danh_sach_xe.at(i).gio_vao.phut = x->gio_vao.phut;
    danh_sach_xe.at(i).gio_vao.giay = x->gio_vao.giay;
    danh_sach_xe.at(i).ngay_gio_vao.ngay = x->ngay_gio_vao.ngay;
    danh_sach_xe.at(i).ngay_gio_vao.thang = x->ngay_gio_vao.thang;
    danh_sach_xe.at(i).ngay_gio_vao.nam = x->ngay_gio_vao.nam;

    i++;
    so_luong_xe++;

    switch(x->loai) {
        case 1: so_xe_hoi++; 
		break;
        case 2: so_xe_bus++; 
		break;
        case 3: so_xe_tai++; 
		break;
        default: break;
    }

    cout << "\nXe da duoc them thanh cong" << endl;
}

int tinhthoigianchenhlech(thoi_gian t1, thoi_gian t2)
{

    int giay1, giay2, tong_giay;
    thoi_gian t3;
    // tinh thoi gian lech gio
    // Chuyen thoi gian ve tong giay
    giay1 = t1.gio * 60 * 60 + t1.phut * 60 + t1.giay;
    giay2 = t2.gio * 60 * 60 + t2.phut * 60 + t2.giay;

    tong_giay = giay2 - giay1;

    // Chuyen so giay ve gio, phut, giay
    t3.phut = tong_giay / 60;
    t3.gio = t3.phut / 60;
    t3.phut = t3.phut % 60;
    t3.giay = tong_giay % 60;

    return t3.gio; // Tra ve so gio chenh lech
}

void xe::xoaXe()
{
    string bien_so;
    int loai;
    thoi_gian gio_ra;
    int thoi_gian_chenh_lech;
    int tien_phi = 0;

    cout << "Nhap loai xe (1 cho o to/2 cho xe bus/3 cho xe tai) : ";
    cin >> loai;
    cout << "Nhap bien so xe : ";
    cin >> bien_so;
    cout << "Nhap thoi gian ra (gio:phut:giay) : ";
    cin >> gio_ra.gio >> gio_ra.dau1 >> gio_ra.phut >> gio_ra.dau2 >> gio_ra.giay;

    for (int j = 0; j < i; j++)
    {
        if ((danh_sach_xe.at(j).bien_so == bien_so) && (danh_sach_xe.at(j).loai == loai))
        {
            danh_sach_xe.at(j).gio_ra.gio = gio_ra.gio;
            danh_sach_xe.at(j).gio_ra.phut = gio_ra.phut;
            danh_sach_xe.at(j).gio_ra.giay = gio_ra.giay;

            thoi_gian_chenh_lech = tinhthoigianchenhlech(danh_sach_xe.at(j).gio_vao, gio_ra);

            if (danh_sach_xe.at(j).loai == 1)
            {
                so_xe_hoi--;
                if (thoi_gian_chenh_lech < 2)
                {
                    tien_phi = 20;
                }
                else if ((thoi_gian_chenh_lech > 2) && (thoi_gian_chenh_lech < 5))
                {
                    tien_phi = 40;
                }
                else
                {
                    tien_phi = 50;
                }
            }
            else if (danh_sach_xe.at(j).loai == 2)
            {
                so_xe_bus--;

                if (thoi_gian_chenh_lech < 2)
                {
                    tien_phi = 5;
                }
                else if ((thoi_gian_chenh_lech > 2) && (thoi_gian_chenh_lech < 5))
                {
                    tien_phi = 10;
                }
                else
                {
                    tien_phi = 20;
                }
            }
            else
            {
                so_xe_tai--;
                if (thoi_gian_chenh_lech < 2)
                {
                    tien_phi = 10;
                }
                else if ((thoi_gian_chenh_lech > 2) && (thoi_gian_chenh_lech < 5))
                {
                    tien_phi = 20;
                }
                else
                {
                    tien_phi = 40;
                }
            }

            cout << "\nXe co bien so  : " << danh_sach_xe.at(j).bien_so << " da roi khoi bai do va thanh toan so tien la. " << tien_phi << endl;
            file.open("parkingDatabase.txt", ios::app);
            if (!file)
            {
                cerr << "Loi: khong the mo tep" << endl;
                exit(1);
            }

            file << danh_sach_xe.at(j).loai << "\t\t\t" << danh_sach_xe.at(j).bien_so << "\t\t\t" << danh_sach_xe.at(j).ngay_gio_vao.ngay << "/" << danh_sach_xe.at(j).ngay_gio_vao.thang << "/" << danh_sach_xe.at(j).ngay_gio_vao.nam << "\t\t\t" << danh_sach_xe.at(j).gio_vao.gio << ":" << danh_sach_xe.at(j).gio_vao.phut << ":" << danh_sach_xe.at(j).gio_vao.giay << "\t\t\t" << danh_sach_xe.at(j).gio_ra.gio << ":" << danh_sach_xe.at(j).gio_ra.phut << ":" << danh_sach_xe.at(j).gio_ra.giay << endl;
            file.close();
            danh_sach_xe.erase(danh_sach_xe.begin() + j);
            i--;
            so_luong_xe--;
            tong_doanh_thu = tong_doanh_thu + tien_phi;
            break;
	if (j == i){

        cout << "\nNhap sai , Vui long nhap lai " << endl;
        cout << "Roi bai do : " << endl;
        xoaXe();
	}
   }
  }
}
void xe::inXe(xe x)
{
    cout << x.loai << "\t\t\t" << x.bien_so << "\t\t\t" << x.ngay_gio_vao.ngay << "/" << x.ngay_gio_vao.thang << "/" << x.ngay_gio_vao.nam << "\t\t\t" << x.gio_vao.gio << ":" << x.gio_vao.phut << ":" << x.gio_vao.giay << endl;
}

void xe::hienThi()
{
    cout << "Loai xe\t\tBien so xe\t\t\tNgay\t\t\tThoi gian vao" << endl;
    for (int j = 0; j < i; j++)
    {
        inXe(danh_sach_xe[j]);
    }
}

void tongXe()
{
    cout << "Tong so xe da do : " << so_luong_xe << endl;
    cout << "Tong so xe o to da do : " << so_xe_hoi << endl;
    cout << "Tong so xe bus da do : " << so_xe_bus << endl;
    cout << " Tong so xe tai da do : " << so_xe_tai << endl;
}

void tongDoanhThu()
{
    cout << "Tong doanh thu den nay : " << tong_doanh_thu << endl;
}

int main()
{
    int lua_chon;
    char ans;
    system("cls");

    do
    {
        system("cls");
        cout << "********************************************************************" << endl;
        cout << "                 HE THONG BAI DO XE                 " << endl;
        cout << "1.Xe den do" << endl
            << "2.Tong so xe da do" << endl
            << "3.Xe roi di" << endl
            << "4.Tong doanh thu " << endl
            << "5.Hien thi " << endl
            << "6.Thoat" << endl
            << "********************************************************************" << endl
            << "Nhap lua chon cua ban: ";
        cin >> lua_chon;

        switch (lua_chon)
        {
        case 1: system("cls");
            cout << "Them xe : " << endl;
            danh_sach_xe.at(i).themXe();
            break;

        case 2: system("cls");
            tongXe();
            break;

        case 3: system("cls");
            cout << "Roi bai do : " << endl;
            danh_sach_xe.at(i).xoaXe();
            break;

        case 4: system("cls");
            tongDoanhThu();
            break;

        case 5: system("cls");
            danh_sach_xe.at(i).hienThi();
            break;
        case 6: exit(0);
        }

        cout << "\nBan co muon tiep tuc, nhan y/n : " << endl;
        cin >> ans;
        if (ans == 'n')
        {
            break;
        }
        else
        {
            continue;
        }

    } while (1);

    return 0;
}



