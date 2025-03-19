#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fstream.h>   
#include <string.h>
#include <time.h>


//Variable ICSA
int i,j,k,l,x_best,x_best_total,permut1,permut2,HASIL,pcrow[300][300],pcrowUpdate[300][300],pcrowPop[300][300],
    pcrowModif[300][300],rute[300][300],rute_modif[300][300],ruteUpdate[300][300],brute[300],jum_ken,
    jum_pel,jum_crow,jum_crow1,fl,jum_pop,max_iterasi,pilihan1,nPop,iterasi ,iterasi1,pilihan,calon_induk[300];
float wmax=0.9,wmin=0.2,w_iter,fitness_relatif[300],cost_max, cost_min, temp,jarak_terpendek,jarak_terpendek_total,
	jarak_terpanjang,kap_ken,permintaan,AP;
float jarak[300][300],memori[300][300],jarakPop[300][300],jarakModif[300][300],jarakUpdate[300][300],
    jarak_total[300],jarak_totalMemori[300],jarak_totalUpdate[300],jarak_totalPosisi[300],jarak_totalModif[300],
    jarak_totalPop[300],jarak_memoricrow[300],jarakposisicrow[300],jarak_tempuh[300][300],jarak_tempuh_modif[300][300],urutan[300],urutanft[300];
double costKMpribadi[300], costKMsewa[300], costv[300], totcost[300],costKMpribadiPop[300], costKMsewaPop[300],
    costvPop[300],totcostPop[300],costKMpribadiModif[300], costKMsewaModif[300], costvModif[300], totcostModif[300],
    costKMpribadiUpdate[300], costKMsewaUpdate[300], costvUpdate[300] ,totcostUpdate[300],/*totcost_memori[300],*/ totcostWorst[300], costKMpribadiMemori[300],
    costKMsewaMemori[300], costvMemori[300],totcostMemori[300];   
double fitness[300],fitness_kumulatif[300],ri[300],rj[300],jumCrow,crow_best[300],crow_best_sementara[300],memori_awal[300][300],memori_baru[300][300],
    crow_update[300][300],pop_sa[300][300],pop_saModif[300][300], crow_awal[300][300],crow_awalPosisi[300][300],
    maksBeban,total_kapasitas_kendaraan,total_permintaan,data[300][300],bantuModif[300][300],random_induk[300];
//long double nilai_min, nilai_max;   
char file[50],nama[50],namafile[50],pil;   

random(int jum_crow,int jum_pel,double crow_awal[300][300],double memori_awal[300][300]);   
transformasi(int j,int jum_pel, double crow_awal[300][300],int pcrow[300][300]);
tentukan_rute(int j,int jum_pel,int pcrow[300][300],double data[300][300],int rute[300][300], float kap_ken, int brute[300],int jum_ken);   
fungsi_tujuan(int j,int jum_pel,int pcrow[300][300],int rute[300][300], int brute[300],int jum_ken,
     float jarak_tempuh[300][300],float jarak_total[300],float jarak[300][300], double costKMpribadi[300],
     double costKMsewa[300], double costv[300], double totcost[300]);
x_terbaik(int jum_crow,double totcost_memori[300],float cost_min, int x_best);
biaya_terkecil(int jum_crow,double totcost[300],float cost_min, int x_best);
jarak_terbaik(int jumcrow,float jarak_total[300],float jarak_terpendek);
void urutfitness(int jum_gagak);

