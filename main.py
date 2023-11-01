import matplotlib.pyplot as plt


def main():
    path_to_file = "D:\\Junk\\records.txt"
    count_recordings = 100
    ns = [i for i in range(0, 10**5, 1000)]
    plt.figure(figsize=(8, 6))
    with open(path_to_file) as f:
        while True:
            name_of_sort_function = f.readline()
            if not name_of_sort_function:
                break
            lead_times = list(map(int, f.readline().split()))
            if len(lead_times) < count_recordings:
                lead_times += [0] * (count_recordings - len(lead_times))
            plt.plot(ns, lead_times, label=name_of_sort_function)

    plt.legend()

    plt.title("Comparison of sorting operating time")
    plt.xlabel("n")
    plt.ylabel("lead_time, s * 10^(-6)")

    plt.show()
    return 0


if __name__ == '__main__':
    main()
