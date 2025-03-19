import random 
import pandas as pd
import math
import sys

def random_crow(ju, jum_pel):
    crow_awal = [[random.random() for _ in range(jum_pel + 1)] for _ in range(ju + 1)]
    memori_awal = [row[:] for row in crow_awal]

    print("========== Posisi Awal =========== :")
    for i in range(1, ju + 1):
        print(f"Crow[{i}]: {crow_awal[i][1:]}")

    print("========== Memori Awal =========== :")
    for i in range(1, ju + 1):
        print(f"Memori[{i}]: {memori_awal[i][1:]}")
    
    return crow_awal, memori_awal

def transformasi(j, jum_pel, crow_awal):
    pcrow = [[0] * (jum_pel + 1) for _ in range(len(crow_awal))]
    
    for i in range(1, jum_pel + 1):
        k = 1
        for l in range(1, jum_pel + 1):
            if crow_awal[j][i] > crow_awal[j][l]:
                k += 1
        pcrow[j][i] = k
    
    print(f"PCrow[{j}]: {pcrow[j][1:]}")
    return pcrow

def tentukan_rute(j, jum_pel, pcrow, data, kap_ken):
    # Inisialisasi rute dengan ukuran yang cukup
    rute = [[0] * (jum_pel + 1) for _ in range(len(pcrow))]
    brute = [0] * len(pcrow)
    
    h = 1
    k = 1
    permintaan = 0

    while h <= jum_pel:
        for i in range(h, jum_pel + 1):
            permintaan += data[pcrow[j][i]][2]
            if permintaan > kap_ken:
                break
        # Pastikan k tidak melebihi batas
        if k < len(rute[j]):
            rute[j][k] = i - 1  # Menyimpan rute
        else:
            print(f"Warning: Indeks k={k} melebihi batas untuk j={j}.")
            break
        k += 1
        permintaan = 0
        h = i

    brute[j] = k - 1

    # Menampilkan rute
    for h in range(1, brute[j] + 1):
        rute[j][0] = 0  # Menetapkan titik awal
        print(f"Rute ke-{h}: ", end="")
        if h <= len(rute):
            print("0 ", end="")
            for i in range(rute[j][h - 1] + 1, rute[j][h] + 1):
                print(f"{pcrow[j][i]} ", end="")
            print("0")
        else:
            print("0 ", end="")
            for i in range(rute[j][h - 1] + 1, rute[j][h] + 1):
                print(f"{pcrow[j][i]} ", end="")
            print()
    
    return rute, brute

def fungsi_tujuan(j, jum_pel, pcrow, rute, brute, jum_ken, jarak_tempuh, jarak_total, jarak, costKMpribadi, costKMsewa, costv, totcost):
    jarak_total[j] = 0
    
    for i in range(1, brute[j] + 1):
        rute[j][0] = 0
        jarak[j][i] = 0

        if i <= jum_ken:  # RUTE TERTUTUP VRP
            for k in range(rute[j][i - 1] + 1, rute[j][i] + 1):
                h = k - 1
                if k == (rute[j][i - 1] + 1):
                    h = 0
                jarak[j][i] += jarak_tempuh[pcrow[j][h]][pcrow[j][k]]  # jarak antar pelanggan
            
            jarak[j][i] += jarak_tempuh[pcrow[j][k]][pcrow[j][0]]  # jarak pelanggan terakhir ke 0
            costKMpribadi[j] = jarak[j][i] * 0.5
        
        else:  # RUTE TERBUKA OVRP
            for k in range(rute[j][i - 1] + 1, rute[j][i] + 1):1
        h = k - 1
        if k == (rute[j][i - 1] + 1):
                    h = 0
                    jarak[j][i] += jarak_tempuh[pcrow[j][h]][pcrow[j][k]]  # jarak antar pelanggan
            
        costKMsewa[j] = jarak[j][i] * 0.6
        costv[j] = (i - jum_ken) * 15
        
        jarak_total[j] += jarak[j][i]  # Total jarak

        # TOTAL BIAYA
        totcost[j] = costKMpribadi[j] + costKMsewa[j] + costv[j]

    # Output hasil
    print(f"Jarak Total = {jarak_total[j]}")
    print(f"Biaya Jarak(per KM) Kendaraan Pribadi = {costKMpribadi[j]}")
    print(f"Biaya Jarak(per KM) Kendaraan Sewa = {costKMsewa[j]}")
    print(f"Biaya Sewa Kendaraan = {(brute[j] - jum_ken)} kendaraan sewa x 15 = {costv[j]}")
    print(f"Total Biaya = {costKMpribadi[j]} + {costKMsewa[j]} + {costv[j]} = {totcost[j]}")

    return fungsi_tujuan

