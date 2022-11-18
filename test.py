with open("dvl_data_3.txt", "r") as f:
    mx = 0
    for l in f.readlines():
        l = l.strip()
        mx = max(mx, len(l))
        print(l)
    print(f"max {mx} chars")
