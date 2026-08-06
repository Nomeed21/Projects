import random

def generate_array(size):
    array = []
    for i in range(size):
        array.append(random.randint(1, size))
    print("Random Array:", array , "\n\n")
    return array

#bubble sort
def bubble_sort(array):
    for i in range(len(array) - 1):
        swapped = False
        
        for j in range(len(array) -1 - i):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j+1], array[j]
                swapped = True
        if not swapped:
            break

    return array

#selection sort
def selection_sort(array):
    for i in range(len(array) - 1):
        min_index = i

        for j in range(i + 1, len(array)):
            if array[min_index] > array[j]:
                min_index = j

        array[min_index], array[i] = array[i], array[min_index]

#insertion sort
def insertion_sort(array):
    for i in range(1, len(array)):
        current = array[i]
        insert_index = i

        for j in range(i - 1, -1, -1):
            if array[j] > current:
                array[j + 1] = array[j]
                insert_index = j
            else:
                break

        array[insert_index] = current

    return array

#quick sort
def partition(array, low, high):
    pivot = array[high]
    i = low - 1
    for j in range(low, high):
        if array[j] <= pivot:
            i += 1
            array[i], array[j] = array[j], array[i]
    array[i + 1], array[high] = array[high], array[i + 1] 
    return i+1

def quick_sort(array, low=0, high=None):
    if high is None:
        high = len(array) - 1

    if low < high:
        pivot_index = partition(array, low, high)
        quick_sort(array, low, pivot_index-1)
        quick_sort(array, pivot_index+1, high)

#counting sort
def counting_sort(arr):
    if not arr:
        return arr

    max_val = max(arr)
    count = [0] * (max_val + 1)

    for num in arr:
        count[num] += 1

    arr[:] = []

    for num, freq in enumerate(count):
        arr.extend([num] * freq)

    return arr

#radix sort
def radix_sort(myArray):
    radixArray = [[], [], [], [], [], [], [], [], [], []]
    maxVal = max(myArray)
    exp = 1

    while maxVal // exp > 0:

        while len(myArray) > 0:
            val = myArray.pop()
            radixIndex = (val // exp) % 10
            radixArray[radixIndex].append(val)

        for bucket in radixArray:
            while len(bucket) > 0:
                val = bucket.pop()
                myArray.append(val)

        exp *= 10
    return myArray



array = generate_array(10)
radix_sort(array)
print("Sorted Array: ", array)