def urutfitness(ju, totcostMemori):
    urutan = [0] * (ju + 1)
    fitness = [0] * (ju + 1)
    fitness_relatif = [0] * (ju + 1)
    fitness_kumulatif = [0] * (ju + 1)

    for i in range(1, ju + 1):
        k = 1
        for l in range(1, ju + 1):
            if totcostMemori[i] > totcostMemori[l]:
                k += 1
        urutan[i] = k

    totalft = sum(urutan[1:])  # Total fitness
    print(f"Total ft = {totalft}")

    for i in range(1, ju + 1):
        fitness[i] = totalft - urutan[i]

    totalfitness = sum(fitness[1:])

    for i in range(1, ju + 1):
        fitness_relatif[i] = fitness[i] / totalfitness
        fitness_kumulatif[i] = fitness_kumulatif[i - 1] + fitness_relatif[i]
        print(f"Fitness[{i}]: {fitness[i]}, Fitness Relatif: {fitness_relatif[i]}, Fitness Kumulatif: {fitness_kumulatif[i]}")

    return fitness_kumulatif

def biaya_terkecil(ju, totcost):
    cost_min = totcost[1]
    x_best = 1
    for i in range(1, ju + 1):
        if totcost[i] < cost_min:
            cost_min = totcost[i]
            x_best = i
    return cost_min, x_best

def jarak_terbaik(ju, jarak_total):
    jarak_terpendek = jarak_total[1]
    x_best = 1
    for i in range(1, ju + 1):
        if jarak_total[i] < jarak_terpendek:
            jarak_terpendek = jarak_total[i]
            x_best = i
    return jarak_terpendek, x_best

def x_terbaik(ju, totcost):
    cost_min = totcost[1]
    x_best = 1
    for i in range(1, ju + 1):
        if totcost[i] < cost_min:
            cost_min = totcost[i]
            x_best = i
    return x_best

def baca_file(nama_file):
    data = []
    try:
        with open(nama_file, 'r') as file:
            for line in file:
                # Misalnya, jika data dipisahkan oleh spasi
                baris_data = line.strip().split()  # Memisahkan berdasarkan spasi
                data.append([float(x) for x in baris_data])  # Mengonversi ke float
    except FileNotFoundError:
        print(f"File '{nama_file}' tidak ditemukan.")
    except Exception as e:
        print(f"Terjadi kesalahan: {e}")
    return data

