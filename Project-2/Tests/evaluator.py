import os
import time
from matplotlib import pyplot as plt

def main():
    time_data = []
    input_data = []
    for i in range(1, 11):
        test = "my_tests/test" + str(i) + ".txt"
        shell_command = "./a.out < " + test
        start_time = time.time()
        time_taken = os.system(shell_command)
        end_time = time.time()
        time_data.append(end_time - start_time)
        input_data.append(10000*i)
        
    plt.plot(input_data, time_data)
    plt.ylabel("Time (in seconds)")
    plt.xlabel("#Vertices")
    plt.show()

if __name__ == "__main__":
    main()