ofstream OVRP;
char jawab[5];
void main()
{
    int jum_ken1,jum_crow1,fl,fl1,
    	max_iterasi1,jum_pel,i,j;
    int cek,tes,pilihdata,benar;
    int benarr,pilihan,pilihan2;
    float jum_ken, jum_crow, max_iterasi, pilihan1;

    clrscr();   
    ifstream OVRPICSA;

    cout<<"\n===============================================================";
    cout<<"\n                    ALTTALLARIKA SATRIA BIMANTARA              ";
    cout<<"\n                           082111233045                        ";
    cout<<"\n             **Program Improved Crow Search Algorithm**        ";
    cout<<"\n	  **Untuk Menyelesaikan Open Vehicle Routing Problem**		 ";
    cout<<"\n===============================================================";

    cout<<"\n Pilih: \n";
    cout<<" 1. Data Kecil\n";   
    cout<<" 2. Data Sedang\n";
    cout<<" 3. Data Besar\n";

    //Membuka data dengan format .txt
    do {

        cout<<"\n Pilihan : ";
        cin>>pilihan1;
        pilihan=pilihan1;
        pilihan2=pilihan1-pilihan;
        if (cin.fail()||pilihan<1||pilihan>3|| cin.peek() != '\n')
        {
            cin.clear(); // Menghapus flag error
            cin.ignore(999, '\n'); // Mengabaikan input yang salah
            cout << "Inputan harus 1,2,3, mohon diulangi!" << endl;
            continue; // Kembali ke awal loop
        }
        switch(pilihan)
        {
            case 1:
                OVRPICSA.open("dataKecil.txt");
                jum_pel=18;
                benarr=1;
                kap_ken=80;
                jum_ken=3;
                break;
            case 2:
                OVRPICSA.open("dataSedang.txt");
                jum_pel=50;
                benarr=1;
                kap_ken=150;
                jum_ken=4;
                break;
            case 3:
                OVRPICSA.open("dataBesar.txt");
                jum_pel=100;
                benarr=1;
                kap_ken=200;
                jum_ken=5;
                break;
            default:
                cout<<"Inputan harus 1,2,3, mohon diulangi!"<<endl;
                benarr=0;
        } break;
    	} while(true);
    	for(i=0;i<=jum_pel;i++)
    	{
        for(j=1;j<=3;j++)
        {
            if(pilihan==1)
            {OVRPICSA>>data[i][j];}
            else if(pilihan==2)
            {OVRPICSA>>data[i][j];}
            else if(pilihan==3)
            {OVRPICSA>>data[i][j];}
        }
    	}

    //INISIALISASI PARAMETER
    cout<<"===== INISIALISASI PARAMETER ====="<<endl;

    //MAKSIMUM ITERASI
    do
    {
        cout<<"Maksimum Iterasi (>=1)			: ";
        cin>>max_iterasi;
        max_iterasi1=max_iterasi;
        tes=0;
        if (cin.fail()||max_iterasi<=0|| cin.peek() != '\n'){
        	cin.clear(); // Menghapus flag error
        	cin.ignore(999, '\n'); // Mengabaikan input yang salah
         tes+=1;
        	cout<<"Inputan harus integer lebih dari 0, mohon diulangi !!"<<endl;
         continue;
        	} break;
    } while(true);

    //KAPASITAS MAKSIMUM KENDARAAN
    do
    {
        //cek kapasitas maksimum lebih besar kah dari semua permintaan pelanggan
        maksBeban=data[1][1];
        for(i=1;i<jum_pel;i++)
        {
            if(maksBeban<data[1][i])
            {
                maksBeban=data[1][i];
            }
        }
        if(maksBeban>kap_ken)
        {
            cout<<"Terdapat permintaan pelanggan yang melebihi kapasitas atau Inputan salah, mohon ulangi!!"<<endl;
        }
    } while(maksBeban>kap_ken);

    //JUMLAH KENDARAAN
    do
    {
        jum_ken1=jum_ken;
        total_permintaan=0;
        //cek jumlah kendaraan
        for(i=1;i<=jum_pel;i++)
        {
            total_permintaan=total_permintaan+data[1][i];
        }
        total_kapasitas_kendaraan=kap_ken*jum_ken;
        if(jum_ken!=jum_ken1)
        {
            cout<<"inputan harus integer, mohon diulangi!!"<<endl;
        }
        else
        {
            if(total_kapasitas_kendaraan<total_permintaan)
            {
                cout<<"Total Permintaan melebihi Total Kapasitas Kendaraan"<<endl;
            }
            if(jum_ken<=0)
            {
                cout<<"Inputan salah, mohon diulangi!!"<<endl;
            }
        }
    } while(jum_ken<=0||total_kapasitas_kendaraan<total_permintaan||jum_ken!=jum_ken1);

    //PARAMETER IMPROVED CROW SEARCH ALGORITHM
    //JUMLAH GAGAK
    do {
        cout << "Jumlah Gagak (>=2)						: ";
        cin >> jum_crow;
        jum_crow1=jum_crow;
        tes=0;
        // Cek apakah input valid
        if (cin.fail()||jum_crow<=1|| cin.peek() != '\n') {
            cin.clear(); // Menghapus flag error
            cin.ignore(999, '\n'); // Mengabaikan input yang salah
            tes+=1;
            cout << "Inputan harus integer lebih dari 2, mohon diulangi!" << endl;
           	continue; // Kembali ke awal loop
            }
            break;
    	} while(true);

    //PARAMETER PANJANG TERBANG
    do
    {
        cout<<"Panjang Terbang (>=1)						: ";
        cin>>fl;
        fl1=fl;
        tes=0;
        if (cin.fail()||fl<1|| cin.peek() != '\n') {
            cin.clear(); // Menghapus flag error
            cin.ignore(999, '\n'); // Mengabaikan input yang salah
            tes+=1;
            cout << "Inputan harus integer, mohon diulangi!" << endl;
            continue; // Kembali ke awal loop
        } break;
        }while(true);

    //PARAMETER PROBABILITAS KEWASPADAAN
    do
    {
        cout<<"Probabilitas Kewaspadaan (0-1)						: ";
        cin>>AP;
        tes=0;
        if (cin.fail()|| AP<=0||AP>1|| cin.peek() != '\n') {
            cin.clear(); // Menghapus flag error
            cin.ignore(999, '\n'); // Mengabaikan input yang salah
            tes+=1;
            cout << "Inputan harus rentang 0 hingga 1, mohon diulangi!" << endl;
            continue; // Kembali ke awal loop
        	}break;
        } while(true);

    clrscr();
    cout<<"----------------------------------------"<<endl<<endl;
    cout<<"nama file: ";
    cin>>file;
    cout<<endl<<"nomer urut file: ";
    cin>>HASIL;
    cout<<endl<<endl<<endl;

    //output notepad
    strcat(file," ke- ");        //menambah karakter ke dalam variabel
    strcpy(namafile,file);       //mengopi isi file ke nama file
    itoa(HASIL,nama,10);         //misal diinputkan HASIL=2202, membuat nama berisi 2202
    strcat(namafile,nama);     //menambah karakter nama ke dalam variabel namafile
    strcat(namafile,".txt"); //strcat berfungsi untuk menggabungkan 2 buah string (melakukan penggabungan variable namafile dan .txt)
    cout<<namafile<<endl<<endl;

    OVRP.open(namafile);
    OVRP<<"\n===============================================================";
    OVRP<<"\n                    ALTTALLARIKA SATRIA BIMANTARA              ";
    OVRP<<"\n                           082111233045                        ";
    OVRP<<"\n             **Program Improved Crow Search Algorithm**        ";
    OVRP<<"\n		**Untuk Menyelesaikan Open Vehicle Routing Problem**		 ";
    OVRP<<"\n===============================================================";
    OVRP<<endl;
    OVRP<<endl;
    OVRP<<"----------Parameter yang digunakan ----------"<<endl;
    OVRP<<" Kapasitas Maksimum kendaraan		= "<<kap_ken<<endl;
    OVRP<<" Jumlah Maksimum Kendaraan 			= "<<jum_ken<<endl;
    OVRP<<" Maksimum Iterasi (>=2)				= "<<max_iterasi<<endl;
    OVRP<<" Jumlah Gagak (>=2)					= "<<jum_crow<<endl;
    OVRP<<" Panjang Terbang (>=1) 				= "<<fl<<endl;
    OVRP<<" Peluang Kewaspadaan (0-1) 			= "<<AP<<endl;
    OVRP<<"\n =========== Data Pelanggan =========== : "<<endl;
    OVRP<<"\n Titik Koordinat : "<<endl;
    OVRP<<"X  "<<" Y "<<"  D" ;
    OVRP<<endl;

    //Data pelanggan
    for(i=0;i<=jum_pel;i++)
    {
        for(j=0;j<3;j++)
        {
            OVRP<<data[i][j]<<"  ";
        }
        OVRP<<endl;
    }
    OVRP<<endl;

    //jarak tempuh
    for(i=0;i<=jum_pel;i++)
    {
        for(j=0;j<=jum_pel;j++)
        {
            if(pilihan1==1||pilihan1==2||pilihan1==3)
            {
                jarak_tempuh[i][j]=sqrt(pow((data[i][0]-data[j][0]),2)+
                pow((data[i][1]-data[j][1]),2));
            }
        }
    }
    OVRP<<endl;

    OVRP<<"Jarak antar pelanggan dan Jarak depot ke pelanggan = "<<endl;

    for(i=0;i<=jum_pel;i++)
    {
        for(j=0;j<=jum_pel;j++)
        {
            OVRP<<jarak_tempuh[i][j]<<"\t ";
        }
        OVRP<<endl;   
    }   
    OVRP<<endl;

    //random bilangan real(0,1)
  	 OVRP<<endl;
    OVRP<<" MEMORI AWAL = POSISI AWAL "<<endl;
    //memanggil fungsi random untuk membangkitkan pop awal
    random(jum_crow,jum_pel,crow_awal,memori_awal);
    OVRP<<" =========== Evaluasi Crow Posisi Awal =========== : "<<endl;
    for(int j=1;j<=jum_crow;j++)
    {
        OVRP<<" Crow ["<<j<<"]: "<<endl;
        //mengkonversi bil.real ke bentuk permutasi
        OVRP<<" Calon Rute Posisi Gagak ["<<j<<"]: "<<endl;
        //transformasi(j,jum_pel,crow_awalPosisi,pcrow);
        transformasi(j,jum_pel,crow_awal,pcrow);
        //menentukan rute
        tentukan_rute(j,jum_pel,pcrow,data,rute,kap_ken,brute,jum_ken);
        //Hitung Fungsi Tujuan   
        fungsi_tujuan(j,jum_pel,pcrow,rute,brute,jum_ken,jarak_tempuh,jarak_total,jarak,costKMpribadi,costKMsewa,costv,totcost);
        OVRP<<endl;
    }
    OVRP<<endl;

    OVRP<<" =========== Evaluasi Crow Memori Awal =========== : "<<endl;
    for(int j=1;j<=jum_crow;j++)
    {
        OVRP<<" Crow ["<<j<<"]: "<<endl;
        //mengkonversi bil.real ke bentuk permutasi
        OVRP<<" Calon Rute Memori gagak ["<<j<<"]: "<<endl;
        //transformasi(j,jum_pel,crow_awalPosisi,pcrow);
        transformasi(j,jum_pel,crow_awal,pcrow);
        //menentukan rute
        tentukan_rute(j,jum_pel,pcrow,data,rute,kap_ken,brute,jum_ken);
        //Hitung Fungsi Tujuan   
        fungsi_tujuan(j,jum_pel,pcrow,rute,brute,jum_ken,jarak_tempuh,jarak_totalMemori,memori,
        		costKMpribadiMemori,costKMsewaMemori,costvMemori,totcostMemori);
        OVRP<<endl;
    }
    OVRP<<endl;

    OVRP<<"------------------------------------------------"<<endl;
    cost_min=biaya_terkecil(jum_crow,totcostMemori,cost_min,x_best);
    x_best=x_terbaik(jum_crow,totcostMemori,cost_min,x_best);
    OVRP<<"===================ITERASI KE-0==================="<<endl;
    OVRP<<" Crow Terbaik Sementara Pada Iterasi-0 Adalah Crow Ke"<<x_best<<endl;
    //OVRP<<"dengan Jarak Terdekat: "<<jarak_total[x_best]<<" dan Biaya Terkecil= "<<totcost[x_best]<<endl;
    fungsi_tujuan(x_best,jum_pel,pcrow,rute,brute,jum_ken,jarak_tempuh,jarak_totalMemori,memori,
        		costKMpribadiMemori,costKMsewaMemori,costvMemori,totcostMemori);
    cout<<"===================ITERASI KE-0==================="<<endl;
    cout<<"Diperoleh Crow Terbaik sementara yaitu Crow ke "<<x_best<<endl;
    cout<<"dengan Jarak Terdekat: "<<jarak_total[x_best]<<" dan Biaya Terkecil= "<<totcost[x_best]<<endl;
    cout<<endl;
    cout<<"Posisi Crow Terbaik Sementara :"<<endl;
    for(int i=1;i<=jum_pel;i++)   
    {
        crow_best_sementara[i]=crow_awal[x_best][i];
        OVRP<<crow_best_sementara[i]<<" ";
    }
    OVRP<<endl;
    OVRP<<"------------------------------------------------"<<endl;
    OVRP<<endl;   

    //PROSES ITERASI
    for(iterasi=1;iterasi<=max_iterasi;iterasi++)
    {
        OVRP<<">>>>>>>>>>>>>>>>>>>> PROSES ITERASI KE "<<iterasi<<">>>>>>>>>>>>>>>>>>>>"<<endl;
        OVRP<<endl;
        OVRP<<" =========== Update Posisi Gagak =========== : "<<endl;
        cout<<">>>>>>>>>>>>>>>>>>>> PROSES ITERASI KE "<<iterasi<<">>>>>>>>>>>>>>>>>>>>"<<endl;
        //memanggil fungsi untuk menghitung fitness relatif,kumulatif,dan seleksi roulettee
        OVRP<<endl;
        urutfitness(jum_crow);
        OVRP<<endl;
        OVRP<<"\n----------------------------"<<endl;
      //memperbarui posisi
   	OVRP<<"PROSES UPDATE POSISI GAGAK"<<endl;
   	w_iter=wmax-(wmax-wmin)*(iterasi/max_iterasi);
        for(int j=1;j<=jum_crow;j++)
        {
            rj[j]=rand()/(double)RAND_MAX;   
            label:   
            permut1=random(jum_crow)+1;
            permut2=random(jum_crow)+1;

            if(permut1!=permut2)   
            {
                if(rj[j]>=AP)
                {   
                    OVRP<<" Karena rj["<<j<<"]= "<<rj[j]<<" > "<<AP<<"= AP maka dilakukan update posisi dengan Persamaan (2.8)"<<endl;
                    OVRP<<" Crow_Baru["<<j<<"]:"<<endl;
                    for(int i=1;i<=jum_pel;i++)   
                    {
                        ri[i]=rand()/(double)RAND_MAX;
                        crow_update[j][i]=w_iter*crow_awal[j][i]+ri[i]*fl*(memori_awal[permut1][i]-crow_awal[permut2][i]);
                        crow_awal[j][i] = crow_update[j][i];   
                        OVRP<<crow_awal[j][i]<<" ";   
                    }
                }
                else   
                {
                    OVRP<<" Karena r["<<j<<"]= "<<rj[j]<<" < "<<AP<<"= AP maka dilakukan update posisi secara Random"<<endl;   
                    OVRP<<" Crow_Baru["<<j<<"]:"<<endl;
                    for(int i=1;i<=jum_pel;i++)   
                    {   
                        crow_update[j][i]=rand()/(double)RAND_MAX;   
                        crow_awal[j][i] = crow_update[j][i];
                        OVRP<<crow_awal[j][i]<<" ";
                    }   
                }   
            } else goto label;

            //MEMANGGIL FUNGSI UNTUK EVALUASI FUNGSI TUJUAN POSISI BARU

            // FUNGSI TUJUAN POSISI BARU (HASIL UPDATE POSISI)   
            //OVRP<<"Crow_Baru["<<j<<"]: "<<endl;
            OVRP<<" Calon Rute Posisi Gagak["<<j<<"]: "<<endl;
            transformasi(j,jum_pel,crow_awal,pcrow);
            //menentukan rute   
            tentukan_rute(j,jum_pel,pcrow,data,rute,kap_ken,brute,jum_ken);   
            //Hitung Fungsi Tujuan
            fungsi_tujuan(j,jum_pel,pcrow,rute,brute,jum_ken,jarak_tempuh,jarak_total,
            		jarak,costKMpribadi,costKMsewa,costv,totcost);
            OVRP<<endl;   
        }

        //PERBANDINGAN MEMORI AWAL=POSISI AWAL DENGAN POSISI BARU   
        OVRP<<" =========== Update Memori Gagak =========== : "<<endl;
        for (i=1; i<=jum_crow; i++)   
        {
            if (totcostMemori[i] <= totcost[i])
            {
                OVRP<<" Karena biaya Memori Crow["<<i<<"] ("<<totcostMemori[i]<<") <= Biaya Update Posisi Crow ["<<i<<"] ("<<totcost[i]<<")"<<endl;
                for(int j=1;j<=jum_pel;j++)
                {   
                    memori_baru[i][j]=memori_awal[i][j];   
                    totcostUpdate[i]=totcostMemori[i];
                    jarak_totalUpdate[i]=jarak_totalMemori[i];
                }
                OVRP<<" Maka, Biaya Memori["<<i<<"] = "<<totcostUpdate[i]<<endl;
                OVRP<<endl;   
            }
            else
            {   
                                OVRP<<" Karena biaya Memori Crow["<<i<<"] ("<<totcostMemori[i]<<") > Biaya UpdatePosisi Crow ["<<i<<"] ("<<totcost[i]<<")"<<endl;
                for(int j=1;j<=jum_pel;j++)
                {   
                    memori_baru[i][j]=crow_update[i][j];
                    totcostUpdate[i]=totcost[i];
                    jarak_totalUpdate[i]=jarak_total[i];
                }
                OVRP<<" Maka, Biaya Memori["<<i<<"] = "<<totcostUpdate[i]<<endl;
                OVRP<<endl;
            }
        }

        //MENAMPILKAN SOLUSI TERBAIK PADA SETIAP ITERASI
        if(iterasi<=max_iterasi)
			{
      	cost_min=biaya_terkecil(jum_crow,totcostUpdate,cost_min,x_best);
			x_best=x_terbaik(jum_crow,totcostUpdate,cost_min,x_best);
         OVRP<<" Crow Terbaik sementara = Crow ke - "<<x_best<<endl;
         OVRP<<" Jarak Terdekat = "<<jarak_total[x_best]<<endl;
        	OVRP<<" Biaya Terkecil = "<<totcost[x_best]<<endl;
         cout<<" Crow Terbaik sementara = Crow ke - "<<x_best<<endl;
         cout<<" Jarak Terdekat = "<<jarak_total[x_best]<<endl;
        	cout<<" Biaya Terkecil = "<<totcost[x_best]<<endl;


         }
        // OVRP<<"Memori Baru Menggantikan Memori Lama"<<endl;
        for (j=1; j<=jum_pel; j++)   
        {
            memori_awal[i][j]=memori_baru[i][j];   
            totcostMemori[j]=totcostUpdate[j];
            jarak_totalMemori[j]=jarak_totalUpdate[j];
        }
        OVRP<<endl;
    }
    OVRP<<endl;
    OVRP<<" _____________________ HASIL AKHIR ________________"<<endl;
    OVRP<<endl;
    cout<<" _____________________ HASIL AKHIR ________________"<<endl;
    cout<<endl;
    cost_min=biaya_terkecil(jum_crow,totcostMemori,cost_min,x_best);     // untuk biaya terbaik keseluruhan
    x_best_total=x_terbaik(jum_crow,totcostMemori,cost_min,x_best);
    OVRP<<" CROW TERBAIK = "<<x_best_total<<endl;
    cout<<" CROW TERBAIK = "<<x_best_total<<endl;
    OVRP<<" Posisi Crow Terbaik : "<<endl;   
    for(int i=1;i<=jum_pel;i++)
    {
        //crow_best[i]=memori_baru[x_best_total][i];
        OVRP<<memori_baru[x_best_total][i]<<" ";
    }
    OVRP<<endl; 
    OVRP<<" Maka diperoleh jarak terdekat "<<jarak_totalMemori[x_best_total]<<" dan Biaya Terkecil "<<totcostMemori[x_best_total]<<endl;
    OVRP<<endl;
    OVRP<<" ________________________________________________"<<endl;
    OVRP<<endl;
    cout<<" Maka diperoleh jarak terdekat "<<jarak_totalMemori[x_best_total]<<" dan Biaya Terkecil "<<totcostMemori[x_best_total]<<endl;
    cout<<endl;
    cout<<" ________________________________________________"<<endl;
        cout<<endl;

    OVRPICSA.close();
    getch();
}

