import cv2

arr = []
N = int(input("N: "))
for I in range(N):
    min_map = input(":")
    arr.append(list(map(int, min_map.split())))

for i in range(N):
    for j in range(N):
       
        if arr[i][j] == 1:
            print("*", end=" ")
        else:
            count = 0
            
            for x in range(max(0, i - 1), min(N, i + 2)):
                for y in range(max(0, j - 1), min(N, j + 2)):
                    count += arr[x][y]
            
            count -= arr[i][j]
            print(count, end=" ")
    print()