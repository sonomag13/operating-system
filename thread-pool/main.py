
"""
Ref.:
https://stackoverflow.com/questions/21143162/python-wait-on-all-of-concurrent-futures-threadpoolexecutors-futures
"""
from concurrent.futures import ThreadPoolExecutor
import random
import time


def work(info):
    print("i = {}".format(info["idx"]))
    val = random.randint(1, 5)
    time.sleep(val)
    info["dict"].update({info["idx"]: val})


def main():
    work_dict = {}
    pool = ThreadPoolExecutor(max_workers=3)
    num = 20
    for i in range(num):
        info = {"dict": work_dict, "idx": i}
        pool.submit(work, info)

    # shutdonw ensures all the task in the pool to be completed
    pool.shutdown(wait=True)

    # interestingly the dictionary is passed by the reference
    for key in work_dict:
        print("key = {} and val = {}".format(key, work_dict[key]))


if __name__ == '__main__':
    main()
    