random(int jum_crow,int jum_pel,double crow_awal[300][300], double memori_awal[300][300])
{
    randomize();
    OVRP<<" =========== Posisi Awal =========== : "<<endl;
    for(int i=1;i<=jum_crow;i++)
    {   
        OVRP<<"Crow["<<i<<"]:"<<endl;
        for(int j=1;j<=jum_pel;j++)
        {   
            crow_awal[i][j]=rand()/(double)RAND_MAX;
            OVRP<<crow_awal[i][j]<<" ";
        } OVRP<<endl;   
    }   

    OVRP<<" =========== Memori Awal =========== : "<<endl;
    for(int i=1;i<=jum_crow;i++)   
    {
        OVRP<<"Memori["<<i<<"]:"<<endl;   
        for(int j=1;j<=jum_pel;j++)
        {
            memori_awal[i][j]=crow_awal[i][j];   
            OVRP<<memori_awal[i][j]<<" ";   
        } OVRP<<endl;   
    }   
    return 0;
}   

transformasi(int j,int jum_pel, double crow_awal[300][300],int pcrow[300][300])   
{   
    int i,l,k;
    for(i=1;i<=jum_pel;i++)   
    {   
        k=1;   
        for(l=1;l<=jum_pel;l++)   
        {
            if(crow_awal[j][i]>crow_awal[j][l])   
            {   
                k+=1;   
            } 
            pcrow[j][i]=k;
        } OVRP<<"  "<<pcrow[j][i];   
    }   
    OVRP<<endl;   
    return 0;   
}