def main():
    print("===============================================================")
    print("                    ALTTALLARIKA SATRIA BIMANTARA              ")
    print("                           082111233045                        ")
    print("             **Program Improved Crow Search Algorithm**        ")
    print("	  **Untuk Menyelesaikan Open Vehicle Routing Problem**		 ")
    print("===============================================================")

    # Pilihan data

    while True:
        print("\n Pilih: \n")
        print(" 1. Data Kecil\n")   
        print(" 2. Data Sedang\n")
        print(" 3. Data Besar\n")

        pilihan_input = input("\nPilihan: ").strip()
        if not pilihan_input.isdigit():
            print("Inputan salah, mohon ulangi !!!!\n")
            continue
   
        pilihan = int(input("Pilihan: "))
        if pilihan == 1:
            jum_pel = 18
            kap_ken = 80
            jum_ken = 3
            file_path = "DataKecil.csv"
            print(f"-Data yang Dipilih: Data Kecil dengan jumlah pelanggan={jum_pel},kapasitas kendaraan={kap_ken}, jumlah kendaraan={jum_ken}\n")
        elif pilihan == 2:
            jum_pel = 50
            kap_ken = 150
            jum_ken = 4
            file_path = "DataSedang.csv"
            print(f"-Data yang Dipilih: Data Sedang dengan jumlah pelanggan={jum_pel},kapasitas kendaraan={kap_ken}, jumlah kendaraan={jum_ken}\n")
        elif pilihan == 3:
            jum_pel = 100
            kap_ken = 200
            jum_ken = 5
            file_path = "DataBesar.csv"
            print(f"-Data yang Dipilih: Data Besar dengan jumlah pelanggan={jum_pel},kapasitas kendaraan={kap_ken}, jumlah kendaraan={jum_ken}\n")
        else:
            print("Pilihan tidak valid.")
            continue
    
        try:
            df = pd.read_csv(file_path, header=None, sep=',')
            data = df.values.tolist()
            data = [[float(item) for item in row] for row in data]  
            break
        except FileNotFoundError:
            print(f"File {file_path} tidak ditemukan. Silakan pilih data yang benar!")
        except ValueError as e:
            print(f"Error: {e}. Pastikan data dalam file txt sesuai format yang diharapkan!")
    
    # Menambahkan keterangan Gagak di header dan Pelanggan di index
    #df.index = [f"Jumlah Pelanggan {i+1}" for i in range(len(df))]
    names = ["X", "Y", "Z"]
    df.columns = [names[i % len(names)] for i in range(len(df.columns))]

    # Menampilkan data dengan format tabel
    print(df)


    # Inisialisasi parameter
    while True:
        try:
            max_iterasi = int(input("Maksimum Iterasi: "))
            if max_iterasi <= 0:
                print("Inputan harus lebih dari 0. Mohon ulangi!")
                continue
            break
        except ValueError:
            print("Inputan harus integer. Mohon ulangi!")

    while True:
        try:
            ju = int(input("Jumlah Gagak (>=2): "))
            if ju <= 1:
                print("Inputan harus lebih dari 1. Mohon ulangi!")
                continue
            break
        except ValueError:
            print("Inputan harus integer. Mohon ulangi!")

    while True:
        try:
            fl = int(input("Panjang Terbang: "))
            if fl <= 0:
                print("Inputan harus lebih dari 0. Mohon ulangi!")
                continue
            break
        except ValueError:
            print("Inputan harus integer. Mohon ulangi!")
    
    while True:
        try:
            AP = float(input("Masukkan AP [0 hingga 1]: "))
            if AP < 0 or AP > 1:
                print("Inputan harus diantara 0 sampai 1. Mohon ulangi!")
                continue
            break
        except ValueError:
            print("Inputan harus diantara 0 sampai 1. Mohon ulangi!")

    file = input("> Nama File: ").strip()
    while True:
        try:
            HASIL = int(input("> Nomor Urut File: "))
            break
        except ValueError:
            print("Inputan harus integer. Mohon ulangi!")
    
    namafile = f"{file}{HASIL}.txt"
    print(f"File akan disimpan dengan nama: {namafile}")

    # Memanggil fungsi random untuk membangkitkan posisi awal
    crow_awal, memori_awal = random_crow(ju, jum_pel)

    with open(namafile, "w", encoding="utf-8") as savefile:
        sys.stdout = savefile

        # Menghitung jarak tempuh
        jarak_tempuh = [[0] * (jum_pel + 1) for _ in range(jum_pel + 1)]
        for i in range(jum_pel + 1):
            for j in range(jum_pel + 1):
                jarak_tempuh[i][j] = math.sqrt((data[i][0] - data[j][0]) ** 2 + (data[i][1] - data[j][1]) ** 2)

        # Evaluasi posisi awal
        for j in range(1, ju + 1):
            pcrow = transformasi(j, jum_pel, crow_awal)
            rute, brute = tentukan_rute(j, jum_pel, pcrow, data, kap_ken)
            totcost = fungsi_tujuan(j, jum_pel, pcrow, rute, brute, jum_ken, jarak_tempuh)
        # Inisialisasi variabel yang diperlukan
jarak_total = [0] * (ju + 1)
jarak = [[0] * (jum_pel + 1) for _ in range(ju + 1)]
costKMpribadi = [0] * (ju + 1)
costKMsewa = [0] * (ju + 1)
costv = [0] * (ju + 1)
totcost = [0] * (ju + 1)

# Evaluasi posisi awal
for j in range(1, ju + 1):
    pcrow = transformasi(j, jum_pel, crow_awal)
    rute, brute = tentukan_rute(j, jum_pel, pcrow, data, kap_ken)
    # Memanggil fungsi_tujuan dengan semua argumen yang diperlukan
    totcost = fungsi_tujuan(j, jum_pel, pcrow, rute, brute, jum_ken, jarak_total, jarak, costKMpribadi, costKMsewa, costv, totcost)

        # Proses iterasi
    for iterasi in range(1, max_iterasi + 1):
            print(f">>>>>>>>>>>>>>>>>>>> PROSES ITERASI KE {iterasi} >>>>>>>>>>>>>>>>>>>>>")
            # Update posisi dan evaluasi
            # (Masukkan logika untuk update posisi dan evaluasi di sini)
    sys.stdout = sys.__stdout__
    # Menampilkan hasil akhir
    print("_____________________ HASIL AKHIR ________________")
    # (Masukkan logika untuk menampilkan hasil akhir di sini)

if __name__ == "__main__":
    main()

