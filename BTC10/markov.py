import numpy as np # tính toán trên ma trận
import pandas as pd # đọc dữ liệu từ file csv
from pprint import pprint # dùng cho mục đích in "đẹp"
from collections import defaultdict # để đếm số lượng lần xảy ra của các trạng thái (đơn lẻ và cặp)

df = pd.read_csv('breakfast.csv')
data = df.Food.tolist()
print(data[-5:]) # xuất ra 5 món ăn cuối cùng bạn ăn

Q = list(set(data))
print(Q)
#exit here to check
# exit()

# tạo nơi lưu trữ giá trị
food_count = defaultdict(int)
food_pair_count = defaultdict(lambda: defaultdict(float))

# food_count: đếm số lần xuất hiện của một trạng thái
# food_pair_count: đếm tất cả các cặp trạng thái có thể [current][future]
n = len(data)
for i in range(n):
    food_count[data[i]] += 1
    if i == n - 1:
        food_pair_count[data[i]][data[i]] += 1
        break
    food_pair_count[data[i]][data[i + 1]] += 1

for i in range(len(Q)):
    for j in range(len(Q)):
        print(f"Hôm nay: {Q[i]} - Ngày mai: {Q[j]}: {food_pair_count[Q[i]][Q[j]]}")
    print()

# chuẩn hóa theo tổng hàng
for key, value in food_pair_count.items():
    for k, v in value.items():
        food_pair_count[key][k] /= food_count[key] # chuẩn hóa

# lấy index của các món ăn để dễ thao tác
keys = list(food_count.keys())
idx = range(len(keys))
key_to_idx = dict(zip(keys, idx)) # key to index
print(key_to_idx)

P = []
for key, value in food_pair_count.items():
    P.append(list(value.values()))
        
# chuyển list sang numpy để dễ tính toán
P = np.array(P)

print('Ma trận chuyển trạng thái P: ')
pprint(P)

# tổng hàng của ma trận phải luôn bằng 1
print(P.sum(axis=1))

# dự đoán món ăn 
curr_food = data[-1]
curr_distribution = P[key_to_idx[curr_food]]
predicted_food = np.random.choice(keys, p=curr_distribution) # random walk with known distribution
predicted_probability = P[key_to_idx[curr_food]][key_to_idx[predicted_food]]

print(f'Món ăn chúng ta ăn hôm trước: {data[-1]}')
print(f'Món ăn nên ăn vào hôm nay là "{predicted_food}"\
 với khả năng xảy ra là {round(predicted_probability * 100, 2)}%')

print("Hello world")