tentukan_rute(int j,int jum_pel,int pcrow[300][300],double data[300][300],int rute[300][300], float kap_ken, int brute[300],int jum_ken)   
{   
    int i,h,k;   
    float permintaan;
    h=1; k=1; permintaan=0;   
    do   
    {   
        for(i=h;i<=jum_pel;i++)   
        {
            permintaan=permintaan+data[pcrow[j][i]][2];   
            if(permintaan>kap_ken)   
            {   
                break;   
            }
        }   
        h=i;   
        rute[j][k]=i-1;   
        k++;   
        permintaan=0;
    } while(i<=jum_pel);   

    brute[j]=k-1;   

    for(h=1;h<=brute[j];h++)
    {   
        rute[j][0]=0;   
        OVRP<<" rute ke- "<<h<<" : ";   
        if (h<=jum_ken)   
        {
            OVRP<<"0 ";   
            for(i=(rute[j][(h-1)])+1;i<=rute[j][h];i++)   
            {   
                OVRP<<pcrow[j][i]<<" ";   
            }
            OVRP<<"0";   
        }   
        else   
        {
            OVRP<<"0 ";
            for(i=(rute[j][(h-1)])+1;i<=rute[j][h];i++)   
            {   
                OVRP<<pcrow[j][i]<<" ";   
            }   
        }
        OVRP<<endl;   
    }   
    return 0;   
}   

