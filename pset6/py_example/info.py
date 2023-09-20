ho_ten = "samira"
thong_tin = { "so_do": [90, 88, 69],
                "chieu_cao": 1.65,
                "quoc_tich": "Japan"
    }

print(ho_ten + "co chieu cao la " + str(thong_tin["chieu_cao"]))

for i in thong_tin["so_do"]:
    print(i)

def boi_toan(ten_nam, ten_nu):
    #tinh toan
    counter = 0
    for i in ten_nam:
        for j in ten_nu:
            if i.lower() == j.lower():
                counter += 1
    if counter < 3:
        return "khong hop"
    return "hop"

print(boi_toan("samira", "leona"))
