import random

arr = []
for i in range(10):
    arr.append(random.randint(1,10))

def lowest_number(arr):
    lowest = arr[0]
    for i in range(1,len(arr)):
        if arr[i] < lowest:
            lowest = arr[i]
    return lowest

def highest_number(arr):
    highest = arr[0]
    for i in range(1, len(arr)):
        if arr[i] > highest:
            highest = arr[i]
    return highest
print(arr)
print("Lowest number: " + str(lowest_number(arr)))
print("Highest number: " + str(highest_number(arr)))