// FUNGSI TUJUAN   
fungsi_tujuan(int j,int jum_pel,int pcrow[300][300],int rute[300][300], int brute[300],int jum_ken, float jarak_tempuh[300][300],
					float jarak_total[300],float jarak[300][300], double costKMpribadi[300],double costKMsewa[300], double costv[300], double totcost[300])
{   
    int i,h,k;
    jarak_total[j]=0;   
    for(i=1;i<=brute[j];i++)
    {   
        rute[j][0]=0;   
        jarak[j][i]=0;

        if (i<=jum_ken) //jika misal rute 1 <= 3 kendaraan ( harus kembali 0)
        {
            // RUTE TERTUTUP VRP   
            for(k=(rute[j][i-1]+1); k<=rute[j][i]; k++)
            {   
                h=k-1;   

                if(k==(rute[j][i-1]+1))   
                {
                    h=0;   
                }   
                jarak[j][i]=jarak[j][i]+jarak_tempuh[pcrow[j][h]][pcrow[j][k]]; // jarak antar pelanggan   
            }   
            jarak[j][i]=jarak[j][i]+jarak_tempuh[pcrow[j][k]][pcrow[j][0]]; // jarak pelanggan terakhir ke 0
            costKMpribadi[j]= jarak[j][i]*0.5;   
        }   
        else  // RUTE TERBUKA OVRP
        {   
            for(k=(rute[j][i-1]+1); k<=rute[j][i]; k++)
            {   
                h=k-1;   
                if(k==(rute[j][i-1]+1))   
                {   
                    h=0;
                }   
                jarak[j][i]=jarak[j][i]+jarak_tempuh[pcrow[j][h]][pcrow[j][k]]; // jarak antar pelanggan   
            }   
            // jarak[j][i]=jarak[j][i]+jarak_tempuh[pcrow[j][k]][pcrow[j][0]]; // jarak pelanggan terakhir ke 0   
            costKMsewa[j]= jarak[j][i]*0.6;
            costv[j]= (i-jum_ken)*15;   
        }   
        jarak_total[j]=jarak_total[j]+jarak[j][i];   

        // TOTAL BIAYA
        totcost[j]=costKMpribadi[j]+costKMsewa[j]+costv[j];   
    }   

    OVRP<<" Jarak Total = "<<jarak_total[j]<<endl;   
    OVRP<<" Biaya Jarak(per KM) Kendaraan Pribadi = "<<costKMpribadi[j]<<endl;
    OVRP<<" Biaya Jarak(per KM) Kendaraan Sewa = "<<costKMsewa[j]<<endl;   
    OVRP<<" Biaya Sewa Kendaraan = "<<(brute[j]-jum_ken)<<" kendaraan sewa"<<" x 15 = "<<costv[j]<<endl;   
    OVRP<<" Total Biaya = "<<costKMpribadi[j]<<" + "<<costKMsewa[j]<<" + "<<costv[j]<<" = "<<totcost[j]<<endl;   

    return 0;
}

// Fungsi untuk sorting nilai fitness
void sorting (int jum_crow)
{
	double temp;
   for (j=1; j<=jum_crow; j++)
   {
    urutanft[j]=totcost[j];
   }
   for (i=1; i<=jum_crow; i++)
   {
   	int min = i;
      for (j=1; j<=jum_crow; j++)
      if (urutanft[j]>urutanft[min])
      {
      	min = j;
         temp = urutanft[i];
         urutanft[i] = urutanft[min];
         urutanft[min]= temp;
      }
   }
}

/* Fungsi Untuk Prosedur Perhitungan Nilai Fitness,
	Ranking, Fitness Relatif dan Fitness kumulatif */
void urutfitness(int jum_crow)
{
   //Perhitungan nilai fitness dan pengurutan
   float totalft=0,totalfitness=0;
   for(int i=1;i<=jum_crow;i++)
   {
      OVRP<<"Rank Gagak ["<<i<<"]:";
      int k=1;
      for (int l=1; l<=jum_crow; l++)
      {
       	if (totcostMemori[i]>totcostMemori[l])
         {
          k+=1;
         }
         urutan[i]=k;
      }
      OVRP<<urutan[i]<<endl;
   }
   sorting(jum_crow);
   for (i=1; i<=jum_crow; i++)
   {
   	totalft=totalft+urutanft[i];
   }
   OVRP<<endl;
	OVRP<<"Total ft = "<<totalft<<endl;
   OVRP<<endl<<"Fitness\t|"<<"Fitness Relatif\t|"<<"Fitness Kumulatif";
   for(i=1;i<=jum_crow;i++)
   {
   	fitness[i]=totalft-urutanft[i];
      totalfitness=totalfitness+fitness[i];
   }
   //Prosedur Perhitungan Fitness Relatif dan Kumulatif
   fitness_kumulatif[0]=0;
   for(i=1;i<=jum_crow;i++)
   {
   	fitness_relatif[i]=fitness[i]/totalfitness;
      fitness_kumulatif[i]=fitness_kumulatif[i-1]+fitness_relatif[i];
      OVRP<<endl<<fitness[i]<<"\t| "<<fitness_relatif[i]<<"      \t|"<<fitness_kumulatif[i];
   }
   OVRP<<endl<<endl<<""<<"Rand       \t|"<<"Pilih|";

   // Proses Seleksi Roda Roulette
   for(i=1;i<=jum_crow;i++)
   {
   	random_induk[i]=rand()/(double)(RAND_MAX);
      OVRP<<endl<<random_induk[i]<<"\t|";
      for(j=1;j<=jum_crow;j++)
      {
      	if(random_induk[i]<=fitness_kumulatif[j])
         {
				calon_induk[i]=j;
            OVRP<<calon_induk[i]<<"\t|";
            break;
         }
      }
   }
}
// jarak gagak terbaik   
jarak_terbaik(int jum_crow,float jarak_total[300],float jarak_terpendek)
{   
    jarak_terpendek=jarak_total[1];   
    for(int i=1;i<=jum_crow;i++)   
    {   
        if(jarak_total[i]<=jarak_terpendek)
        {   
            jarak_terpendek=jarak_total[i];
            x_best=i;
        }
    }
    return jarak_terpendek;   
}   

  

x_terbaik(int jum_crow,double totcost[300],float cost_min, int x_best)
{
    cost_min=totcost[1];   
    for(int i=1;i<=jum_crow;i++)
    {
        if(totcost[i]<=cost_min)   
        {   
            cost_min=totcost[i];   
            x_best=i;   
        }
    }   
    return x_best;   
}   


// biaya terkecil (terbaik)
biaya_terkecil(int jum_crow,double totcost[300],float cost_min,int x_best)
{
    cost_min=totcost[1];
    for(int i=1;i<=jum_crow;i++)
    {
        if(totcost[i]<=cost_min)
        {
            cost_min=totcost[i];
            x_best=i;
        }
    }
    return cost_min;
}
